/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "aws.h"

#include "../s3/s3.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AwsAccount, "metadata.json")

using namespace Qt::StringLiterals;

AwsAccount::AwsAccount(QObject *parent, const KPluginMetaData &md, const QVariantList &args)
    : Account(parent, md, args)
{
    new S3(this, config().group(u"S3"_s));
}

#include "aws.moc"
