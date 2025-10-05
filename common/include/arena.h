/* SPDX-License-Identifier: Apache-2.0 */
#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

struct arena {
    void *data; /* mmap'd block */
    struct arena *next;
    size_t mmaped_size, pos;
};

void arena_init(struct arena *self);
void* arena_alloc(struct arena *self, size_t size);
void arena_free(struct arena *self);

/* used for iterative purposes */
void *arena_iter(struct arena *self);

#endif