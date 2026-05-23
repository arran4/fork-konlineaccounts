/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "redditsetup.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusReply>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QOAuthHttpServerReplyHandler>
#include <QUrlQuery>
#include <QUuid>

#include <KConfigGroup>
#include <KLocalizedString>
#include <KPluginFactory>
#include <KSharedConfig>

#include <QCoro/QCoroCore>

#include "debug.h"

using namespace Qt::Literals;

#ifndef REDDIT_CLIENT_ID
#define REDDIT_CLIENT_ID ""
#endif

QString redditClientId()
{
    return QStringLiteral(REDDIT_CLIENT_ID);
}

RedditSetup::RedditSetup(QObject *parent)
    : QObject(parent)
    , m_nam(new QNetworkAccessManager(this))
{
}

void RedditSetup::registerReddit()
{
    doRegisterReddit();
}

QCoro::Task<void> RedditSetup::doRegisterReddit()
{
    auto handler = new QOAuthHttpServerReplyHandler(1234, this);

    handler->setCallbackText(i18n("Authentication completed, return to System Settings"));

    if (!handler->isListening()) {
        qCWarning(LOG_KONLINEACCOUNTS_REDDIT) << "Could not start local HTTP server for OAuth";
        m_builder->fail(i18n("Could not start local HTTP server for OAuth"));
        handler->deleteLater();
        co_return;
    }

    const QString clientId = redditClientId();
    if (clientId.isEmpty()) {
        qCWarning(LOG_KONLINEACCOUNTS_REDDIT) << "Reddit Client ID is not set";
        m_builder->fail(i18n("Reddit Client ID is not set"));
        handler->deleteLater();
        co_return;
    }
    const QString state = QUuid::createUuid().toString(QUuid::WithoutBraces);

    QDesktopServices::openUrl(
        QUrl(u"https://www.reddit.com/api/v1/authorize?client_id=%1&response_type=code&state=%2&redirect_uri=http://localhost:1234&duration=permanent&scope=identity%20read"_s.arg(clientId).arg(state)));

    const QVariantMap values = co_await qCoro(handler, &QOAuthHttpServerReplyHandler::callbackReceived);

    qCDebug(LOG_KONLINEACCOUNTS_REDDIT) << "Got Reddit OAuth callback";

    const QString authCode = values[u"code"_s].toString();
    const QString returnedState = values[u"state"_s].toString();

    if (state != returnedState) {
        qCWarning(LOG_KONLINEACCOUNTS_REDDIT) << "Reddit OAuth callback error: state mismatch";
        m_builder->fail(i18n("State mismatch"));
        handler->deleteLater();
        co_return;
    }

    const QUrl tokenUrl = QUrl(u"https://www.reddit.com/api/v1/access_token"_s);
    QUrlQuery q;

    q.addQueryItem(QStringLiteral("grant_type"), u"authorization_code"_s);
    q.addQueryItem(QStringLiteral("code"), authCode);
    q.addQueryItem(QStringLiteral("redirect_uri"), u"http://localhost:1234"_s);

    QNetworkRequest tokenRequest(tokenUrl);
    tokenRequest.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));

    QString auth = clientId + ":";
    tokenRequest.setRawHeader("Authorization", "Basic " + auth.toUtf8().toBase64());

    QNetworkReply *tokenReply = m_nam->post(tokenRequest, q.toString().toUtf8());
    auto tokenData = co_await tokenReply;

    if (tokenReply->error()) {
        qCWarning(LOG_KONLINEACCOUNTS_REDDIT) << "Failed to obtain Reddit token" << tokenReply->errorString() << tokenData;
        m_builder->fail(tokenReply->errorString());
        handler->deleteLater();
        tokenReply->deleteLater();
        co_return;
    }

    QJsonDocument authReplyDoc = QJsonDocument::fromJson(tokenData);

    const QString accessToken = authReplyDoc[u"access_token"].toString();
    const QString refreshToken = authReplyDoc[u"refresh_token"].toString();

    if (accessToken.isEmpty() || refreshToken.isEmpty()) {
        qCWarning(LOG_KONLINEACCOUNTS_REDDIT) << "Missing tokens in Reddit OAuth response";
        m_builder->fail(i18n("Received invalid tokens from Reddit"));
        handler->deleteLater();
        tokenReply->deleteLater();
        co_return;
    }

    auto redditGroup = m_builder->config().group(u"Reddit"_s);
    redditGroup.writeEntry("clientId", clientId);
    redditGroup.writeEntry("accessToken", accessToken);
    redditGroup.writeEntry("refreshToken", refreshToken);

    m_builder->finish();
    handler->deleteLater();
    tokenReply->deleteLater();
    co_return;
}

AccountBuilder *RedditSetup::builder() const
{
    return m_builder;
}

void RedditSetup::setBuilder(AccountBuilder *builder)
{
    m_builder = builder;
    Q_EMIT builderChanged();
}
