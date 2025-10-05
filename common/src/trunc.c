/* SPDX-License-Identifier: Apache-2.0 */
#include <trunc.h>
#include <stdint.h>

uint32_t trunc_bits(uint32_t in, uint8_t nbits)
{
    uint32_t res = 0;

    for (uint8_t i = 0; i <= nbits; i++) {
        res |= in & (1 << i);
    }

    return res;
}