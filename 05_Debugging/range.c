#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
  int32_t start = 0;
  int32_t end = 1;
  int32_t step = 1;
  if (argc == 1)
  {
    printf("%s",
      "usage: range [start] [end] [step]\n"
      "start: range start\n"
      "end: range end\n"
      "step: range step\n"
      "output depends on the number of arguments as follows:\n"
      "    1 arg: [0, 1, ..., end-1]\n"
      "    2 args: [start, start+1, ..., end-1]\n"
      "    3 args: [start, start+step, ..., end-1]\n"
       );
    return 0;
  }
  else if (argc == 2)
    sscanf(argv[1], "%d", &end);
  else
  {
    sscanf(argv[1], "%d", &start);
    sscanf(argv[2], "%d", &end);
    if (argc == 4) 
      sscanf(argv[3], "%d", &step);
    if (!step || start < end && step < 0)
      return 0;
  }
  
  for (int32_t i = start; i < end; i += step)
    printf("%d\n", i);
}
