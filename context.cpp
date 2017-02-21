// Copyright (C) 2017 Tomoyuki Fujimori <moyu@dromozoa.com>
//
// This file is part of dromozoa-zmq.
//
// dromozoa-zmq is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// dromozoa-zmq is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with dromozoa-zmq.  If not, see <http://www.gnu.org/licenses/>.

#include "common.hpp"

namespace dromozoa {
  namespace {
    void impl_gc(lua_State* L) {
      check_context_handle(L, 1)->~context_handle();
    }

    void impl_call(lua_State* L) {
      if (void* handle = zmq_ctx_new()) {
        luaX_new<context_handle>(L, handle);
        luaX_set_metatable(L, "dromozoa.zmq.context");
      } else {
        push_error(L);
      }
    }

    void impl_term(lua_State* L) {
      if (check_context_handle(L, 1)->term() == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_shutdown(lua_State* L) {
      if (zmq_ctx_shutdown(check_context(L, 1)) == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_socket(lua_State* L) {
      int type = luaX_check_integer<int>(L, 2);
      if (void* handle = zmq_socket(check_context(L, 1), type)) {
        new_socket(L, handle);
      } else {
        push_error(L);
      }
    }

    void impl_get(lua_State* L) {
      int name = luaX_check_integer<int>(L, 2);
      int result = zmq_ctx_get(check_context(L, 1), name);
      if (result == -1) {
        push_error(L);
      } else {
        luaX_push(L, result);
      }
    }

    void impl_set(lua_State* L) {
      int name = luaX_check_integer<int>(L, 2);
      int value = luaX_check_integer<int>(L, 3);
      if (zmq_ctx_set(check_context(L, 1), name, value) == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }
  }

  context_handle* check_context_handle(lua_State* L, int arg) {
    return luaX_check_udata<context_handle>(L, arg, "dromozoa.zmq.context");
  }

  void* check_context(lua_State* L, int arg) {
    return check_context_handle(L, arg)->get();
  }

  void initialize_context(lua_State* L) {
    lua_newtable(L);
    {
      luaL_newmetatable(L, "dromozoa.zmq.context");
      lua_pushvalue(L, -2);
      luaX_set_field(L, -2, "__index");
      luaX_set_field(L, -1, "__gc", impl_gc);
      lua_pop(L, 1);

      luaX_set_metafield(L, -1, "__call", impl_call);
      luaX_set_field(L, -1, "term", impl_term);
      luaX_set_field(L, -1, "shutdown", impl_shutdown);
      luaX_set_field(L, -1, "socket", impl_socket);
      luaX_set_field(L, -1, "get", impl_get);
      luaX_set_field(L, -1, "set", impl_set);
    }
    luaX_set_field(L, -2, "context");
  }
}
