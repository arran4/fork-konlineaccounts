/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "reddit.h"

#include "redditinterface.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(RedditAccount, "metadata.json")

using namespace Qt::StringLiterals;

RedditAccount::RedditAccount(QObject *parent, const KPluginMetaData &md, const QVariantList &args)
    : Account(parent, md, args)
{
    new RedditInterface(this, config().group(u"Reddit"_s));
}

#include "reddit.moc"
