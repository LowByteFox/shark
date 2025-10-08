/* SPDX-License-Identifier: Apache-2.0 */
#include <encodings.h>
#include <str.h>

#include <string.h>
#include <stdint.h>
#include <strings.h>

static const char *instrs[] = {
    "mov",
    "add",
    "sub",
    "mul",
    "smul",
    "div",
    "sdiv",
    "rem",
    "srem",
    "and",
    "or",
    "xor",
    NULL
};

uint8_t get_instr_opcode(const struct str instr)
{
    for (uint8_t opcode = 0; instrs[opcode] != NULL; opcode++) {
        if (strncasecmp(instrs[opcode], instr.ptr, instr.len) == 0)
            return opcode;
    }

    return 0xFF;
}

enum encoding_type get_instr_type(const struct str instr)
{
    uint8_t opcode = get_instr_opcode(instr);
    if (opcode == INVALID_OPCODE) return XXX_OP;

    if (opcode >= 1 && opcode <= 11) return MATH_OP;

    return XXX_OP;
}

struct str get_opcode_instr(uint8_t opcode)
{
    size_t nul_opcode = sizeof(instrs) / sizeof(instrs[0]) - 1;

    if (opcode >= nul_opcode) return (struct str) { NULL, 0 };

    return str(instrs[opcode]);
}