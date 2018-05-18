// Copyright (C) 2017,2018 Tomoyuki Fujimori <moyu@dromozoa.com>
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
      luaX_push(L, luaX_string_reference(static_cast<const char*>(zmq_msg_data(message)), zmq_msg_size(message)));
    }

    void impl_call(lua_State* L) {
      message_handle_impl* impl = 0;
      if (luaX_string_reference source = luaX_to_string(L, 2)) {
        size_t i = luaX_opt_range_i(L, 3, source.size());
        size_t j = luaX_opt_range_j(L, 4, source.size());
        if (j < i) {
          j = i;
        }
        impl = message_handle::init_data(source.data() + i, j - i);
      } else {
        impl = message_handle::init();
      }
      if (impl) {
        luaX_new<message_handle>(L, impl);
        luaX_set_metatable(L, "dromozoa.zmq.message");
      } else {
        push_error(L);
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

    void impl_recv(lua_State* L) {
      int flags = luaX_opt_integer<int>(L, 3, 0);
      int result = zmq_msg_recv(check_message(L, 1), check_socket(L, 2), flags);
      if (result == -1) {
        push_error(L);
      } else {
        luaX_push(L, result);
      }
    }

    void impl_close(lua_State* L) {
      if (check_message_handle(L, 1)->close() == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

    void impl_more(lua_State* L) {
      luaX_push(L, zmq_msg_more(check_message(L, 1)));
    }

    void impl_get(lua_State* L) {
      int property = luaX_check_integer<int>(L, 2);
      int result = zmq_msg_get(check_message(L, 1), property);
      if (result == -1) {
        push_error(L);
      } else {
        luaX_push(L, result);
      }
    }

    void impl_set(lua_State* L) {
      int property = luaX_check_integer<int>(L, 2);
      int value = luaX_check_integer<int>(L, 3);
      if (zmq_msg_set(check_message(L, 1), property, value) == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

#ifdef HAVE_ZMQ_MSG_GETS
    void impl_gets(lua_State* L) {
      const char* property = luaL_checkstring(L, 2);
      if (const char* result = zmq_msg_gets(check_message(L, 1), property)) {
        luaX_push(L, result);
      } else {
        push_error(L);
      }
    }
#endif
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
      luaX_set_field(L, -1, "send", impl_send);
      luaX_set_field(L, -1, "recv", impl_recv);
      luaX_set_field(L, -1, "close", impl_close);
      luaX_set_field(L, -1, "more", impl_more);
      luaX_set_field(L, -1, "get", impl_get);
      luaX_set_field(L, -1, "set", impl_set);
#ifdef HAVE_ZMQ_MSG_GETS
      luaX_set_field(L, -1, "gets", impl_gets);
#endif
    }
    luaX_set_field(L, -2, "message");
  }
}
