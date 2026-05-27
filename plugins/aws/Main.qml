/*
 *   SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
 *
 *   SPDX-License-Identifier: GPL-2.0-or-later
 */

pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls as Controls
import QtQuick.Layouts

import org.kde.kirigami as Kirigami
import org.kde.konlineaccounts.aws
import org.kde.konlineaccounts

SetupItem {
    id: root

    AwsSetup {
        id: setup
        builder: root.builder
    }

    ColumnLayout {
        anchors.fill: parent

        Kirigami.FormLayout {
            Layout.fillWidth: true

            Controls.TextField {
                id: regionField
                Kirigami.FormData.label: i18n("Region:")
            }
            Controls.TextField {
                id: accessKeyField
                Kirigami.FormData.label: i18n("Access Key:")
            }
            Controls.TextField {
                id: secretKeyField
                Kirigami.FormData.label: i18n("Secret Key:")
                echoMode: TextInput.Password
            }
        }

        Controls.Button {
            text: i18n("Save")
            Layout.alignment: Qt.AlignRight
            enabled: accessKeyField.text.trim() !== "" && secretKeyField.text.trim() !== ""
            onClicked: {
                setup.save(regionField.text, accessKeyField.text, secretKeyField.text)
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
