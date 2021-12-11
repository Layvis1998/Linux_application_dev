#include "tests.h"

int main()
{
  int count_pass = 0;
  int count_fail = 0;
  float *ptr = 0;
  buf_push(ptr, 1.1);
  buf_push(ptr, 1.2);
  buf_push(ptr, 1.3);
  buf_push(ptr, 1.4);
  TEST("size 4", buf_size(ptr) == 4);
  TEST("pop 3", buf_pop(ptr) == (float)1.4f);
  buf_trunc(ptr, 3);
  TEST("size 3", buf_size(ptr) == 3);
  TEST("pop 2", buf_pop(ptr) == (float)1.3f);
  TEST("pop 1", buf_pop(ptr) == (float)1.2f);
  TEST("pop 0", buf_pop(ptr) == (float)1.1f);
  TEST("size 0 (pop)", buf_size(ptr) == 0);
  buf_free(ptr);
  return count_fail != 0;
}
