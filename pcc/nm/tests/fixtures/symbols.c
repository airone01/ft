/* Test fixture with various symbol types for nm testing */

#include <stdio.h>

/* Global initialized variable (D) */
int global_initialized_var = 42;
char global_str[] = "Hello world";

/* Global uninitialized variable / bss (B or C) */
int global_uninitialized_var;
double global_array[100];

/* Static initialized variable (d) */
static int static_initialized_var = 123;
static const char *static_str_ptr = "static string";

/* Static uninitialized variable (b) */
static int static_uninitialized_var;
static char static_buf[256];

/* Read-only data (R or r) */
const int const_read_only_var = 999;
const char const_message[] = "Read-only message";

/* External undefined symbols (U) */
extern void external_function(void);
extern int external_variable;

/* Weak symbol (W / w) */
__attribute__((weak)) void weak_function(void) { printf("weak function\n"); }

__attribute__((weak)) int weak_variable = 7;

/* Static function (t) */
static int static_helper_function(int a, int b) {
  return a + b + static_initialized_var + static_uninitialized_var;
}

/* Global function (T) */
int global_main_entry(void) {
  if (external_variable) {
    external_function();
  }
  return static_helper_function(global_initialized_var, const_read_only_var);
}
