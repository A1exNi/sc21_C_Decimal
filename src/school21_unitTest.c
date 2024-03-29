#include "test.c"

int main(void) {
  int no_failed = 0;
  Suite *test;
  SRunner *runner;
  test = test_suite();
  runner = srunner_create(test);
  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
