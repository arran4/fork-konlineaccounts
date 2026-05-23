/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QDBusAbstractAdaptor>
#include <QDBusUnixFileDescriptor>
#include <QObject>

#include <KConfigGroup>

#include "account.h"

class OpenAICompatibleInterface : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.KOnlineAccounts.OpenAICompatible")

    Q_PROPERTY(QString instanceUrl READ instanceUrl)
    Q_PROPERTY(QDBusUnixFileDescriptor accessToken READ accessToken)

public:
    OpenAICompatibleInterface(Account *account, KConfigGroup config);

    QString instanceUrl() const;
    QDBusUnixFileDescriptor accessToken() const;

private:
    KConfigGroup m_config;
    Account *m_account;
};
