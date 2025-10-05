/* SPDX-License-Identifier: Apache-2.0 */
#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include <ir.h>
#include <stdint.h>

#define INVALID_ASSEMBLY 0xFFFFFFFF

uint32_t assemble_instruction(struct ir_iter *iter);

#endif