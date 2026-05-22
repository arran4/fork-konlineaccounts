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
import org.kde.konlineaccounts.lemmy
import org.kde.konlineaccounts

SetupItem {
    id: root

    LemmySetup {
        id: lemmy

        builder: root.builder
    }

    ColumnLayout {
        anchors.fill: parent

        Kirigami.FormLayout {
            id: fl

            Layout.fillWidth: true
            Layout.fillHeight: true

            Controls.TextField {
                id: instance
                placeholderText: "https://lemmy.kde.org"
                Kirigami.FormData.label: "Instance URL:"
            }

            Controls.TextField {
                id: username
                Kirigami.FormData.label: "Username:"
            }

            Controls.TextField {
                id: password
                echoMode: TextInput.Password
                Kirigami.FormData.label: "Password:"
            }

            Controls.BusyIndicator {
                id: busy

                running: false
            }
        }

        Controls.Button {
            text: "Add"

            enabled: !busy.running

            Layout.alignment: Qt.AlignRight

            onClicked: {
                busy.running = true;
                lemmy.registerLemmy(instance.text, username.text, password.text);
            }
        }
    }
}
