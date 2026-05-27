/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "s3account.h"

#include "s3.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(S3Account, "metadata.json")

using namespace Qt::StringLiterals;

S3Account::S3Account(QObject *parent, const KPluginMetaData &md, const QVariantList &args)
    : Account(parent, md, args)
{
    new S3(this, config().group(u"S3"_s));
}

#include "s3account.moc"
