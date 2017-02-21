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

    void impl_getsockopt(lua_State* L) {
      int name = luaX_check_integer<int>(L, 2);
      int result = -1;
      switch (getsockopt_option(name)) {
        case getsockopt_option_int:
          result = getsockopt_integer<int>(L, name);
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
