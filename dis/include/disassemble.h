/* SPDX-License-Identifier: Apache-2.0 */
#ifndef DISASSEMBLE_H
#define DISASSEMBLE_H

#include <stdint.h>
#include <stdbool.h>

bool disassemble_instruction(uint32_t *instr);

#endif