# SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
# SPDX-License-Identifier: BSD-2-Clause

kcoreaddons_add_plugin(lemmy INSTALL_NAMESPACE "konlineaccounts/providers")

target_sources(lemmy PRIVATE lemmy.cpp lemmyinterface.cpp)

target_link_libraries(lemmy PRIVATE accounts KF6::CoreAddons Qt::DBus)

ecm_add_qml_module(lemmysetup URI "org.kde.konlineaccounts.lemmy" QML_FILES Main.qml GENERATE_PLUGIN_SOURCE DEPENDENCIES QtCore org.kde.konlineaccounts)
target_sources(lemmysetup PRIVATE lemmysetup.cpp)
target_link_libraries(lemmysetup PRIVATE Qt::NetworkAuth QCoro::Core QCoro::Network KF6::I18n KF6::KIOCore accounts)
ecm_finalize_qml_module(lemmysetup)

ecm_qt_declare_logging_category(lemmysetup
    HEADER debug.h
    IDENTIFIER LOG_KONLINEACCOUNTS_LEMMY
    CATEGORY_NAME konlineaccounts.lemmy
    DESCRIPTION "KOnlineAccounts Lemmy"
    EXPORT KOnlineAccounts
)
