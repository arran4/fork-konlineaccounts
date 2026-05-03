/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "julesinterface.h"

#include <QDBusConnection>

using namespace Qt::StringLiterals;

JulesInterface::JulesInterface(Account *account, KConfigGroup config)
    : QDBusAbstractAdaptor(account)
    , m_config(config)
    , m_account(account)
{
    QDBusConnection::sessionBus().registerObject(account->objectPath(), account, QDBusConnection::ExportAdaptors);
}

QString JulesInterface::token() const
{
    if (!m_account->hasAccess()) {
        return {};
    }

    return m_config.readEntry("token");
}
