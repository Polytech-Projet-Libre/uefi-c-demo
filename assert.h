#ifndef H_ASSERT
#define H_ASSERT

#define assert(condition) __assert(condition, #condition, &__func__[0], __LINE__)

int __assert(_Bool condition, const char *cond, const char *func, int line);

#endif
