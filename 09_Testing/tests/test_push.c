#include "tests.h"

int main(int argc, char **argv)
{
  volatile int count_pass = 0;
  volatile int count_fail = 0;
  long *ai = 0;
  for (int i = 0; i < 10000; i++)
    buf_push(ai, i);
  TEST("size 10000", buf_size(ai) == 10000);
  int match = 0;
  for (int i = 0; i < (int)(buf_size(ai)); i++)
    match = match + (ai[i] == i);
  TEST("match 10000", match == 10000);
  buf_free(ai);

  return (count_fail != 0);
}
