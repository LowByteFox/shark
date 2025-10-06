/* SPDX-License-Identifier: Apache-2.0 */
#ifndef PARSER_H
#define PARSER_H

#include <diagnostics.h>
#include <str.h>
#include <ir.h>
#include <arena.h>
#include <stddef.h>
#include <tokens.h>

struct parser {
    struct tokens tokens;
    struct diagnostics diag;
    size_t off;
};

void tokenize(struct parser *self, const char *code, const char *filename);
struct ir_builder parse(struct parser *self);

#endif