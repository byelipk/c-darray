#include "minunit.h"
#include <darray/darray.h>

char * test_it_works() {
  return NULL;
}

char * test_create() {
  DArray * array = DArray_create(sizeof(int), 100);

  mu_assert(array != NULL, "DArray_create failed.");
  mu_assert(array->contents != NULL, "contents are wrong in darray");
  mu_assert(array->end == 0, "end isn't at the right spot");
  mu_assert(array->max == 100, "end isn't at the right spot");
  mu_assert(array->element_size == sizeof(int), "element size is wrong");

  DArray_implode(array);

  return NULL;
}

char * all_tests() {
  mu_suite_start();

  mu_run_test(test_it_works);
  mu_run_test(test_create);

  return NULL;
}

RUN_TESTS(all_tests);
