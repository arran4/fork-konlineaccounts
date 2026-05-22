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

class RedditInterface : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.KOnlineAccounts.Reddit")

    Q_PROPERTY(QString clientId READ clientId)
    Q_PROPERTY(QDBusUnixFileDescriptor accessToken READ accessToken)
    Q_PROPERTY(QDBusUnixFileDescriptor refreshToken READ refreshToken)

public:
    RedditInterface(Account *account, KConfigGroup config);

    QString clientId() const;
    QDBusUnixFileDescriptor accessToken() const;
    QDBusUnixFileDescriptor refreshToken() const;

private:
    KConfigGroup m_config;
    Account *m_account;
};
