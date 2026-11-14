/* util.h and util.c define copies of GLIBC and POSIX functions since I'm not
 * allowed to use anything other than ISO LIBC. */

#ifndef UTIL_H
#define UTIL_H

/**
 * @returns NULL on failure
 * @note 'm' is just there so the function has a different name and I'm sure
 * mine is used
 */
char *mstrdup(const char *src);

#endif /* UTIL_H */
