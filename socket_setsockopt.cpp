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

namespace dromozoa {
  namespace {
    template <class T>
    inline int setsockopt_integer(lua_State* L, int name) {
      int value = luaX_check_integer<int>(L, 3);
      return zmq_setsockopt(check_socket(L, 1), name, &value, sizeof(value));
    }

    void impl_setsockopt(lua_State* L) {
      int name = luaX_check_integer<int>(L, 2);
      int result = -1;
      switch (name) {
        case ZMQ_BACKLOG:
        case ZMQ_CONFLATE:
        case ZMQ_CONNECT_TIMEOUT:
        case ZMQ_CURVE_SERVER:
        case ZMQ_GSSAPI_PLAINTEXT:
        case ZMQ_GSSAPI_SERVER:
        case ZMQ_HANDSHAKE_IVL:
        case ZMQ_HEARTBEAT_IVL:
        case ZMQ_HEARTBEAT_TIMEOUT:
        case ZMQ_HEARTBEAT_TTL:
        case ZMQ_IMMEDIATE:
        case ZMQ_INVERT_MATCHING:
        case ZMQ_IPV6:
        case ZMQ_LINGER:
        case ZMQ_MULTICAST_HOPS:
        case ZMQ_MULTICAST_MAXTPDU:
        case ZMQ_PLAIN_SERVER:
        case ZMQ_USE_FD:
        case ZMQ_PROBE_ROUTER:
        case ZMQ_RATE:
          result = setsockopt_integer<int>(L, name);
          break;
        case ZMQ_MAXMSGSIZE:
          result = setsockopt_integer<int64_t>(L, name);
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
