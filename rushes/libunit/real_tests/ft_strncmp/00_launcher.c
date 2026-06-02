
#include "../tests.h"

int strncmp_launcher(void) {
  t_unit_test *testlist;
  int res;

  testlist = NULL;
  load_test(&testlist, "Basic test", &strncmp_basic_test, 0);
  load_test(&testlist, "Len test", &strncmp_len_test, 0);
  load_test(&testlist, "High len test", &strncmp_high_len_test, 0);
  res = launch_tests(testlist, "ft_strncmp");
  clear_tests(&testlist);
  return (res);
}
