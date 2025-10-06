/* SPDX-License-Identifier: Apache-2.0 */
#include "loc.h"
#include "str.h"
#include <stdarg.h>
#include <diagnostics.h>
#include <stdio.h>


struct diagnostics diag_init(struct str filename, struct str source)
{
    struct diagnostics diag = { 0 };
    diag.filename = filename;
    diag.source = source;

    return diag;
}

void diag_update(struct diagnostics *diag, int offset, int len)
{
    diag->location = get_loc(diag->source, offset);
    diag->line = get_line(diag->source, offset);
    diag->length = len - 1;
}

void diag_err(struct diagnostics *diag, const char *fmt, ...)
{
    fprintf(stderr, "%.*s:%d:%d: \e[1;31merror\e[0m: ",
        (int) diag->filename.len, diag->filename.ptr, diag->location.line, diag->location.column);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "%4d | %.*s\n", diag->location.line, (int) diag->line.len, diag->line.ptr);
    fprintf(stderr, "     | \e[1;31m");
    fprintf(stderr, "%*c", diag->location.column, '^');

    for (int i = 0; i < diag->length; i++) fputc('~', stderr);
    fputs("\e[0m\n", stderr);
}

void diag_warn(struct diagnostics *diag, const char *fmt, ...)
{
    fprintf(stderr, "%.*s:%d:%d: \e[1;33mwarn\e[0m: ",
        (int) diag->filename.len, diag->filename.ptr, diag->location.line, diag->location.column);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "%4d | %.*s\n", diag->location.line, (int) diag->line.len, diag->line.ptr);
    fprintf(stderr, "     | \e[1;33m");
    fprintf(stderr, "%*c", diag->location.column, '^');

    for (int i = 0; i < diag->length; i++) fputc('~', stderr);
    fputs("\e[0m\n", stderr);
}
