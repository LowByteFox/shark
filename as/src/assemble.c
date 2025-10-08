/* SPDX-License-Identifier: Apache-2.0 */
#include <arr.h>
#include "diagnostics.h"
#include "parser.h"
#include "trunc.h"
#include <assemble.h>
#include <encodings.h>
#include <ir.h>
#include <stdbool.h>
#include <stdint.h>

#include <stdlib.h> /* IWYU pragma: keep */

typedef uint32_t (*assemble_fn)(struct assembler *self, struct ir_op *current);

static uint32_t assemble_instruction(struct assembler *self, struct ir_op *current);
static uint32_t assemble_math(struct assembler *self, struct ir_op *current);

static assemble_fn vtable[] = {
    [MATH_OP] = assemble_math
};

void assembler_init(struct assembler *self, struct parser *parser)
{
    self->diag = parser->diag;
    self->ir = parse(parser);
    self->iter = ir_iter(&self->ir);
}

struct instructions assemble(struct assembler *self)
{
    struct instructions instrs = { 0 };

    struct ir_op *current;

    while ((current = ir_next(&self->iter)) != NULL) {
        if (current->kind == IR_LABEL) {
            /* TODO: Register label and location registration */
        } else if (current->kind == IR_INSTR) {
            instructions_push(&instrs, assemble_instruction(self, current));
        }
    }

    return instrs;
}


static uint32_t assemble_instruction(struct assembler *self, struct ir_op *current)
{
    enum encoding_type type = get_instr_type(current->label);
    if (type == XXX_OP) return INVALID_ASSEMBLY;
    return vtable[type](self, current);
}

static uint32_t assemble_math(struct assembler *self, struct ir_op *current)
{
    uint32_t encoded = INVALID_ASSEMBLY;
    uint32_t opcode = get_instr_opcode(current->label);
    struct ir_op *params[3];
    bool switch_order = false;

    params[0] = ir_next(&self->iter);
    params[1] = ir_next(&self->iter);
    params[2] = ir_next(&self->iter);

    if (params[0] == NULL || params[1] == NULL || params[2] == NULL) {
        diag_update(&self->diag, current->offset, current->len);
        int nargs = params[0] == NULL ? 0 : params[1] == NULL ? 1 : 2;
        diag_err(&self->diag, "Expected 3 argumenets, got: %d\n", nargs);
        return INVALID_ASSEMBLY;
    }

    if (params[0]->kind != IR_REG) {
        diag_update(&self->diag, params[0]->offset, params[0]->len);
        diag_err(&self->diag, "Expected output register, got:\n");
        return INVALID_ASSEMBLY;
    }

    for (int i = 1; i < 3; i++) {
        if (params[i]->kind != IR_REG && params[i]->kind != IR_IMM) {
            diag_update(&self->diag, params[i]->offset, params[i]->len);
            diag_err(&self->diag, "Expected register or immediate, got:\n");
            return INVALID_ASSEMBLY;
        }
    }

    if (params[1]->kind == IR_REG && params[2]->kind == IR_IMM) {
        struct math_op_01 *res;
emit_r_i:
        res = (void*) &encoded;
        res->opcode = opcode;
        res->bits = switch_order ? 0b10 : 0b01;
        res->output_reg = params[0]->reg;
        res->input_reg = params[1]->reg;
        res->input_imm = params[2]->imm;
    } else if (params[1]->kind == IR_IMM && params[2]->kind == IR_REG) {
        switch_order = true;
        goto emit_r_i;
    } else if (params[1]->kind == IR_REG && params[2]->kind == IR_REG) {
        struct math_op_00 *res = (void*) &encoded;
        res->opcode = opcode;
        res->bits = 0b00;
        res->output_reg = params[0]->reg;
        res->input_reg1 = params[1]->reg;
        res->input_reg2 = params[2]->reg;
    } else {
        struct math_op_11 *res = (void*) &encoded;
        res->opcode = opcode;
        res->bits = 0b11;
        res->output_reg = params[0]->reg;
        res->input_imm1 = trunc_bits(params[1]->imm, 10);
        res->input_imm2 = trunc_bits(params[2]->imm, 10);
    } 

    return encoded;
}

_ARR_IMPL(instruction, instructions);