#define LUA_CORE

#include "lua.h"
#include "llex.h"
#include "lparser.h"
#include "lzio.h"
#include "lundump.h"

LUAI_FUNC void luaX_init (lua_State *L) {
  UNUSED(L);
}

LUAI_FUNC Closure *luaY_parser(lua_State * L, ZIO *, Mbuffer *, Dyndata *, const char *, int) {
  lua_pushliteral(L,"parser not loaded");
  lua_error(L);
  return NULL;
}

LUAI_FUNC int luaU_dump (lua_State* L, const Proto*, lua_Writer, void*, int) {
  lua_pushliteral(L,"dumper not loaded");
  lua_error(L);
  return 0;
}
