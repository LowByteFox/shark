/* SPDX-License-Identifier: Apache-2.0 */
#include <program.h>
#include <config.h>

#if HAVE_LIBGEN_H
#include <libgen.h>
#endif

static const char *p;

void setprogname(const char *prog)
{
#if HAVE_LIBGEN_H
    p = basename((void*) prog);
#else
    p = prog;
#endif
}

const char *getprogname()
{
    return p;
}
