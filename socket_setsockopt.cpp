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

#include <errno.h>
#include <stdint.h>

#include "common.hpp"
#include "symbols.hpp"

namespace dromozoa {
  namespace {
    size_t initialize_curve_key_size_z85() {
      int major = 0;
      int minor = 0;
      int patch = 0;
      zmq_version(&major, &minor, &patch);
      if (major < 4 || (major == 4 && minor < 1)) {
        return 40;
      } else {
        return 41;
      }
    }

    static const size_t curve_key_size_z85 = initialize_curve_key_size_z85();

    template <class T>
    inline int setsockopt_integer(lua_State* L, int name) {
      int value = luaX_check_integer<int>(L, 3);
      return zmq_setsockopt(check_socket(L, 1), name, &value, sizeof(value));
    }

    int setsockopt_string(lua_State* L, int name) {
      if (lua_isnoneornil(L, 3)) {
        return zmq_setsockopt(check_socket(L, 1), name, 0, 0);
      } else {
        luaX_string_reference value = luaX_check_string(L, 3);
        return zmq_setsockopt(check_socket(L, 1), name, value.data(), value.size());
      }
    }

    int setsockopt_curve(lua_State* L, int name) {
      if (lua_isnoneornil(L, 3)) {
        return zmq_setsockopt(check_socket(L, 1), name, 0, 0);
      } else {
        luaX_string_reference value = luaX_check_string(L, 3);
        if (value.size() == 32) {
          return zmq_setsockopt(check_socket(L, 1), name, value.data(), 32);
        } else if (value.size() == 40) {
          return zmq_setsockopt(check_socket(L, 1), name, value.data(), curve_key_size_z85);
        } else {
          errno = EINVAL;
          return -1;
        }
      }
    }

    void impl_setsockopt(lua_State* L) {
      int name = luaX_check_integer<int>(L, 2);
      int result = -1;
      switch (setsockopt_option(name)) {
        case setsockopt_option_int:
          result = setsockopt_integer<int>(L, name);
          break;
        case setsockopt_option_int64_t:
          result = setsockopt_integer<int64_t>(L, name);
          break;
        case setsockopt_option_uint64_t:
          result = setsockopt_integer<uint64_t>(L, name);
          break;
        case setsockopt_option_character_string:
        case setsockopt_option_binary_data:
          result = setsockopt_string(L, name);
          break;
        case setsockopt_option_binary_data_or_Z85_text_string:
          result = setsockopt_curve(L, name);
          break;
        default:
          errno = EINVAL;
      }
      if (result == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }
  }

  void initialize_socket_setsockopt(lua_State* L) {
    luaX_set_field(L, -1, "setsockopt", impl_setsockopt);
  }
}
