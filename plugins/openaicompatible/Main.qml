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
import org.kde.konlineaccounts.openaicompatible
import org.kde.konlineaccounts

SetupItem {
    id: root

    OpenAICompatibleSetup {
        id: openaicompatible

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
                placeholderText: "https://api.openai.com"
                text: "https://api.openai.com"
                Kirigami.FormData.label: i18n("Instance URL:")
            }

            Controls.TextField {
                id: token
                echoMode: TextInput.Password
                Kirigami.FormData.label: i18n("Token:")
            }

            Controls.BusyIndicator {
                id: busy

                running: false
            }
        }

        Controls.Button {
            text: i18n("Add")

            enabled: !busy.running && token.text.length > 0

            Layout.alignment: Qt.AlignRight

            onClicked: {
                busy.running = true;
                openaicompatible.registerOpenAICompatible(instance.text, token.text);
            }
        }
    }
}
