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

class S3 : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.KOnlineAccounts.S3")

    Q_PROPERTY(QString endpoint READ endpoint)
    Q_PROPERTY(QString region READ region)
    Q_PROPERTY(QString accessKey READ accessKey)
    Q_PROPERTY(QDBusUnixFileDescriptor secretKey READ secretKey)

public:
    S3(Account *account, KConfigGroup config);

    QString endpoint() const;
    QString region() const;
    QString accessKey() const;
    QDBusUnixFileDescriptor secretKey() const;

private:
    KConfigGroup m_config;
    Account *m_account;
};
