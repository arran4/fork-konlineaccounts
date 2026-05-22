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

        onBuilderChanged: {
            if (lemmy.builder) {
                lemmy.builder.finished.connect(() => busy.running = false)
                lemmy.builder.failed.connect(() => busy.running = false)
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Kirigami.FormLayout {
            id: fl

            Layout.fillWidth: true
            Layout.fillHeight: true

            Controls.TextField {
                id: instance
                placeholderText: i18n("https://lemmy.kde.org")
                Kirigami.FormData.label: i18n("Instance URL:")
            }

            Controls.TextField {
                id: username
                Kirigami.FormData.label: i18n("Username:")
            }

            Controls.TextField {
                id: password
                echoMode: TextInput.Password
                Kirigami.FormData.label: i18n("Password:")
            }

            Controls.BusyIndicator {
                id: busy

                running: false
            }
        }

        Controls.Button {
            text: i18n("Add")

            enabled: !busy.running && instance.text.length > 0 && username.text.length > 0 && password.text.length > 0

            Layout.alignment: Qt.AlignRight

            onClicked: {
                busy.running = true;
                lemmy.registerLemmy(instance.text, username.text, password.text);
            }
        }
    }
}
