/* SPDX-License-Identifier: Apache-2.0 */
#include <arena.h>
#include <assert.h>
#include <ir.h>
#include <stdint.h>
#include <stdio.h>

void ir_init(struct ir_builder *builder)
{
    arena_init(&builder->arena);
}

void ir_emit(struct ir_builder *builder, enum ir_type type)
{
    builder->current = arena_alloc(&builder->arena, sizeof(struct ir_op));
    builder->current->kind = type;
    builder->current->offset = -1;
}

void ir_offset(struct ir_builder *builder, int offset, int len)
{
    assert(builder->current != NULL && "Forgot to call `ir_emit`?");
    builder->current->offset = offset;
    builder->current->len = len;
}

/* fill in data */
void ir_label(struct ir_builder *builder, struct str label)
{
    assert(builder->current != NULL && "Forgot to call `ir_emit`?");
    assert(builder->current->kind == IR_LABEL && "Expected IR_LABEL");
    builder->current->label = label;
    builder->current = NULL;
}

void ir_instr(struct ir_builder *builder, struct str label)
{
    assert(builder->current != NULL && "Forgot to call `ir_emit`?");
    assert(builder->current->kind == IR_INSTR && "Expected IR_LABEL");
    builder->current->label = label;
    builder->current = NULL;
}

void ir_reg(struct ir_builder *builder, uint32_t reg)
{
    assert(builder->current != NULL && "Forgot to call `ir_emit`?");
    assert(builder->current->kind == IR_REG && "Expected IR_REG");
    builder->current->reg = reg;
    builder->current = NULL;
}

void ir_imm(struct ir_builder *builder, uint32_t imm)
{
    assert(builder->current != NULL && "Forgot to call `ir_emit`?");
    assert(builder->current->kind == IR_IMM && "Expected IR_IMM");
    builder->current->imm = imm;
    builder->current = NULL;
}

struct ir_iter ir_iter(struct ir_builder *builder)
{
    return (struct ir_iter) {
        .current_arena = &builder->arena,
        .ref = arena_iter(&builder->arena),
    };
}

struct ir_op *ir_next(struct ir_iter *iter)
{
    uint8_t *it = iter->current_arena->data;
    uint8_t *end = it + iter->current_arena->pos;

    if ((uintptr_t) iter->ref >= (uintptr_t) end) {
        if (iter->current_arena->next == NULL)
            return NULL;

        iter->current_arena = iter->current_arena->next;
        iter->ref = arena_iter(iter->current_arena);
    }

    return iter->ref++;
}

void ir_describe(struct ir_op *op)
{
    switch (op->kind) {
    case IR_LABEL:
        printf("IR_LABEL = %.*s\n", (int) op->label.len, op->label.ptr);
        break;
    case IR_INSTR:
        printf("IR_INSTR = %.*s\n", (int) op->label.len, op->label.ptr);
        break;
    case IR_REG:
        printf("IR_REG = R%d\n", op->reg);
        break;
    case IR_IMM:
        printf("IR_IMM = #%d\n", op->reg);
        break;
    }
}