#ifndef H_ASSERT
#define H_ASSERT

#define assert(condition) __assert(condition, #condition, &__func__[0], __LINE__)

int __assert(_Bool condition, const char *cond, const char *func, int line);

#endif

int __assert(_Bool condition, const char *cond, const char *func, int line)
{
  if (!condition) {
    printf("Assertion failed (%s) %s:%d", cond, func, line);
    exit(1);
  }

  return condition;
}