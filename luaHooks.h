#pragma once

extern "C" {
#include "lstate.h"
#include <lauxlib.h>
int luaB_print(lua_State* L);
}

typedef void(*f_parser_type)(lua_State* L, __int64** a2);
typedef void(*lua_pushinteger_type)(lua_State* L, lua_Integer n);

typedef void(*lua_setglobal_type)(lua_State* L, const char* name);
typedef int(*lua_pcallk_type)(lua_State* L, int nargs, int nresults, int errfunc, lua_KContext ctx, lua_KFunction k);
typedef int(*luaL_loadstring_type)(lua_State* L, const char* s);
typedef const char*(*lua_pushstring_type)(lua_State* L, const char* s);
typedef void(*lua_pushcclosure_type)(lua_State* L, lua_CFunction fn, int n);
typedef const char* (*lua_tolstring_type)(lua_State* L, int idx, size_t* len);
typedef int(*lua_rawgeti_type)(lua_State* L, int idx, lua_Integer n);

extern lua_setglobal_type lua_setglobal_sb;
extern lua_pcallk_type lua_pcallk_sb;
extern luaL_loadstring_type luaL_loadstring_sb;
extern lua_pushstring_type lua_pushstring_sb;
extern lua_pushcclosure_type lua_pushcclosure_sb;
extern lua_tolstring_type lua_tolstring_sb;
extern lua_rawgeti_type lua_rawgeti_sb;

void initLuaHook();