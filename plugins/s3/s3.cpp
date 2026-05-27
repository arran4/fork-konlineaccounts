/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "s3.h"

#include "fdwriter.h"

using namespace Qt::Literals;

S3::S3(Account *account, KConfigGroup config)
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

QString S3::endpoint() const
{
    CHECK_ACCESS

    return m_config.readEntry("endpoint", QString());
}

QString S3::region() const
{
    CHECK_ACCESS

    return m_config.readEntry("region", QString());
}

QString S3::accessKey() const
{
    CHECK_ACCESS

    return m_config.readEntry("accessKey", QString());
}

QDBusUnixFileDescriptor S3::secretKey() const
{
    CHECK_ACCESS

    const QByteArray secretKey = m_config.readEntry("secretKey", QString()).toUtf8();

    const auto result = FdWriter::write(secretKey);

    if (!result) {
        m_account->sendErrorReply(QDBusError::InternalError, u"Internal error"_s);
        return {};
    }

    return *result;
}
