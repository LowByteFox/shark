/* SPDX-License-Identifier: Apache-2.0 */
#include <ir.h>
#include <lexer.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <tokens.h>
#include <parser.h>

static struct token *peek(struct parser *self);
static struct token *consume(struct parser *self);
static void emit_instr_args(struct parser *self, struct ir_builder *builder);
static uint32_t str_to_reg(struct str view);
static uint32_t str_to_imm(struct str view);

void tokenize(struct parser *self, const char *code)
{
    struct token t = { 0 };
    struct lexer l = { 0 };
    l.buffer = str(code);

    while ((t = lexer_next(&l)).type != END) {
        tokens_push(&self->tokens, t);
    }
}

struct ir_builder parse(struct parser *self)
{
    struct ir_builder builder;
    ir_init(&builder);

    struct token *current = consume(self);
    while (current != NULL && current->type != END) {
        switch (current->type) {
        case LABEL_TOK:
            ir_emit(&builder, IR_LABEL);
            current->view.len--; /* remove : */
            ir_label(&builder, current->view);
            break;
        case SYMBOL:
            ir_emit(&builder, IR_INSTR);
            ir_instr(&builder, current->view);
            emit_instr_args(self, &builder);
            break;
        default:
            /* ! ERR */
            break;
        }

        current = consume(self);
    }

    return builder;
}


static struct token *consume(struct parser *self)
{
    if (self->off >= self->tokens.len) return NULL;
    
    return self->tokens.ptr + (self->off++);
}

static struct token *peek(struct parser *self)
{
    if (self->off >= self->tokens.len) return NULL;
    
    return self->tokens.ptr + self->off;
}

static void emit_instr_args(struct parser *self, struct ir_builder *builder)
{
    struct token *current = peek(self);

    while (current != NULL && (current->type == REGISTER || current->type == CONSTANT)) {
        consume(self);
        if (current->type == REGISTER) {
            ir_emit(builder, IR_REG);
            ir_reg(builder, str_to_reg(current->view));
        } else {
            ir_emit(builder, IR_IMM);
            ir_imm(builder, str_to_imm(current->view));
        }

        current = peek(self);
        if (current == NULL || current->type != COMMA) break;
        consume(self);
        current = peek(self);
    }
}

static uint32_t str_to_reg(struct str view)
{
    char buffer[view.len];
    memset(buffer, 0, view.len);
    memcpy(buffer, view.ptr + 1, view.len);

    /* ! check for register size */
    return atoi(buffer);
}

static uint32_t str_to_imm(struct str view)
{
    char buffer[view.len];
    memset(buffer, 0, view.len);
    memcpy(buffer, view.ptr + 1, view.len);

    return atoi(buffer);
}
