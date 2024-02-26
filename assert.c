#include <uefi.h>

int __assert(_Bool condition, const char *cond, const char *func, int line)
{
  if (!condition) {
    fprintf(stderr, "Assertion failed (%s) %s:%d\n", cond, func, line);
    exit(1);
  }

  return condition;
}