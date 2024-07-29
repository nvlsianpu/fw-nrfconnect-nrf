/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef BL_STORAGE_INTERNAL_H_
#define BL_STORAGE_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup bl_storage Bootloader storage (protected data).
 * @{
 */

const struct monotonic_counter *get_counter_struct(uint16_t description);

/** This library implements monotonic counters where each time the counter
 *  is increased, a new slot is written.
 *  This way, the counter can be updated without erase. This is, among other things,
 *  necessary so the counter can be used in the OTP section of the UICR
 *  (available on e.g. nRF91 and nRF53).
 */
struct monotonic_counter {
	/* Counter description. What the counter is used for. See
	 * BL_MONOTONIC_COUNTERS_DESC_x.
	 */
	uint32_t description;
	/* Number of entries in 'counter_slots' list. */
	uint32_t num_counter_slots;
#ifdef CONFIG_NRFX_NVMC
	uint16_t counter_slots[1];
#elif defined(CONFIG_NRFX_RRAMC)
	uint32_t counter_slots[1];
#endif
};

/** The second data structure in the provision page. It has unknown length since
 *  'counters' is repeated. Note that each entry in counters also has unknown
 *  length, and each entry can have different length from the others, so the
 *  entries beyond the first cannot be accessed via array indices.
 */
struct counter_collection {
	uint32_t type; /* Must be "monotonic counter". */
	uint32_t num_counters; /* Number of entries in 'counters' list. */
	struct monotonic_counter counters[1];
};

/** Function for getting the current value and the first free slot.
 *
 * @param[in]   counter_desc  Counter description
 * @param[out]  counter_value The current value of the requested counter.
 * @param[out]  free_slot     Pointer to the first free slot. Can be NULL.
 *
 * @retval 0        Success
 * @retval -EINVAL  Cannot find counters with description @p counter_desc or the pointer to
 *                  @p counter_value is NULL.
 */
#ifdef CONFIG_NRFX_NVMC
int get_monotonic_counter(uint16_t counter_desc, uint16_t *counter_value);
#elif defined(CONFIG_NRFX_RRAMC)
int get_monotonic_counter(uint16_t counter_desc, uint32_t *counter_value);
#endif

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* BL_STORAGE_INTERNAL_H_ */
