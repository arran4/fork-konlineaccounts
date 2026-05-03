/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QDBusAbstractAdaptor>
#include <QObject>

#include <KConfigGroup>

#include "account.h"

class JulesInterface : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.KOnlineAccounts.Jules")

    Q_PROPERTY(QString token READ token)

public:
    JulesInterface(Account *account, KConfigGroup config);

    QString token() const;

private:
    KConfigGroup m_config;
    Account *m_account;
};
