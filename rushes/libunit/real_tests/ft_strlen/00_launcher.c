
#include "../tests.h"

int strlen_launcher(void) {
  t_unit_test *testlist;
  int res;

  testlist = NULL;
  load_test(&testlist, "null", &test_null, 0);
  load_test(&testlist, "basic", &test_basic, 0);
  load_test(&testlist, "large", &test_large, 0);
  res = launch_tests(testlist, "strlen");
  clear_tests(&testlist);
  return (res);
}
