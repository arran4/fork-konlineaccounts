/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "openaicompatiblesetup.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusReply>
#include <QDesktopServices>
#include <QGuiApplication>

#include <KConfigGroup>
#include <KLocalizedString>
#include <KPluginFactory>
#include <KSharedConfig>


#include "debug.h"

using namespace Qt::Literals;

OpenAICompatibleSetup::OpenAICompatibleSetup(QObject *parent)
    : QObject(parent)
{
}

void OpenAICompatibleSetup::registerOpenAICompatible(const QString &instanceUrl, const QString &token)
{
    auto openaicompatibleGroup = m_builder->config().group(u"OpenAICompatible"_s);
    openaicompatibleGroup.writeEntry("instanceUrl", instanceUrl);
    openaicompatibleGroup.writeEntry("accessToken", token);

    m_builder->finish();
}

AccountBuilder *OpenAICompatibleSetup::builder() const
{
    return m_builder;
}

void OpenAICompatibleSetup::setBuilder(AccountBuilder *builder)
{
    m_builder = builder;
    Q_EMIT builderChanged();
}
