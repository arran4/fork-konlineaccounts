/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "julessetup.h"

#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::StringLiterals;

JulesSetup::JulesSetup(QObject *parent)
    : QObject(parent)
{
}

void JulesSetup::registerJules(const QString &token)
{
    auto julesGroup = m_builder->config().group(u"Jules"_s);
    julesGroup.writeEntry("token", token);

    m_builder->finish();
}

AccountBuilder *JulesSetup::builder() const
{
    return m_builder;
}

void JulesSetup::setBuilder(AccountBuilder *builder)
{
    m_builder = builder;
    Q_EMIT builderChanged();
}
