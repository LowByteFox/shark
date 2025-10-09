/* SPDX-License-Identifier: Apache-2.0 */
#include <encodings.h>
#include <cpu.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef void (*emulate_fn)(struct cpu *self, struct bare_op *op);

static struct bare_op inline *fetch_instr(struct cpu *self);
static void emulate_math(struct cpu *self, struct bare_op *op);

static emulate_fn vtable[] = {
    [MATH_OP] = emulate_math
};

void cpuinfo(struct cpu *self)
{
    printf("============ cpu debug ============\n");
    printf("Memory size:\t\t 0x%08lx\n", self->memory_limit);
    printf("Program counter:\t 0x%08lx\n", self->pc);
    printf("============ registers ============\n");
    for (int i = 0; i < REGISTER_COUNT; i++)
        printf("R%d:\t\t\t 0x%08x\n", i, self->registers[i]);
}

void emulate(struct cpu *self)
{
    /* ! there is NO halt, end on 0 opcode */
    struct bare_op *c;

    while ((c = fetch_instr(self))->opcode != 0) {
        struct str name = get_opcode_instr(c->opcode);
        enum encoding_type enc_t = get_instr_type(name);

        vtable[enc_t](self, c);
    }
}

#define _math(opcode, operator, type) case opcode: \
    *(type*) output_reg = ((type) a) operator ((type) b);\
    break;

static void emulate_math(struct cpu *self, struct bare_op *op)
{
    uint32_t a, b;
    bool swap = true;
    uint32_t *output_reg = NULL;

    switch (op->bits) {
    case 0b00: {
        struct math_op_00 *dis = (void*) op;
        output_reg = self->registers + dis->output_reg;
        a = self->registers[dis->input_reg1];
        b = self->registers[dis->input_reg2];
        break;
    }
    case 0b01:
        swap = false;
    case 0b10: {
        struct math_op_01 *dis = (void*) op;
        output_reg = self->registers + dis->output_reg;
        if (swap) {
            a = dis->input_imm;
            b = self->registers[dis->input_reg];
        } else {
            a = self->registers[dis->input_reg];
            b = dis->input_imm;
        }
        break;
    }
    case 0b11: {
        struct math_op_11 *dis = (void*) op;
        output_reg = self->registers + dis->output_reg;
        a = dis->input_imm1;
        b = dis->input_imm2;
        break;
    }
    }

    switch (op->opcode) {
    _math(1, +, uint32_t)
    _math(2, -, uint32_t)
    _math(3, *, uint32_t)
    _math(4, *, int32_t)
    _math(5, /, uint32_t)
    _math(6, /, int32_t)
    _math(7, %, uint32_t)
    _math(8, %, int32_t)
    _math(9, &, uint32_t)
    _math(10, |, uint32_t)
    _math(11, ^, uint32_t)
    }
}

#undef _math

static struct bare_op inline *fetch_instr(struct cpu *self)
{
    return (struct bare_op*) (self->memory + ((self->pc += 4) - 4));
}