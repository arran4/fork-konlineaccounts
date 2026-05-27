/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "awssetup.h"

using namespace Qt::Literals;

AwsSetup::AwsSetup(QObject *parent)
    : QObject(parent)
{
}

AccountBuilder *AwsSetup::builder() const
{
    return m_builder;
}

void AwsSetup::setBuilder(AccountBuilder *builder)
{
    m_builder = builder;
    Q_EMIT builderChanged();
}

void AwsSetup::save(const QString &region, const QString &accessKey, const QString &secretKey)
{
    if (!m_builder) {
        return;
    }

    auto s3Group = m_builder->config().group(u"S3"_s);

    // Construct the endpoint dynamically based on the region
    QString endpoint = QStringLiteral("https://s3.amazonaws.com");
    if (!region.isEmpty() && region != u"us-east-1"_s) {
        endpoint = QStringLiteral("https://s3.%1.amazonaws.com").arg(region);
    }

    s3Group.writeEntry("endpoint", endpoint);
    s3Group.writeEntry("region", region);
    s3Group.writeEntry("accessKey", accessKey);
    s3Group.writeEntry("secretKey", secretKey);

    m_builder->finish();
}
