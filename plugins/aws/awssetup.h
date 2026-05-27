/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QObject>
#include <qqmlregistration.h>

#include "accountbuilder.h"

class AwsSetup : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(AccountBuilder *builder READ builder WRITE setBuilder NOTIFY builderChanged)
public:
    AwsSetup(QObject *parent = nullptr);

    AccountBuilder *builder() const;
    void setBuilder(AccountBuilder *builder);
    Q_SIGNAL void builderChanged();

    Q_INVOKABLE void save(const QString &region, const QString &accessKey, const QString &secretKey);

private:
    AccountBuilder *m_builder = nullptr;
};
