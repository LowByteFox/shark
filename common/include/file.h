/* SPDX-License-Identifier: Apache-2.0 */
#ifndef FILE_H
#define FILE_H

#include <stddef.h>
#include <stdint.h>

char *read_entire_file(const char *path, int *len);
void write_entire_file(const char *path, uint8_t *buffer, size_t len);

char *file_basename(char *path);

#endif