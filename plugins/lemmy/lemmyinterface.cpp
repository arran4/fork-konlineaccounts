/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "lemmyinterface.h"

#include "fdwriter.h"

using namespace Qt::Literals;

LemmyInterface::LemmyInterface(Account *account, KConfigGroup config)
    : QDBusAbstractAdaptor(account)
    , m_config(config)
    , m_account(account)
{
}

#define CHECK_ACCESS                                                                                                                                           \
    if (!m_account->currentCallerHasAccess()) {                                                                                                                \
        m_account->sendErrorReply(QDBusError::AccessDenied, u"Caller is not authorized to read this property"_s);                                              \
        return {};                                                                                                                                             \
    }

QString LemmyInterface::instanceUrl() const
{
    CHECK_ACCESS

    return m_config.readEntry("instanceUrl", QString());
}

QString LemmyInterface::username() const
{
    CHECK_ACCESS

    return m_config.readEntry("username", QString());
}

QDBusUnixFileDescriptor LemmyInterface::accessToken() const
{
    CHECK_ACCESS

    const QByteArray accessToken = m_config.readEntry("accessToken", QString()).toUtf8();

    const auto result = FdWriter::write(accessToken);

    if (!result) {
        m_account->sendErrorReply(QDBusError::InternalError, u"Internal error"_s);
        return {};
    }

    return *result;
}
