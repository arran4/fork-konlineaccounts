/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "s3setup.h"

using namespace Qt::Literals;

S3Setup::S3Setup(QObject *parent)
    : QObject(parent)
{
}

AccountBuilder *S3Setup::builder() const
{
    return m_builder;
}

void S3Setup::setBuilder(AccountBuilder *builder)
{
    m_builder = builder;
    Q_EMIT builderChanged();
}

void S3Setup::save(const QString &endpoint, const QString &region, const QString &accessKey, const QString &secretKey)
{
    if (!m_builder) {
        return;
    }

    auto s3Group = m_builder->config().group(u"S3"_s);
    s3Group.writeEntry("endpoint", endpoint);
    s3Group.writeEntry("region", region);
    s3Group.writeEntry("accessKey", accessKey);
    s3Group.writeEntry("secretKey", secretKey);

    m_builder->finish();
}
