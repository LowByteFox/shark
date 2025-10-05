/* SPDX-License-Identifier: Apache-2.0 */
#include <arena.h>
#include <config.h>

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#if HAVE_SYS_MMAN_H
#include <sys/mman.h>
#endif

#define align(x, align) (((x) + (align) - 1) & ~((align) - 1))

void arena_init(struct arena *self)
{
    memset(self, 0, sizeof(*self));

#if HAVE_SYS_MMAN_H
    self->data = mmap(NULL, PAGE_SIZE + sizeof(*self), PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (self->data == MAP_FAILED) return;
#else
    self->data = malloc(PAGE_SIZE + sizeof(*self));

    if (self->data == NULL) return;
#endif

    self->mmaped_size = PAGE_SIZE + sizeof(*self);
    self->pos += sizeof(*self);
}

void* arena_alloc(struct arena *self, size_t size)
{
    size = align(size, sizeof(void*));

    if (self->next != NULL && self->pos + size > self->mmaped_size)
        return arena_alloc(self->next, size);

    uint8_t *ptr = self->data;

    if (self->pos + size > self->mmaped_size) {
        self->next = self->data;

        arena_init(self->next);

        if (self->next->data == NULL) return NULL;

        return arena_alloc(self->next, size);
    }

    ptr += self->pos;
    memset(ptr, 0, size);
    self->pos += size;
    return ptr;
}

void arena_free(struct arena *self)
{
    if (self->next != NULL)
        arena_free(self->next);

#if HAVE_SYS_MMAN_H
    munmap(self->data, self->mmaped_size);
#else
    free(self->data);
#endif

    self->data = NULL;
    self->next = NULL;
    self->mmaped_size = 0;
    self->pos = 0;
}

void *arena_iter(struct arena *self)
{
    uint8_t *ptr = self->data;
    return ptr + sizeof(*self);
}