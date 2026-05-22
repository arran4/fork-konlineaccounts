/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "lemmysetup.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <KConfigGroup>
#include <KLocalizedString>
#include <KPluginFactory>
#include <KSharedConfig>

#include <QCoro/QCoroCore>
#include <QCoro/QCoroNetwork>

#include "debug.h"

using namespace Qt::Literals;

LemmySetup::LemmySetup(QObject *parent)
    : QObject(parent)
{
}

void LemmySetup::registerLemmy(const QString &instanceUrl, const QString &username, const QString &password)
{
    doRegisterLemmy(instanceUrl, username, password);
}

QCoro::Task<void> LemmySetup::doRegisterLemmy(const QString &_instanceUrl, const QString &username, const QString &password)
{
    QString instanceUrl = _instanceUrl.trimmed();
    if (!instanceUrl.startsWith(u"http://") && !instanceUrl.startsWith(u"https://")) {
        instanceUrl.prepend(u"https://");
    }

    QUrl loginUrl = QUrl::fromUserInput(instanceUrl);
    loginUrl.setPath(u"/api/v3/user/login"_s);
    const QJsonObject obj{
        {QStringLiteral("username_or_email"), username},
        {QStringLiteral("password"), password},
    };
    const QJsonDocument doc(obj);

    QNetworkRequest req(loginUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    QNetworkAccessManager *nam = new QNetworkAccessManager(this);

    QNetworkReply *loginReply = nam->post(req, doc.toJson());
    const QByteArray loginReplyData = co_await loginReply;

    if (loginReply->error()) {
        qCWarning(LOG_KONLINEACCOUNTS_LEMMY) << "Error logging in" << loginReply->errorString();
        m_builder->fail(loginReply->errorString());
        loginReply->deleteLater();
        nam->deleteLater();
        co_return;
    }

    loginReply->deleteLater();
    nam->deleteLater();

    QJsonParseError parseError;
    QJsonDocument replyDoc = QJsonDocument::fromJson(loginReplyData, &parseError);

    if (parseError.error != QJsonParseError::NoError || !replyDoc.isObject() || !replyDoc.object().contains(u"jwt")) {
        qCWarning(LOG_KONLINEACCOUNTS_LEMMY) << "Invalid JSON response or missing JWT token";
        m_builder->fail(i18n("Invalid server response"));
        co_return;
    }

    const QString accessToken = replyDoc.object()[u"jwt"].toString();

    auto lemmyGroup = m_builder->config().group(u"Lemmy"_s);
    lemmyGroup.writeEntry("instanceUrl", instanceUrl);
    lemmyGroup.writeEntry("username", username);
    lemmyGroup.writeEntry("accessToken", accessToken);

    m_builder->finish();
    co_return;
}

AccountBuilder *LemmySetup::builder() const
{
    return m_builder;
}

void LemmySetup::setBuilder(AccountBuilder *builder)
{
    m_builder = builder;
    Q_EMIT builderChanged();
}
