/* SPDX-License-Identifier: Apache-2.0 */
#include <err.h>
#include <file.h>
#include <program.h>
#include <config.h>
#include <cpu.h>
#include <stdlib.h>
#include <string.h>

#define RAM_SIZE PAGE_SIZE * 4

int main(int argc, char **argv)
{
    /* TODO: Handle resource limits through arguments */
    setprogname(argv[0]);

    if (argc != 2)
        die("Expected 2 arguments, got: %d!", argc);

    struct cpu cpu = { 0 };
    cpu.memory_limit = RAM_SIZE;
    cpu.memory = malloc(RAM_SIZE);

    int size = 0;
    char *infile = read_entire_file(argv[1], &size);

    if (size % 4 != 0)
        die("input file is not 4 byte aligned!");

    /* load image into memory */
    memcpy(cpu.memory, infile, size);
    memset(cpu.memory + size, 0, 4);
    free(infile);

    emulate(&cpu);
    cpuinfo(&cpu);
    free(cpu.memory);
    return 0;
}