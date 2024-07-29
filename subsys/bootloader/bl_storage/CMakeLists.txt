#
# Copyright (c) 2020 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

zephyr_library()
zephyr_library_sources(bl_storage.c)
if(CONFIG_NRFX_NVMC)
zephyr_library_sources(bl_storage_nvmc.c)
elseif(CONFIG_NRFX_RRAMC)
zephyr_library_sources(bl_storage_rramc.c)
endif()

if(CONFIG_MCUBOOT_HW_DOWNGRADE_PREVENTION)
  # NB: This option can only be enabled for the MCUBoot image
  zephyr_library_sources(nrf_nv_counters.c)
endif()
