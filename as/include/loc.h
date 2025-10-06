/* SPDX-License-Identifier: Apache-2.0 */
#ifndef LOC_H
#define LOC_H

#include <str.h>

#include <stdint.h>

struct source_loc {
    uint32_t line;
    uint32_t column;
};

struct source_loc get_loc(struct str code, int offset);
struct str get_line(struct str code, int offset);

#endif