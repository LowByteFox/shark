/* SPDX-License-Identifier: Apache-2.0 */
#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <loc.h>
#include <str.h>
#include <stdbool.h>

struct diagnostics {
    struct str filename, source, line;
    struct source_loc location;
    int length;
    bool errored;
};

struct diagnostics diag_init(struct str filename, struct str source);
void diag_update(struct diagnostics *diag, int offset, int len);

void diag_err(struct diagnostics *diag, const char *fmt, ...);
void diag_warn(struct diagnostics *diag, const char *fmt, ...);

#endif