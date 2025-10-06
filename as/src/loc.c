/* SPDX-License-Identifier: Apache-2.0 */

#include "str.h"
#include <loc.h>
#include <stdint.h>

struct source_loc get_loc(struct str code, int offset)
{
    struct source_loc l = { 1, 0 };

    for (; offset >= 0 && code.ptr[offset] != '\n'; offset--) {
        if (code.ptr[offset] != '\n') l.column++;
    }

    for (; offset >= 0; offset--) {
        if (code.ptr[offset] == '\n') l.line++;
    }

    return l;
}

struct str get_line(struct str code, int offset)
{
    int start, end;

    for (; offset >= 0 && code.ptr[offset] != '\n'; offset--);
    offset++;

    start = offset;

    for (; offset < code.len && code.ptr[offset] != '\n'; offset++);

    end = offset;

    return str_view(code, start, end);
}