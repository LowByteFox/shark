/* SPDX-License-Identifier: Apache-2.0 */
#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>
#include <str.h>
#include <arr.h>

enum token_type {
    END,
    SYMBOL,
    LABEL_TOK,
    CONSTANT,
    REGISTER,
    COMMA
};

struct token {
    enum token_type type;
    struct str view;
    size_t offset;
};

_ARR(struct token, tokens);

#endif