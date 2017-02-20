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
    void impl_poll(lua_State* L) {
      luaL_checkany(L, 1);
      long timeout = luaX_opt_integer<long>(L, 2, -1);

      std::vector<zmq_pollitem_t> items;

      for (int i = 1; ; ++i) {
        zmq_pollitem_t item = { 0, -1, 0, 0 };

        luaX_get_field(L, 1, i);
        if (lua_isnil(L, -1)) {
          lua_pop(L, 1);
          break;
        }

        luaX_get_field(L, -1, "socket");
        if (void* socket = to_socket(L, -1)) {
          item.socket = socket;
          lua_pop(L, 1);
        } else {
          lua_pop(L, 1);
          // luaX_get_field(L, -1, "fd");
          // if (luaX_is_integer(L, -1)) {
          //   item.fd = lua_tointeger(L, -1);
          // }
          // lua_pop(L, 1);
          item.fd = luaX_check_integer_field<int>(L, luaX_abs_index(L, -1), "fd");
        }
        luaX_get_field(L, -1, "events");
        if (luaX_is_integer(L, -1)) {
          item.events = lua_tointeger(L, -1);
        }
        lua_pop(L, 1);
        lua_pop(L, 1);

        items.push_back(item);
      }

      int result = zmq_poll(&items[0], items.size(), timeout);
      if (result == -1) {
        push_error(L);
      } else {
        for (int i = 1; ; ++i) {
          luaX_get_field(L, 1, i);
          if (lua_isnil(L, -1)) {
            lua_pop(L, 1);
            break;
          }
          luaX_set_field(L, -1, "revents", items[i - 1].revents);
          lua_pop(L, 1);
        }
        luaX_push(L, result);
      }
    }
  }

  void initialize_main(lua_State* L) {
    luaX_set_field(L, -1, "poll", impl_poll);
  }
}
