/* SPDX-License-Identifier: Apache-2.0 */
#include "str.h"
#include <encodings.h>
#include <disassemble.h>
#include <stdint.h>
#include <stdio.h>

static void dissasemble_math(uint32_t *instr);

bool disassemble_instruction(uint32_t *instr)
{
    struct bare_op *bare = (void*) instr;
    struct str name = get_opcode_instr(bare->opcode);
    enum encoding_type enc_t = get_instr_type(name);

    switch (enc_t) {
    case MATH_OP:
        printf("%.*s ", (int) name.len, name.ptr);
        dissasemble_math(instr);
        break;
    case XXX_OP:
        printf("Invalid instruction!\n");
        return true;
    }

    return false;
}

static void dissasemble_math(uint32_t *instr)
{
    struct bare_op *bare = (void*) instr;
    bool swap = true;

    switch (bare->bits) {
    case 0b00: {
        struct math_op_00 *dis = (void*) instr;
        printf("R%d, R%d, R%d\n", dis->output_reg, dis->input_reg1, dis->input_reg2);
        break;
    }
    case 0b01:
        swap = false;
    case 0b10: {
        struct math_op_01 *dis = (void*) instr;
        if (swap)
            printf("R%d, #%d, R%d\n", dis->output_reg, dis->input_imm, dis->input_reg);
        else
            printf("R%d, R%d, #%d\n", dis->output_reg, dis->input_reg, dis->input_imm);
        break;
    }
    case 0b11: {
        struct math_op_11 *dis = (void*) instr;
        printf("R%d, #%d, #%d\n", dis->output_reg, dis->input_imm1, dis->input_imm2);
        break;
    }
    }
}