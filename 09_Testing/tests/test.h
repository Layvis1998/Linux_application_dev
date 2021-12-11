#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>

static jmp_buf escape;

static void test_abort(void)
{
    longjmp(escape, 1);
}

#define BUF_ABORT test_abort()
#include "buf.h"

#if _WIN32
#  define C_RED(s)     s
#  define C_GREEN(s)   s
#else
#  define C_RED(s)     "\033[31;1m" s "\033[0m"
#  define C_GREEN(s)   "\033[32;1m" s "\033[0m"
#endif

#define TEST(s, x) \
  do \
  { \
    if (x) \
    { \
      printf(C_GREEN("PASS") " %s\n", s); \
      count_pass++; \
    } \
    else \
    { \
      printf(C_RED("FAIL") " %s\n", s); \
      count_fail++; \
    } \
  } while (0)

static uint32_t pcg32(uint64_t *s)
{
  uint64_t m = 0x5851f42d4c957f2d;
  uint64_t a = 0x8b260b70b8e98891;
  uint64_t p = *s;
  uint32_t x = ((p >> 18) ^ p) >> 27;
  uint32_t r = p >> 59;
  *s = p * m + a;
  return (x >> r) | (x << (-r & 31u));
}

static unsigned long bench(uint64_t *rg)
{
  unsigned long r = 0;
  uint32_t n = 1000000 + pcg32(rg) % 4000000;
  float *buffer = 0;
  for (uint32_t i = 0; i < n; i++)
    buf_push(buffer, pcg32(rg) / (double)UINT32_MAX);
  float threshold = pcg32(rg) / (double)UINT32_MAX;

  for (uint32_t i = 0; i < n; i++)
    r = r + (buffer[i] > threshold);

  buf_free(buffer);
  return r;
}

#ifdef _WIN32
  #include <windows.h>

uint64_t uepoch()
{
  FILETIME file;
  GetSystemTimeAsFileTime(&file);
  uint64_t var = file.dwHighDateTime;
  var = var << 32;
  var |= file.dwLowDateTime;
  var = var / 10;
  var = var - UINT64_C(11644473600000000);
  return var;
}

#else
  #include <sys/time.h>

uint64_t uepoch()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return 1000000LL * tv.tv_sec + tv.tv_usec;
}
#endif
