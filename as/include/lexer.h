/* SPDX-License-Identifier: Apache-2.0 */
#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <str.h>
#include <tokens.h>

struct lexer {
    struct str buffer;
    size_t off;
};

struct token lexer_next(struct lexer *l);

#endif