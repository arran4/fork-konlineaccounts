# SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
# SPDX-License-Identifier: BSD-2-Clause

kcoreaddons_add_plugin(s3 INSTALL_NAMESPACE "konlineaccounts/providers")

target_sources(s3 PRIVATE s3account.cpp s3.cpp)

target_link_libraries(s3 PRIVATE accounts KF6::CoreAddons Qt::DBus)

ecm_add_qml_module(s3setup URI "org.kde.konlineaccounts.s3" QML_FILES Main.qml GENERATE_PLUGIN_SOURCE DEPENDENCIES QtCore org.kde.konlineaccounts)
target_sources(s3setup PRIVATE s3setup.cpp)
target_link_libraries(s3setup PRIVATE QCoro::Core QCoro::Network KF6::I18n KF6::KIOCore accounts)
ecm_finalize_qml_module(s3setup)
