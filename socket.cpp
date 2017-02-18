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
      check_socket_handle(L, 1)->~socket_handle();
    }

    void impl_close(lua_State* L) {
      if (check_socket_handle(L, 1)->close() == 0) {
        luaX_push_success(L);
      } else {
        push_error(L);
      }
    }

    void impl_bind(lua_State* L) {
      if (zmq_bind(check_socket(L, 1), luaL_checkstring(L, 2)) == 0) {
        luaX_push_success(L);
      } else {
        push_error(L);
      }
    }

    void impl_connect(lua_State* L) {
      if (zmq_connect(check_socket(L, 1), luaL_checkstring(L, 2)) == 0) {
        luaX_push_success(L);
      } else {
        push_error(L);
      }
    }
  }

  socket_handle* check_socket_handle(lua_State* L, int arg) {
    return luaX_check_udata<socket_handle>(L, arg, "dromozoa.zmq.socket");
  }

  void* check_socket(lua_State* L, int arg) {
    return check_socket_handle(L, arg)->get();
  }

  void new_socket(lua_State* L, void* handle) {
    luaX_new<socket_handle>(L, handle);
    luaX_set_metatable(L, "dromozoa.zmq.socket");
  }

  void initialize_socket(lua_State* L) {
    lua_newtable(L);
    {
      luaL_newmetatable(L, "dromozoa.zmq.socket");
      lua_pushvalue(L, -2);
      luaX_set_field(L, -2, "__index");
      luaX_set_field(L, -1, "__gc", impl_gc);
      lua_pop(L, 1);

      luaX_set_field(L, -1, "close", impl_close);
      luaX_set_field(L, -1, "bind", impl_bind);
      luaX_set_field(L, -1, "connect", impl_connect);
    }
    luaX_set_field(L, -2, "socket");
  }
}
