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

char * test_new() {
  DArray * array = DArray_create(sizeof(int), 100);

  int * value = DArray_new(array);

  mu_assert(value != NULL, "Failed to make new element.");

  DArray_free(value);
  DArray_implode(array);

  return NULL;
}

char * test_set_and_get() {
  // Step 1: Create the array
  DArray * array = DArray_create(sizeof(int), 100);

  // Step 2: Allocate memory for array elements
  int * value1 = DArray_new(array);
  int * value2 = DArray_new(array);

  // Step 3: Dereference the pointers and assign values to the array
  *value1 = 100;
  *value2 = 200;

  // Step 4: Map array elements to actual index positions in the array
  DArray_set(array, 0, value1);
  DArray_set(array, 1, value2);

  // Step 5: Index into the array to retrieve elements. These variables
  //         will be stored on the stack, so we don't need to free them.
  int * result1 = DArray_get(array, 0);
  int * result2 = DArray_get(array, 1);

  mu_assert(result1 == value1, "Expected mem address to match");
  mu_assert(result2 == value2, "Expected mem address to match");

  mu_assert(*value1 == 100, "Expected value to equal 100");
  mu_assert(*value2 == 200, "Expected value to equal 200");

  // Free memory used by array elements, and the array itself
  DArray_implode(array);

  return NULL;
}

char * test_remove() {
  DArray * array = DArray_create(sizeof(int), 100);

  int * val1 = DArray_new(array);
  int * val2 = DArray_new(array);

  *val1 = 100;
  *val2 = 200;

  DArray_set(array, 0, val1);
  DArray_set(array, 1, val2);

  int * val_check = DArray_remove(array, 0);
  mu_assert(val_check != NULL, "Should not get NULL");
  mu_assert(*val_check == *val1, "Should get the first value");
  mu_assert(DArray_get(array, 0) == NULL, "Should be gone");
  DArray_free(val_check);

  val_check = DArray_remove(array, 1);
  mu_assert(val_check != NULL, "Should not get NULL");
  mu_assert(*val_check == *val2, "Should get the second value");
  mu_assert(DArray_get(array, 1) == NULL, "Should be gone");
  DArray_free(val_check);

  DArray_implode(array);

  return NULL;
}

char * test_expand_contract() {
  DArray * array = DArray_create(sizeof(int), 100);

  int * val1 = DArray_new(array);
  int * val2 = DArray_new(array);

  *val1 = 100;
  *val2 = 200;

  DArray_set(array, 0, val1);
  DArray_set(array, 1, val2);

  int old_max = array->max;

  DArray_expand(array);
  mu_assert((unsigned int)array->max == old_max + array->expand_rate,
    "Wrong size after expand.");

  DArray_contract(array);
  mu_assert((unsigned int)array->max == array->expand_rate + 1,
    "Should stay at the expand rate at least.");

  // Run it a second time
  DArray_contract(array);
  mu_assert((unsigned int)array->max == array->expand_rate + 1,
    "Should stay at the expand rate at least.");

  DArray_implode(array);

  return NULL;
}

char * test_push_pop() {
  DArray * array = DArray_create(sizeof(int), 100);

  for (int i = 0; i < 1000; i++) {
    int * val = DArray_new(array);
    *val = i * 333;
    DArray_push(array, val);
  }

  mu_assert(array->max == 1300, "Wrong max size.");

  for (int i = 999; i >= 0; i--) {
    int * val = DArray_pop(array);
    mu_assert(val != NULL, "Shouldn't get a NULL value");
    mu_assert(*val == i * 333, "Wrong value.");
  }

  DArray_implode(array);

  return NULL;
}

char * all_tests() {
  mu_suite_start();

  mu_run_test(test_it_works);
  mu_run_test(test_create);
  mu_run_test(test_new);
  mu_run_test(test_set_and_get);
  mu_run_test(test_remove);
  mu_run_test(test_expand_contract);
  mu_run_test(test_push_pop);

  return NULL;
}

RUN_TESTS(all_tests);
