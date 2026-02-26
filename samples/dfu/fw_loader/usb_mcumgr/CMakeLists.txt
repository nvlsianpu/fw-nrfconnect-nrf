#
# Copyright (c) 2026 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(usb_mcumgr)

target_sources(app PRIVATE ${ZEPHYR_BASE}/samples/subsys/mgmt/mcumgr/smp_svr/src/main.c)

# Custom CDC ACM serial init (registers all devicetree instances) when enabled
target_sources_ifdef(CONFIG_FW_LOADER_CUSTOM_USB app PRIVATE cdc_acm_serial.c)
