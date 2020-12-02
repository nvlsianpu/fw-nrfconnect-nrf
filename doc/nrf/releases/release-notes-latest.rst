.. _ncs_release_notes_latest:

Changes in |NCS| v1.4.99
########################

.. contents::
   :local:
   :depth: 2

The most relevant changes that are present on the master branch of the |NCS|, as compared to the latest release, are tracked in this file.

.. note::
    This file is a work in progress and might not cover all relevant changes.

Changelog
*********

The following sections provide detailed lists of changes by component.

nRF5
====

The following changes are relevant for the nRF52 and nRF53 Series.

nRF5340 SoC
-----------

* Updated:

  * ``bl_boot`` library - Disabled clock interrupts before booting the application.
    This change fixes an issue where the :ref:`bootloader` sample would not be able to boot a Zephyr application on the nRF5340 SoC.

Thread
------

* Added:

  * Development support for the nRF5340 in single-protocol configuration for the :ref:`ot_cli_sample`, :ref:`coap_client_sample`, and :ref:`coap_server_sample` samples.

* Optimized ROM and RAM used by Thread samples.

Common
======

The following changes are relevant for all device families.

Crypto
------

* Added:

  * nrf_cc3xx_platform v0.9.5, with the following highlights:

    * Added correct TRNG characterization values for nRF5340 devices.

    See the :ref:`crypto_changelog_nrf_cc3xx_platform` for detailed information.
  * nrf_cc3xx_mbedcrypto version v0.9.5, with the following highlights:

    * Built to match the nrf_cc3xx_platform v0.9.5 including correct TRNG characterization values for nRF5340 devices.

    See the :ref:`crypto_changelog_nrf_cc3xx_mbedcrypto` for detailed information.

* Updated:

  * Rewrote the :ref:`nrfxlib:nrf_security`'s library stripping mechanism to not use the POST_BUILD option in a custom build rule.
    The library stripping mechanism was non-functional in certain versions of SEGGER Embedded Studio Nordic Edition.

MCUboot
=======

sdk-mcuboot
-----------

The MCUboot fork in |NCS| contains all commits from the upstream MCUboot repository up to and including ``c74c551ed6``, plus some |NCS| specific additions.

* Bootloader:

  * Added hardening against hardware level fault injection and timing attacks.
    See ``CONFIG_BOOT_FIH_PROFILE_HIGH`` and similar Kconfig options.
  * Introduced abstract crypto primitives to simplify porting.
  * Added ram-load upgrade mode (not enabled for Zephyr yet).
  * Renamed single-image mode to single-slot mode.
    See the ``CONFIG_SINGLE_APPLICATION_SLOT`` option.
  * Added a patch for turning off cache for Cortex-M7 before chain-loading.
  * Fixed an issue that caused HW stack protection to catch the chain-loaded application during its early initialization.
  * Added reset of Cortex SPLIM registers before boot.
  * Fixed a build issue that occurred if the CONF_FILE contained multiple file paths instead of a single file path.
  * Added watchdog feed on nRF devices.
    See the ``CONFIG_BOOT_WATCHDOG_FEED`` option.
  * Removed the ``flash_area_read_is_empty()`` port implementation function.
  * Updated the ARM core configuration to only be initialized when selected by the user.
    See the ``CONFIG_MCUBOOT_CLEANUP_ARM_CORE`` option.
  * Allowed the final data chunk in the image to be unaligned in the serial-recovery protocol.

* Image tool:

  * Updated the tool to print an image digest during verification.
  * Added a possibility to set a confirm flag for HEX files as well.
  * Updated the usage of ``--confirm`` to imply ``--pad``.
  * Fixed the argument handling of ``custom_tlvs``.

sdk-nrfxlib
===========

See the changelog for each library in the :doc:`nrfxlib documentation <nrfxlib:README>` for the most current information.

sdk-mcumgr
==========

The mcumgr library fork in |NCS| contains all commits from the upstream mcumgr
up to and including snapshot ``a3d5117b08``.

* Changes:

  * Fixed issue with devices mcuboot version 1.6.0 and earlier where power outage
    during erase of corrupted image in slot-1 could lead to device not being able to boot
    nor update with mcumgr returning error code 6 (MGMT_ERR_EBADSTATE).
  * Added support for invoking shell commands (shell management) with mcumgr command line.
  * Removed broken log management support.

Zephyr
======

sdk-zephyr
----------

.. NOTE TO MAINTAINERS: The latest Zephyr commit appears in multiple places; make sure you update them all.

The Zephyr fork in |NCS| contains all commits from the upstream Zephyr repository up to and including ``7a3b253ced``, plus some |NCS| specific additions.

For a complete list of upstream Zephyr commits incorporated into |NCS| since the most recent release, run the following command from the :file:`ncs/zephyr` repository (after running ``west update``):

.. code-block:: none

   git log --oneline 7a3b253ced ^v2.3.0-rc1-ncs1

For a complete list of |NCS| specific commits, run:

.. code-block:: none

   git log --oneline manifest-rev ^7a3b253ced

The current |NCS| release is based on Zephyr 2.4.0.
See the :ref:`Zephyr 2.4.0 release notes <zephyr:zephyr_2.4>` for a list of changes.

For the list of the most recent additions specific to |NCS|, see :ref:`ncs_release_notes_140`.

* Drivers and sensors:

  * Flash:

    * Added support for nRF53 Series SoCs in the nRF QSPI NOR flash driver (nrf_qspi_nor).

  * USB:

    * Made the USB DFU class compatible with the target configuration that does not have a secondary image slot.
    * Added support for using USB DFU within MCUboot with single application slot mode.


* Libraries/subsystems:

  * Settings:

    * Removed SETTINGS_USE_BASE64 support, which has been deprecated for more than two releases.

  * Storage:

    * :ref:`flash_map_api`: Added an API to get the value of an erased byte in the flash_area.
      See :c:func:`flash_area_erased_val`.
    * :ref:`stream_flash`: Eliminated the usage of the flash API internals.


  * File systems:

    * Enabled FCB to work with non-0xff erase value flash.
    * Enabled FCB to work with non-0xff erase value flash.
    * Added ``CONFIG_FS_MOUNT_FLAG_NO_FORMAT`` flag to FATFS Kconfig options, that removes formatting capabilities from FAT FS;
      the option also prevents unformatted devices to be formatted to FAT FS on mount attempt.
    * Added support for ``fs_mount()`` flags: ``FS_MOUNT_FLAG_READ_ONLY`` and ``FS_MOUNT_FLAG_NO_FORMAT``.
    * The runtime check of FS API of a driver interface will not be perfromed when ``CONFIG_NO_RUNTIME_CHECKS`` option is enabled.
