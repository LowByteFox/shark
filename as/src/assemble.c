/* SPDX-License-Identifier: Apache-2.0 */
#include "trunc.h"
#include <assemble.h>
#include <encodings.h>
#include <ir.h>
#include <stdint.h>

typedef uint32_t (*assemble_fn)(struct ir_iter *iter, uint32_t opcode);

static uint32_t assemble_math(struct ir_iter *iter, uint32_t opcode);

static assemble_fn vtable[] = {
    [MATH_OP] = assemble_math
};

uint32_t assemble_instruction(struct ir_iter *iter)
{
    struct ir_op *op = ir_next(iter);

    switch (op->kind) {
    case IR_INSTR: {
        enum encoding_type type = get_instr_type(op->label);
        if (type == INVALID_OPCODE) return INVALID_ASSEMBLY;
        return vtable[type](iter, get_instr_opcode(op->label));
    }
    default:
        /* ! ERR */
        return INVALID_ASSEMBLY;
    }
}

static uint32_t assemble_math(struct ir_iter *iter, uint32_t opcode)
{
    uint32_t encoded;
    struct ir_op *params[3];

    params[0] = ir_next(iter);
    params[1] = ir_next(iter);
    params[2] = ir_next(iter);

    if (params[1]->kind == IR_IMM && params[2]->kind == IR_IMM) {
        struct math_op_11 *res = (void*) &encoded;
        res->opcode = opcode;
        res->bits = 0b11;
        res->output_reg = params[0]->reg;
        res->input_imm1 = trunc_bits(params[1]->imm, 10);
        res->input_imm2 = trunc_bits(params[2]->imm, 10);
        return encoded;
    }

    return INVALID_ASSEMBLY;
}