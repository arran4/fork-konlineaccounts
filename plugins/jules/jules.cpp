/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "jules.h"

#include "julesinterface.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(JulesAccount, "metadata.json")

using namespace Qt::StringLiterals;

JulesAccount::JulesAccount(QObject *parent, const KPluginMetaData &md, const QVariantList &args)
    : Account(parent, md, args)
{
    new JulesInterface(this, config().group(u"Jules"_s));
}

#include "jules.moc"
