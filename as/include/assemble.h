/* SPDX-License-Identifier: Apache-2.0 */
#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include <parser.h>
#include <arr.h>
#include <diagnostics.h>
#include <ir.h>
#include <stddef.h>
#include <stdint.h>

#define INVALID_ASSEMBLY 0xFFFFFFFF

typedef uint32_t instruction;

struct assembler {
    struct ir_builder ir;
    struct ir_iter iter;
    struct diagnostics diag;
    size_t off; /* offset in bytes from the start of the assembly */
};

_ARR(instruction, instructions);

void assembler_init(struct assembler *self, struct parser *parser);
struct instructions assemble(struct assembler *self);

#endif