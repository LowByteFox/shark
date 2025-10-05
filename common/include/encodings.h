/* SPDX-License-Identifier: Apache-2.0 */
#ifndef ENCODINGS_H
#define ENCODINGS_H

#include <stdint.h>
#include <str.h>

#define INVALID_OPCODE 0xFF

enum encoding_type {
    MATH_OP,
    XXX_OP
};

struct math_op_00 {
    uint32_t opcode: 6;
    uint32_t bits: 2;
    uint32_t output_reg: 4;
    uint32_t input_reg1: 4;
    uint32_t input_reg2: 4;
    uint32_t unused: 12;
};

struct math_op_01 {
    uint32_t opcode: 6;
    uint32_t bits: 2;
    uint32_t output_reg: 4;
    uint32_t input_reg: 4;
    uint32_t input_imm: 16;
};

struct math_op_11 {
    uint32_t opcode: 6;
    uint32_t bits: 2;
    uint32_t output_reg: 4;
    uint32_t input_imm1: 10;
    uint32_t input_imm2: 10;
};

uint8_t get_instr_opcode(const struct str instr);
enum encoding_type get_instr_type(const struct str instr);

#endif