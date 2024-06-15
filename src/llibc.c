#include <limits.h>
#include <stddef.h>

#include "llibc.h"

char *luaA_strchr(const char *s, int c) {
  char b;
  while ((b = *s)) {
    if (b == c) {
      return (char *)s;
    }
    s++;
  }

  return NULL;
}

int luaA_strcmp(const char *s1, const char *s2) {
  int c1, c2;
  while (1) {
    if (((c1 = *s1++) != (c2 = *s2++)) || !c1 || !c2) {
      break;
    }
  }
  return c1 - c2;
}

size_t luaA_strlen(const char *s) {
  size_t r = 0;

  while (*s++) {
    r++;
  }

  return r;
}

const char *luaA_strpbrk(const char *s, const char *accepted) {
  char c;
  while ((c = *s)) {
    if (luaA_strchr(accepted, c))
      return s;
    s++;
  }
  return NULL;
}

static int lstrncmp(const char *s1, const char *s2, size_t n) {
  int c1, c2;
  while (n--) {
    if (((c1 = *s1++) != (c2 = *s2++)) || !c1 || !c2) {
      return c1 - c2;
    }
  }

  return 0;
}

char *luaA_strstr(const char *s1, const char *s2) {
  size_t l = luaA_strlen(s2);

  while (*s1) {
    if (!lstrncmp(s1, s2, l)) {
      return (char *)s1;
    }
    s1++;
  }

  return NULL;
}

int luaA_memcmp(const void *s1_, const void *s2_, size_t n) {
  unsigned char *s1 = (unsigned char *)s1_;
  const unsigned char *s2 = (unsigned char *)s2_;
  size_t i;

  for (i = 0; i < n; i++, s1++, s2++) {
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }
  }

  return 0;
}

int luaA_strspn(const char *str, const char *cset) {
  int r = 0;
  while (str) {
    if (!luaA_strchr(cset, *str++))
      return r;
    r++;
  }
  return r;
}

const void *luaA_memchr(const void *s_, int c, size_t n) {
  const unsigned char *s = (unsigned char *)s_;
  size_t i;

  for (i = 0; i < n; i++, s++) {
    if (*s == c) {
      return s;
    }
  }

  return NULL;
}

char *luaA_strcpy(char *s1, const char *s2) {
  char *r = s1;

  while ((*s1++ = *s2++))
    ;

  return r;
}

static const inline int strisspace(char c) {
  return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
         c == '\v';
}

long int luaA_strtol(const char *nptr, char **endptr, int base) {
  if (base < 0 || base == 1 || base >= 37) {
    return 0;
  }

  if ((*nptr == '0') && ((*(nptr + 1) == 'x') || (*(nptr + 1) == 'X'))) {
    if ((base != 0) && (base != 16)) {
      return 0;
    }
    base = 16;
    nptr += 2;
  } else if (*nptr == '0') {
    if ((base != 0) && (base != 8) && (*(nptr + 1) != 0)) {
      return 0;
    }
    base = 8;
    nptr++;
  } else if (base == 0) {
    base = 10;
  }

  int got_something = 0;
  int negative = 0;
  unsigned long int r = 0;

  char c;
  char maxLC = 'a' + (base - 10) - 1;
  char maxUC = 'A' + (base - 10) - 1;

  while ((c = *nptr++)) {
    if (strisspace(c) && !got_something) {
      continue;
    }
    if (((c == '+') || (c == '-')) && !got_something) {
      got_something = 1;
      if (c == '-') {
        negative = 1;
      }
      continue;
    }
    if ((c >= '0') && (c <= '9')) {
      c -= '0';
    } else if ((c >= 'a') && (c <= maxLC)) {
      c -= 'a' - 10;
    } else if ((c >= 'A') && (c <= maxUC)) {
      c -= 'A' - 10;
    } else {
      break;
    }
    if (c >= base) {
      break;
    }
    got_something = 1;
    r *= base;
    r += c;
  }

  if (endptr) {
    *endptr = (char *)nptr - 1;
  }
  return negative ? -r : r;
}

long lua_number2str(char *s, long n) {
  if (n == 0) {
    s[0] = '0';
    s[1] = 0;
    return 1;
  }
  long r = 0;
  if (n < 0) {
    n = -n;
    *s++ = '-';
    r++;
  }
  char out[32];
  char *ptr = out;
  while (n) {
    long digit = n % 10;
    n /= 10;
    *ptr++ = digit + '0';
  }
  while (ptr != out) {
    *s++ = *--ptr;
    r++;
  }
  *s++ = 0;
  return r;
}
