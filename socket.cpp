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

#include <vector>

#include "common.hpp"

namespace dromozoa {
  namespace {
    void impl_gc(lua_State* L) {
      check_socket_handle(L, 1)->~socket_handle();
    }

    void impl_close(lua_State* L) {
      if (check_socket_handle(L, 1)->close() == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_bind(lua_State* L) {
      const char* endpoint = luaL_checkstring(L, 2);
      if (zmq_bind(check_socket(L, 1), endpoint) == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_connect(lua_State* L) {
      const char* endpoint = luaL_checkstring(L, 2);
      if (zmq_connect(check_socket(L, 1), endpoint) == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_recv(lua_State* L) {
      size_t size = luaX_check_integer<size_t>(L, 2);
      int flags = luaX_opt_integer<int>(L, 3, 0);
      std::vector<char> buffer(size);
      int result = zmq_recv(check_socket(L, 1), &buffer[0], size, flags);
      if (result == -1) {
        push_error(L);
      } else {
        lua_pushlstring(L, &buffer[0], result);
      }
    }

    void impl_send(lua_State* L) {
      size_t size = 0;
      const char* buffer = luaL_checklstring(L, 2, &size);
      size_t i = luaX_opt_range_i(L, 3, size);
      size_t j = luaX_opt_range_j(L, 4, size);
      if (j < i) {
        j = i;
      }
      int flags = luaX_opt_integer<int>(L, 5, 0);
      int result = zmq_send(check_socket(L, 1), buffer + i, j - i, flags);
      if (result == -1) {
        push_error(L);
      } else {
        luaX_push(L, result);
      }
    }
  }

  socket_handle* check_socket_handle(lua_State* L, int arg) {
    return luaX_check_udata<socket_handle>(L, arg, "dromozoa.zmq.socket");
  }

  void* check_socket(lua_State* L, int arg) {
    return check_socket_handle(L, arg)->get();
  }

  void* to_socket(lua_State* L, int index) {
    if (socket_handle* self = luaX_to_udata<socket_handle>(L, index, "dromozoa.zmq.socket")) {
      return self->get();
    } else {
      return 0;
    }
  }

  void new_socket(lua_State* L, void* handle) {
    luaX_new<socket_handle>(L, handle);
    luaX_set_metatable(L, "dromozoa.zmq.socket");
  }

  void initialize_socket_getsockopt(lua_State* L);
  void initialize_socket_setsockopt(lua_State* L);

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
      luaX_set_field(L, -1, "recv", impl_recv);
      luaX_set_field(L, -1, "send", impl_send);

      initialize_socket_getsockopt(L);
      initialize_socket_setsockopt(L);
    }
    luaX_set_field(L, -2, "socket");
  }
}
