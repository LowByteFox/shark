/* SPDX-License-Identifier: Apache-2.0 */
#ifndef CPU_H
#define CPU_H

#include <stddef.h>
#include <stdint.h>

#define REGISTER_COUNT 16

struct cpu {
    uint32_t registers[REGISTER_COUNT];
    uint8_t *memory;
    size_t memory_limit, pc;
};

void cpuinfo(struct cpu *self);
void emulate(struct cpu *self);

#endif