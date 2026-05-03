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
import org.kde.konlineaccounts.jules
import org.kde.konlineaccounts

SetupItem {
    id: root

    JulesSetup {
        id: jules

        builder: root.builder
    }

    ColumnLayout {
        anchors.fill: parent

        Kirigami.FormLayout {
            id: fl

            Layout.fillWidth: true
            Layout.fillHeight: true

            Controls.TextField {
                id: tokenInput
                placeholderText: "Enter Jules token"
                Kirigami.FormData.label: "Token:"
                echoMode: TextInput.Password
            }
        }

        Controls.Button {
            text: "Add"
            Layout.alignment: Qt.AlignRight

            onClicked: {
                jules.registerJules(tokenInput.text);
            }
        }
    }
}
