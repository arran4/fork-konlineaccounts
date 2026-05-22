# SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
# SPDX-License-Identifier: BSD-2-Clause

kcoreaddons_add_plugin(reddit INSTALL_NAMESPACE "konlineaccounts/providers")

target_sources(reddit PRIVATE reddit.cpp redditinterface.cpp)

target_link_libraries(reddit PRIVATE accounts KF6::CoreAddons Qt::DBus)

ecm_add_qml_module(redditsetup URI "org.kde.konlineaccounts.reddit" QML_FILES Main.qml GENERATE_PLUGIN_SOURCE DEPENDENCIES QtCore org.kde.konlineaccounts)
target_sources(redditsetup PRIVATE redditsetup.cpp)
target_link_libraries(redditsetup PRIVATE Qt::NetworkAuth QCoro::Core QCoro::Network KF6::I18n KF6::KIOCore accounts)
target_compile_definitions(redditsetup PRIVATE REDDIT_CLIENT_ID="KDE_Online_Accounts")
ecm_finalize_qml_module(redditsetup)

ecm_qt_declare_logging_category(redditsetup
    HEADER debug.h
    IDENTIFIER LOG_KONLINEACCOUNTS_REDDIT
    CATEGORY_NAME konlineaccounts.reddit
    DESCRIPTION "KOnlineAccounts Reddit"
    EXPORT KOnlineAccounts
)
