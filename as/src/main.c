/* SPDX-License-Identifier: Apache-2.0 */
#include "assemble.h"
#include <parser.h>
#include <err.h>
#include <program.h>
#include <file.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    setprogname(argv[0]);

    if (argc != 3)
        die("Expected 3 arguments, got: %d!", argc);

    char *infile = read_entire_file(argv[1], NULL);
    struct parser par = { 0 };
    tokenize(&par, infile, file_basename(argv[1]));
    struct assembler compiler = { 0 };
    assembler_init(&compiler, &par);
    if (par.diag.errored)
        goto end;

    struct instructions compiled = assemble(&compiler);

    write_entire_file(argv[2], (void*) compiled.ptr, compiled.len * sizeof(instruction));

    free(compiled.ptr);
end:
    free(par.tokens.ptr);
    free(infile);
    return 0;
}
