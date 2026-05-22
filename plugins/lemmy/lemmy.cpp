/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "lemmy.h"

#include "lemmyinterface.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(LemmyAccount, "metadata.json")

using namespace Qt::StringLiterals;

LemmyAccount::LemmyAccount(QObject *parent, const KPluginMetaData &md, const QVariantList &args)
    : Account(parent, md, args)
{
    new LemmyInterface(this, config().group(u"Lemmy"_s));
}

#include "lemmy.moc"
