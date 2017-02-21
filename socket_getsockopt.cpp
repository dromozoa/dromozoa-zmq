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

#include <errno.h>
#include <stdint.h>

#include <vector>

#include "common.hpp"
#include "symbols.hpp"

namespace dromozoa {
  namespace {
    template <class T>
    inline int getsockopt_integer(lua_State* L, int name) {
      T value = 0;
      size_t size = sizeof(value);
      int result = zmq_getsockopt(check_socket(L, 1), name, &value, &size);
      if (result != -1) {
        luaX_push(L, value);
      }
      return result;
    }

    int getsockopt_string(lua_State* L, int name) {
      size_t size = luaX_opt_integer<size_t>(L, 3, 256);
      std::vector<char> value(size);
      int result = zmq_getsockopt(check_socket(L, 1), name, &value[0], &size);
      if (result != -1) {
        luaX_push(L, &value[0]);
      }
      return result;
    }

    int getsockopt_curve(lua_State* L, int name) {
      size_t size = luaX_opt_integer<size_t>(L, 3, 41);
      int result = -1;
      if (size == 32) {
        char value[32] = { 0 };
        result = zmq_getsockopt(check_socket(L, 1), name, value, &size);
        if (result != -1) {
          lua_pushlstring(L, value, 32);
        }
      } else if (size == 41) {
        char value[41] = { 0 };
        result = zmq_getsockopt(check_socket(L, 1), name, value, &size);
        if (result != -1) {
          lua_pushlstring(L, value, 40);
        }
      } else {
        errno = EINVAL;
      }
      return result;
    }

    void impl_getsockopt(lua_State* L) {
      int name = luaX_check_integer<int>(L, 2);
      int result = -1;
      switch (getsockopt_option(name)) {
        case getsockopt_option_int:
          result = getsockopt_integer<int>(L, name);
          break;
        case getsockopt_option_int64_t:
          result = getsockopt_integer<int64_t>(L, name);
          break;
        case getsockopt_option_uint64_t:
          result = getsockopt_integer<uint64_t>(L, name);
          break;
        case getsockopt_option_character_string:
          result = getsockopt_string(L, name);
          break;
        case setsockopt_option_binary_data_or_Z85_text_string:
          result = getsockopt_curve(L, name);
          break;
        default:
          errno = EINVAL;
      }
      if (result == -1) {
        push_error(L);
      }
    }
  }

  void initialize_socket_getsockopt(lua_State* L) {
    luaX_set_field(L, -1, "getsockopt", impl_getsockopt);
  }
}
