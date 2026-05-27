# SPDX-FileCopyrightText: 2025 Nicolas Fella <nicolas.fella@gmx.de>
# SPDX-License-Identifier: BSD-2-Clause

kcoreaddons_add_plugin(aws INSTALL_NAMESPACE "konlineaccounts/providers")

target_sources(aws PRIVATE aws.cpp ../s3/s3.cpp)

target_link_libraries(aws PRIVATE accounts KF6::CoreAddons Qt::DBus)

ecm_add_qml_module(awssetup URI "org.kde.konlineaccounts.aws" QML_FILES Main.qml GENERATE_PLUGIN_SOURCE DEPENDENCIES QtCore org.kde.konlineaccounts)
target_sources(awssetup PRIVATE awssetup.cpp)
target_link_libraries(awssetup PRIVATE QCoro::Core QCoro::Network KF6::I18n KF6::KIOCore accounts)
ecm_finalize_qml_module(awssetup)
