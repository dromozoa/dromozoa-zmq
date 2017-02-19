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
      check_message_handle(L, 1)->~message_handle();
    }

    void impl_tostring(lua_State* L) {
      zmq_msg_t* message = check_message(L, 1);
      lua_pushlstring(L, static_cast<const char*>(zmq_msg_data(message)), zmq_msg_size(message));
    }

    void impl_call(lua_State* L) {
      luaX_new<message_handle>(L);
      luaX_set_metatable(L, "dromozoa.zmq.message");
    }

    void impl_init(lua_State* L) {
      if (check_message_handle(L, 1)->init() == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_init_size(lua_State* L) {
      size_t size = luaX_check_integer<size_t>(L, 2);
      if (check_message_handle(L, 1)->init_size(size) == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_init_data(lua_State* L) {
      size_t size = 0;
      const char* data = luaL_checklstring(L, 2, &size);
      if (check_message_handle(L, 1)->init_data(data, size) == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_close(lua_State* L) {
      if (check_message_handle(L, 1)->close() == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_recv(lua_State* L) {
      int flags = luaX_opt_integer<int>(L, 3, 0);
      int result = zmq_msg_recv(check_message(L, 1), check_socket(L, 2), flags);
      if (result == -1) {
        push_error(L);
      } else {
        luaX_push(L, result);
      }
    }

    void impl_send(lua_State* L) {
      int flags = luaX_opt_integer<int>(L, 3, 0);
      int result = zmq_msg_send(check_message(L, 1), check_socket(L, 2), flags);
      if (result == -1) {
        push_error(L);
      } else {
        luaX_push(L, result);
      }
    }
  }

  message_handle* check_message_handle(lua_State* L, int arg) {
    return luaX_check_udata<message_handle>(L, arg, "dromozoa.zmq.message");
  }

  zmq_msg_t* check_message(lua_State* L, int arg) {
    return check_message_handle(L, arg)->get();
  }

  void initialize_message(lua_State* L) {
    lua_newtable(L);
    {
      luaL_newmetatable(L, "dromozoa.zmq.message");
      lua_pushvalue(L, -2);
      luaX_set_field(L, -2, "__index");
      luaX_set_field(L, -1, "__gc", impl_gc);
      luaX_set_field(L, -1, "__tostring", impl_tostring);
      lua_pop(L, 1);

      luaX_set_metafield(L, -1, "__call", impl_call);
      luaX_set_field(L, -1, "init", impl_init);
      luaX_set_field(L, -1, "init_size", impl_init_size);
      luaX_set_field(L, -1, "init_data", impl_init_data);
      luaX_set_field(L, -1, "close", impl_close);
      luaX_set_field(L, -1, "recv", impl_recv);
      luaX_set_field(L, -1, "send", impl_send);
    }
    luaX_set_field(L, -2, "message");
  }
}
