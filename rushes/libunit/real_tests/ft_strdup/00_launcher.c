
#include "../tests.h"

int strdup_launcher(void) {
  t_unit_test *testlist;
  int res;

  testlist = NULL;
  load_test(&testlist, "Basic test", &strdup_basic_test, 0);
  load_test(&testlist, "Basic test", &strdup_null_test, 0);
  res = launch_tests(testlist, "strdup");
  clear_tests(&testlist);
  return (res);
}
