#include "ft_printf.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

// this tells GNU to shut up, we're intentionally testing bad stuff
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-extra-args"
#pragma GCC diagnostic ignored "-Wformat-overflow"

#define TEST_CMP(format, ...)                                                  \
  do {                                                                         \
    printf("'%s'\t", format);                                                  \
    printf("[");                                                               \
    fflush(stdout); /* Force standard printf to print the bracket NOW */       \
    int std_ret = printf(format, ##__VA_ARGS__);                               \
    fflush(stdout); /* Force standard printf to print the format NOW */        \
    printf("]\t[");                                                            \
    fflush(stdout);                                                            \
    int ft_ret = ft_printf(format, ##__VA_ARGS__);                             \
    fflush(stdout);                                                            \
    printf("]\t");                                                             \
    if (std_ret != ft_ret) {                                                   \
      printf("\033[0;31mFAIL\033[0m: std returned %d, ft returned %d\n",       \
             std_ret, ft_ret);                                                 \
    } else {                                                                   \
      printf("\033[0;32mPASS\033[0m\n");                                       \
    }                                                                          \
    assert(std_ret == ft_ret);                                                 \
  } while (0)

// MANDATORY TESTS

void test_chars_and_strings() {
  printf("=== TESTING %%c and %%s ===\n");
  TEST_CMP("%c", 'A');
  TEST_CMP("%c", '0');
  TEST_CMP("%c", '\n');
  TEST_CMP("%s", "Hello 42!");
  TEST_CMP("%s", "");
  TEST_CMP("%s", (char *)NULL);
}

void test_pointers() {
  printf("=== TESTING %%p ===\n");
  int x = 42;
  void *ptr = &x;
  TEST_CMP("%p", ptr);
  TEST_CMP("%p", NULL);
}

void test_decimals() {
  printf("=== TESTING %%d and %%i ===\n");
  TEST_CMP("%d", 42);
  TEST_CMP("%d", -42);
  TEST_CMP("%d", 0);
  TEST_CMP("%d", INT_MAX);
  TEST_CMP("%d", INT_MIN);
  TEST_CMP("%i", 2147483647);
  TEST_CMP("%i", (int)-2147483648);
}

void test_unsigned_and_hex() {
  printf("=== TESTING %%u, %%x, %%X ===\n");
  TEST_CMP("%u", 42);
  TEST_CMP("%u", 0);
  TEST_CMP("%u", UINT_MAX);

  TEST_CMP("%x", 42);
  TEST_CMP("%x", 0);
  TEST_CMP("%x", UINT_MAX);

  TEST_CMP("%X", 42);
  TEST_CMP("%X", 0);
  TEST_CMP("%X", UINT_MAX);
}

void test_percent() {
  printf("=== TESTING %%%% ===\n");
  TEST_CMP("%%");
  TEST_CMP("%%%%%%");
  TEST_CMP("100%% real");
}

// BONUS TESTS

void test_bonus_hash_space_plus() {
  printf("=== TESTING BONUS: #, space, + ===\n");
  // # flag with hex
  TEST_CMP("%#x", 42);
  TEST_CMP("%#X", 42);
  TEST_CMP("%#x", 0); // standard printf prints "0", not "0x0"

  // + flag with numbers
  TEST_CMP("%+d", 42);
  TEST_CMP("%+d", -42);
  TEST_CMP("%+i", 0);

  // space flag with numbers
  TEST_CMP("% d", 42);
  TEST_CMP("% d", -42);
  TEST_CMP("% i", 0);

  // combinations
  TEST_CMP("%+ d", 42); // + usually overrides space
}

void test_bonus_width_and_precision() {
  printf("=== TESTING BONUS: -, 0, ., width ===\n");
  // Width
  TEST_CMP("%5d", 42);
  TEST_CMP("%10s", "42");

  // Minus flag (left justify)
  TEST_CMP("%-5d", 42);
  TEST_CMP("%-10s", "42");

  // Zero flag (zero padding)
  TEST_CMP("%05d", 42);
  TEST_CMP("%010d", -42);

  // Precision
  TEST_CMP("%.5d", 42);
  TEST_CMP("%.3s", "Hello 42!");
  // Special case: printing 0 with 0 precision yields empty string
  TEST_CMP("%.0d", 0);

  // Complex Combinations
  TEST_CMP("%-10.5d", 42);
  TEST_CMP("%08.5d", 42);
  TEST_CMP("%+#10.5x", 42);
}

int main() {
  // Mandatory
  test_chars_and_strings();
  test_pointers();
  test_decimals();
  test_unsigned_and_hex();
  test_percent();

  // Bonus
  test_bonus_hash_space_plus();
  test_bonus_width_and_precision();

  return 0;
}
