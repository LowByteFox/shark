/* SPDX-License-Identifier: Apache-2.0 */
#include "str.h"
#include <ctype.h>
#include <threads.h>
#include <tokens.h>
#include <lexer.h>

#include <stddef.h>

static char next_char(struct lexer *l);
static char peek_char(struct lexer *l);
static void lex_reg(struct lexer *l, struct token *o);
static void lex_sym(struct lexer *l, struct token *o);

struct token lexer_next(struct lexer *l)
{
    struct token ret = { 0 };
    char c = 0;

    size_t off = l->off;

start:
    c = next_char(l);

    switch (c) {
    case ';':
        while ((c = next_char(l)) != '\n' && c != 0);
        goto start;
    case ',':
        ret.type = COMMA;
        ret.view = str_view(l->buffer, off, l->off);
        ret.offset = off;
        break;
    case 'R':
        lex_reg(l, &ret);
        break;
    case '#':
        lex_reg(l, &ret);
        ret.type = CONSTANT;
    default:
        if (isspace(c)) goto start;
        if (isalpha(c)) lex_sym(l, &ret);
    }

    return ret;
}


static char next_char(struct lexer *l)
{
    if (l->off == l->buffer.len) return 0;

    return l->buffer.ptr[l->off++];
}

static char peek_char(struct lexer *l)
{
    if (l->off == l->buffer.len) return 0;

    return l->buffer.ptr[l->off];
}

static void lex_reg(struct lexer *l, struct token *o)
{
    o->type = REGISTER;
    o->offset = l->off - 1;

    while (isdigit(peek_char(l))) { next_char(l); }

    o->view = str_view(l->buffer, o->offset, l->off);
}

static void lex_sym(struct lexer *l, struct token *o)
{
    o->type = SYMBOL;
    o->offset = l->off - 1;

    while (isalnum(peek_char(l))) { next_char(l); }
    if (peek_char(l) == ':') { next_char(l); o->type = LABEL_TOK; }

    o->view = str_view(l->buffer, o->offset, l->off);
}