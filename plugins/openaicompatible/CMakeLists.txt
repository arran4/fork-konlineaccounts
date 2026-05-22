# SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
# SPDX-License-Identifier: BSD-2-Clause

kcoreaddons_add_plugin(openaicompatible INSTALL_NAMESPACE "konlineaccounts/providers")

target_sources(openaicompatible PRIVATE openaicompatible.cpp openaicompatibleinterface.cpp)

target_link_libraries(openaicompatible PRIVATE accounts KF6::CoreAddons Qt::DBus)

ecm_add_qml_module(openaicompatiblesetup URI "org.kde.konlineaccounts.openaicompatible" QML_FILES Main.qml GENERATE_PLUGIN_SOURCE DEPENDENCIES QtCore org.kde.konlineaccounts)
target_sources(openaicompatiblesetup PRIVATE openaicompatiblesetup.cpp)
target_link_libraries(openaicompatiblesetup PRIVATE KF6::I18n accounts)
ecm_finalize_qml_module(openaicompatiblesetup)

ecm_qt_declare_logging_category(openaicompatiblesetup
    HEADER debug.h
    IDENTIFIER LOG_KONLINEACCOUNTS_OPENAICOMPATIBLE
    CATEGORY_NAME konlineaccounts.openaicompatible
    DESCRIPTION "KOnlineAccounts OpenAI Compatible"
    EXPORT KOnlineAccounts
)
