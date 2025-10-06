/* SPDX-License-Identifier: Apache-2.0 */
#ifndef ERR_H
#define ERR_H

void warn(const char *fmt, ...);
void err(const char *fmt, ...);
void die(const char *fmt, ...);

#endif