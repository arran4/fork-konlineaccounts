/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QObject>
#include <QVariant>
#include <qqmlregistration.h>

#include <QCoro/QCoroCore>

#include "accountbuilder.h"

class LemmySetup : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(AccountBuilder *builder READ builder WRITE setBuilder NOTIFY builderChanged)

public:
    explicit LemmySetup(QObject *parent = nullptr);

    Q_INVOKABLE void registerLemmy(const QString &instanceUrl, const QString &username, const QString &password);

    AccountBuilder *builder() const;
    void setBuilder(AccountBuilder *builder);
    Q_SIGNAL void builderChanged();

private:
    QCoro::Task<void> doRegisterLemmy(const QString &instanceUrl, const QString &username, const QString &password);

    AccountBuilder *m_builder;
};
