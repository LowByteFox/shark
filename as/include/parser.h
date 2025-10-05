/* SPDX-License-Identifier: Apache-2.0 */
#ifndef PARSER_H
#define PARSER_H

#include <ir.h>
#include <arena.h>
#include <stddef.h>
#include <tokens.h>

struct parser {
    struct tokens tokens;
    size_t off;
};

void tokenize(struct parser *self, const char *code);
struct ir_builder parse(struct parser *self);

#endif