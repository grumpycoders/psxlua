#ifndef llibc_h
#define llibc_h

#include <stddef.h>

char * luaA_strchr(const char * s, int c);
int luaA_strcmp(const char * s1, const char * s2);
size_t luaA_strlen(const char * s);
const char *luaA_strpbrk(const char *s, const char *accepted);
char *luaA_strstr(const char *s1, const char *s2);
int luaA_strspn(const char *str, const char *cset);
char * luaA_strcpy(char * s1, const char * s2);
#define luaA_memcpy __builtin_memcpy
int luaA_memcmp(const void *s1, const void *s2, size_t n);
const void * luaA_memchr(const void * s_, int c, size_t n);

#ifdef LUA_TARGET_PSX
int luaI_sprintf(char *str, const char *format, ...);
void luaI_free(void *);
void *luaI_realloc(void *, size_t);
#else
#include <stdio.h>
#include <stdlib.h>
#define luaI_sprintf sprintf
#define luaI_free free
#define luaI_realloc realloc
#endif

#endif
