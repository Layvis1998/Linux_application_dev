#include "tests.h"

int main()
{
  float *ptr = 0;
  int count_pass = 0;
  int count_fail = 0;
  TEST("capacity init", buf_capacity(ptr) == 0);
  TEST("size init", buf_size(ptr) == 0);
  buf_push(ptr, 1.3f);
  TEST("size 1", buf_size(ptr) == 1);
  TEST("value", ptr[0] == (float)1.3f);
  buf_clear(ptr);
  TEST("clear", buf_size(ptr) == 0);
  TEST("clear not-free", (ptr != 0) );
  buf_free(ptr);
  TEST("free", ptr == 0);

  /* Clearing an NULL pointer is a no-op */
  buf_clear(ptr);
  TEST("clear empty", buf_size(ptr) == 0);
  TEST("clear no-op", ptr == 0);
  return !(count_fail == 0);
}
