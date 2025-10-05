/* SPDX-License-Identifier: Apache-2.0 */
#ifndef ARR_H
#define ARR_H

#undef CAP
#define CAP 8

#define _ARR(type, name)                            \
struct name {                                       \
    type *ptr;                                      \
    size_t len, capacity;                           \
};                                                  \
void name##_push(struct name *self, type item);

#define _ARR_IMPL(type, name)                                                   \
void name##_push(struct name *self, type item) {                                \
    if (self->len == self->capacity) {                                          \
        if (self->capacity == 0) self->capacity = CAP;                          \
        self->ptr = realloc(self->ptr, sizeof(type) * (self->capacity *= 2));   \
    }                                                                           \
    self->ptr[self->len++] = item;                                              \
}

#endif