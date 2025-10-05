/* SPDX-License-Identifier: Apache-2.0 */
#include <str.h>
#include <string.h>

struct str str(const char *in)
{
    return (struct str) {
        .ptr = in,
        .len = strlen(in),
    };
}

struct str str_view(struct str in, size_t start, size_t end)
{
    return (struct str) {
        .ptr = in.ptr + start,
        .len = end - start
    };
}