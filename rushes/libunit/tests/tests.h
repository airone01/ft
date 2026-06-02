
#ifndef TESTS_H
#define TESTS_H

#include "libunit.h"

// LAUNCHERS
int libunit_launcher(void);

// libunit
int test_ok(void);
int test_ko(void);
int test_sigsegv(void);
int test_sigbus(void);
int test_sigkill(void);
int test_sigabrt(void);
int test_sigfpe(void);
int test_sigpipe(void);
int test_timeout(void);

#endif // !TESTS_H
