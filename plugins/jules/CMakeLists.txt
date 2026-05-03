# SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
# SPDX-License-Identifier: BSD-2-Clause

add_library(jules MODULE
    jules.cpp
    julesinterface.cpp
)

target_link_libraries(jules
    KOnlineAccounts
    Qt::DBus
    KF6::CoreAddons
    KF6::ConfigCore
)

install(TARGETS jules DESTINATION ${KDE_INSTALL_PLUGINDIR}/konlineaccounts)

# QML Module
ecm_add_qml_module(julessetup
    URI org.kde.konlineaccounts.jules
    INSTALL_DIR ${KDE_INSTALL_QMLDIR}/org/kde/konlineaccounts/jules
    QML_FILES
        Main.qml
    SOURCES
        julessetup.cpp
)

target_link_libraries(julessetup
    KOnlineAccounts
    KF6::ConfigCore
)
