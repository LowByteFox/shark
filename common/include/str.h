/* SPDX-License-Identifier: Apache-2.0 */
#ifndef STR_H
#define STR_H

#include <stddef.h>

struct str {
    const char *ptr;
    size_t len;
};

struct str str(const char *in);
struct str str_view(struct str in, size_t start, size_t end);

#endif