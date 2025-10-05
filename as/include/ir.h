/* SPDX-License-Identifier: Apache-2.0 */
#ifndef IR_H
#define IR_H

#include <arena.h>
#include <stdint.h>
#include <str.h>

enum ir_type {
    IR_LABEL,
    IR_INSTR,
    IR_REG,
    IR_IMM,
};

struct ir_op {
    enum ir_type kind;
    union {
        struct str label; /* label/instr */
        uint32_t reg; 
        uint32_t imm;
    };
};

struct ir_builder {
    struct arena arena;
    struct ir_op *current; /* to be populated */
};

struct ir_iter {
    struct arena *current_arena;
    struct ir_op *ref;
};

void ir_init(struct ir_builder *builder);

void ir_emit(struct ir_builder *builder, enum ir_type type);
void ir_label(struct ir_builder *builder, struct str label);
void ir_instr(struct ir_builder *builder, struct str label);
void ir_reg(struct ir_builder *builder, uint32_t reg);
void ir_imm(struct ir_builder *builder, uint32_t imm);

struct ir_iter ir_iter(struct ir_builder *builder);
struct ir_op *ir_next(struct ir_iter *iter);

void ir_describe(struct ir_op *op);

#endif