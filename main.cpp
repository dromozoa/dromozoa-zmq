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

#include <stdint.h>

#include <vector>

#include "common.hpp"

namespace dromozoa {
  namespace {
    void impl_has(lua_State* L) {
      const char* capability = luaL_checkstring(L, 1);
      luaX_push(L, zmq_has(capability));
    }

    void impl_poll(lua_State* L) {
      luaL_checkany(L, 1);
      long timeout = luaX_opt_integer<long>(L, 2, -1);

      std::vector<zmq_pollitem_t> items;
      for (int i = 1; ; ++i) {
        zmq_pollitem_t item = { 0, -1, 0, 0 };
        if (luaX_get_field(L, 1, i) == LUA_TNIL) {
          lua_pop(L, 1);
          break;
        }
        luaX_get_field(L, -1, "socket");
        if (void* socket = to_socket(L, -1)) {
          item.socket = socket;
          lua_pop(L, 1);
        } else {
          lua_pop(L, 1);
          item.fd = luaX_check_integer_field<int>(L, -1, "fd");
        }
        item.events = luaX_check_integer_field<int>(L, -1, "events");
        lua_pop(L, 1);
        items.push_back(item);
      }

      int result = zmq_poll(&items[0], items.size(), timeout);
      if (result == -1) {
        push_error(L);
      } else {
        for (int i = 1; ; ++i) {
          if (luaX_get_field(L, 1, i) == LUA_TNIL) {
            lua_pop(L, 1);
            break;
          }
          luaX_set_field(L, -1, "revents", items[i - 1].revents);
          lua_pop(L, 1);
        }
        luaX_push(L, result);
        lua_pushvalue(L, 1);
      }
    }

    void impl_z85_decode(lua_State* L) {
      size_t size = 0;
      const char* data = luaL_checklstring(L, 1, &size);
      std::vector<uint8_t> buffer(size * 4 / 5);
      if (const uint8_t* result = zmq_z85_decode(&buffer[0], data)) {
        lua_pushlstring(L, reinterpret_cast<const char*>(result), buffer.size());
      } else {
        push_error(L);
      }
    }

    void impl_z85_encode(lua_State* L) {
      size_t size = 0;
      const char* data = luaL_checklstring(L, 1, &size);
      std::vector<char> buffer(size * 5 / 4 + 1);
      if (const char* result = zmq_z85_encode(&buffer[0], reinterpret_cast<const uint8_t*>(data), size)) {
        luaX_push(L, result);
      } else {
        push_error(L);
      }
    }
  }

  void initialize_main(lua_State* L) {
    luaX_set_field(L, -1, "has", impl_has);
    luaX_set_field(L, -1, "poll", impl_poll);
    luaX_set_field(L, -1, "z85_decode", impl_z85_decode);
    luaX_set_field(L, -1, "z85_encode", impl_z85_encode);
  }
}
