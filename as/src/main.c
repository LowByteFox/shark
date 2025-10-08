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
                            "  add R0, R0, R0", "<input>");

    struct assembler compiler = { 0 };
    assembler_init(&compiler, &p);

    struct instructions compiled = assemble(&compiler);

    for (int i = 0; i < compiled.len; i++) {
        struct math_op_11 *decompiled = (void*) (compiled.ptr + i);
        printf("%d %d\n", decompiled->opcode, decompiled->bits);
    }

    free(compiled.ptr);
    free(p.tokens.ptr);
    return 0;
}