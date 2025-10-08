/* SPDX-License-Identifier: Apache-2.0 */
#include <disassemble.h>
#include <file.h>
#include <program.h>
#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    setprogname(argv[0]);

    if (argc != 2)
        die("Expected 2 arguments, got: %d!", argc);

    int size = 0;
    char *infile = read_entire_file(argv[1], &size);

    if (size % 4 != 0)
        die("input file is not 4 byte aligned!");

    for (int i = 0; i < size; i += 4) {
        printf("0x%08x\t", i);
        if (disassemble_instruction((uint32_t*) (infile + i)))
            break;
    }

    free(infile);
    return 0;
}