/* SPDX-License-Identifier: Apache-2.0 */
#include "err.h"
#include <config.h>
#include <stdint.h>
#include <stdlib.h>

#if HAVE_SYS_STAT_H && HAVE_UNISTD_H && HAVE_FCNTL_H
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#if HAVE_LIBGEN_H
#include <libgen.h>
#endif

char *read_entire_file(const char *path)
{
#if HAVE_SYS_STAT_H && HAVE_UNISTD_H && HAVE_FCNTL_H
    struct stat s;
    if (stat(path, &s) == -1) {
        warn("stat: ");
        return NULL;
    }

    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        warn("open: ");
        return NULL;
    }

    char *buffer = malloc(s.st_size);

    if (read(fd, buffer, s.st_size) == -1) {
        warn("read: ");
        free(buffer);
        close(fd);
        return NULL;
    }

    close(fd);
    return buffer;
#else
#error "Not supported yet!"
#endif
}

void write_entire_file(const char *path, uint8_t *buffer, size_t len)
{
#if HAVE_UNISTD_H && HAVE_FCNTL_H

    int fd = open(path, O_WRONLY | O_CREAT, 0666);

    if (fd == -1) {
        warn("open: ");
        return;
    }

    if (write(fd, buffer, len) == -1) {
        warn("write: ");
        close(fd);
        return;
    }

    close(fd);
#else
#error "Not supported yet!"
#endif
}

char *file_basename(char *path)
{
#if HAVE_LIBGEN_H
    return basename(path);
#else
#error "Not supported yet!"
#endif
}