#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  //panic("Not implemented");
  va_list ap;
  va_start(ap, fmt);
  
  for (const char *p = fmt; *p; p++)
  {
    if (*p == '%')
    {
      p++;
      if (*p == 's')
        {
          const char* s = va_arg(ap, char*);
          putstr(s);
        }
      else if (*p == 'd')
      {
        int a = va_arg(ap, int);
        bool isN = false;
        if (a < 0)
        {
          isN = true;
          a = -a;
        }
        
        int len = 1;
        int64_t t = 10;
        while (a >= t)
        {
          len++;
          t *= 10;
        }

        char x[len];
        for (size_t i = len; i > 0; i--)
        {
          x[i-1] = a % 10;
          a /= 10;
        }
        if (isN)
        {
          putch('-');
        }
        
        for (size_t i = 0; i < len; i++)
        {
          putch(x[i]+'0');
        }
      }
      else
      {
        panic("E R R O R!");
      }
    }
    else
      putch(*p);
  }
  va_end(ap);
  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  panic("Not implemented");
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
