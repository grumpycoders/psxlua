/*
** $Id: lctype.h,v 1.12.1.1 2013/04/12 18:48:47 roberto Exp $
** 'ctype' functions for Lua
** See Copyright Notice in lua.h
*/

#ifndef lctype_h
#define lctype_h

/*
** WARNING: the functions defined here do not necessarily correspond
** to the similar functions in the standard C ctype.h. They are
** optimized for the specific needs of Lua
*/

#if !defined(LUA_USE_CTYPE)

#if 'A' == 65 && '0' == 48
/* ASCII case: can use its own tables; faster and fixed */
#define LUA_USE_CTYPE	0
#else
/* must use standard C ctype */
#define LUA_USE_CTYPE	1
#endif

#endif


#if !LUA_USE_CTYPE	/* { */

#include <limits.h>

#include "llimits.h"


#define ALPHABIT	0
#define DIGITBIT	1
#define PRINTBIT	2
#define SPACEBIT	3
#define XDIGITBIT	4
#define PUNCTBIT	5


#define MASK(B)		(1 << (B))


/*
** add 1 to char to allow index -1 (EOZ)
*/
#define testprop(c,p)	(luai_ctype_[(c)+1] & (p))

/*
** 'lalpha' (Lua alphabetic) and 'lalnum' (Lua alphanumeric) both include '_'
*/
#define lislalpha(c)	testprop(c, MASK(ALPHABIT))
#define lislalnum(c)	testprop(c, (MASK(ALPHABIT) | MASK(DIGITBIT)))
#define lisalpha(c)	(lislalpha((c)) && ((c) != '_'))
#define lisalnum(c)	(lislalnum((c)) && ((c) != '_'))
#define lisdigit(c)	testprop(c, MASK(DIGITBIT))
#define lisspace(c)	testprop(c, MASK(SPACEBIT))
#define lisprint(c)	testprop(c, MASK(PRINTBIT))
#define lisxdigit(c)	testprop(c, MASK(XDIGITBIT))

#define llowerbit ('A' ^ 'a')
#define lislower(c)	(lisalpha((c)) && (((c) & llowerbit) == llowerbit))
#define lisupper(c)	(lisalpha((c)) && (((c) & llowerbit) == 0))

#define lisgraph(c)	(((c) > ' ') && ((c) < 0x7f))
#define liscntrl(c)	(((c) < ' ') || ((c) == 0x7f))

#define lispunct(c)	testprop(c, MASK(PUNCTBIT))

/*
** this 'ltolower' only works for alphabetic characters
*/
#define ltolower(c)	((c) | llowerbit)
#define ltoupper(c)	((c) & ~llowerbit)


/* two more entries for 0 and -1 (EOZ) */
extern const unsigned char luai_ctype_[UCHAR_MAX + 2];


#else			/* }{ */

/*
** use standard C ctypes
*/

#include <ctype.h>


#define lislalpha(c)	(isalpha(c) || (c) == '_')
#define lislalnum(c)	(isalnum(c) || (c) == '_')
#define lisdigit(c)	(isdigit(c))
#define lisspace(c)	(isspace(c))
#define lisprint(c)	(isprint(c))
#define lisxdigit(c)	(isxdigit(c))

#define ltolower(c)	(tolower(c))

#endif			/* } */

#endif

