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
import org.kde.konlineaccounts.reddit
import org.kde.konlineaccounts

SetupItem {
    id: root

    RedditSetup {
        id: reddit

        builder: root.builder
    }

    ColumnLayout {
        anchors.fill: parent

        Kirigami.FormLayout {
            id: fl

            Layout.fillWidth: true
            Layout.fillHeight: true

            Controls.BusyIndicator {
                id: busy

                running: false
            }
        }

        Controls.Button {
            text: "Login to Reddit"

            enabled: !busy.running

            Layout.alignment: Qt.AlignRight

            onClicked: {
                busy.running = true;
                reddit.registerReddit();
            }
        }
    }
}
