/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "openaicompatible.h"

#include "openaicompatibleinterface.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(OpenAICompatibleAccount, "metadata.json")

using namespace Qt::StringLiterals;

OpenAICompatibleAccount::OpenAICompatibleAccount(QObject *parent, const KPluginMetaData &md, const QVariantList &args)
    : Account(parent, md, args)
{
    new OpenAICompatibleInterface(this, config().group(u"OpenAICompatible"_s));
}

#include "openaicompatible.moc"
