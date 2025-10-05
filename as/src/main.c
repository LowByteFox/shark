/* SPDX-License-Identifier: Apache-2.0 */
#include <ir.h>
#include <assemble.h>
#include <encodings.h>
#include <stdint.h>
#include <stdio.h>
#include <tokens.h>
#include <parser.h>
#include <stddef.h>
#include <stdlib.h>

int main()
{
    struct parser p = { 0 };
    uint32_t res;

    tokenize(&p, "main:\n"
                            "  add R0, #1, #1      ; Adds 1 + 1 to R0");

    struct ir_builder ir = parse(&p);
    struct ir_iter i = ir_iter(&ir);
    /* skip label */
    ir_next(&i);

    if ((res = assemble_instruction(&i)) != INVALID_ASSEMBLY) {
        printf("Assembled!\n");
        struct math_op_11 *decompiled = (void*) &res;
        printf("%d %d %d %d %d\n", decompiled->opcode, decompiled->bits, decompiled->output_reg, decompiled->input_imm1, decompiled->input_imm2);
    }

    free(p.tokens.ptr);
    return 0;
}