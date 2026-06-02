
#include "../tests.h"

int atoi_launcher(void) {
  t_unit_test *testlist;
  int res;

  testlist = NULL;
  load_test(&testlist, "Basic test", &atoi_basic_test, 0);
  load_test(&testlist, "INT MAX test", &atoi_int_max_test, 0);
  load_test(&testlist, "INT MIN test", &atoi_int_min_test, 0);
  load_test(&testlist, "NULL test", &atoi_null_test, 0);
  res = launch_tests(testlist, "atoi");
  clear_tests(&testlist);
  return (res);
}
