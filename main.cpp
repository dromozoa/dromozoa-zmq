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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include <stdint.h>

#include <vector>

#include "common.hpp"

#ifdef HAVE_ZMQ_CURVE_KEYPAIR
extern "C" {
  int zmq_curve_keypair (char*, char*);
}
#endif

namespace dromozoa {
  namespace {
    void impl_version(lua_State* L) {
      int major = 0;
      int minor = 0;
      int patch = 0;
      zmq_version(&major, &minor, &patch);
      luaX_push(L, major);
      luaX_push(L, minor);
      luaX_push(L, patch);
    }

#ifdef HAVE_ZMQ_HAS
    void impl_has(lua_State* L) {
      const char* capability = luaL_checkstring(L, 1);
      luaX_push(L, zmq_has(capability));
    }
#endif

    void impl_poll(lua_State* L) {
      luaL_checktype(L, 1, LUA_TTABLE);
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

    void impl_proxy(lua_State* L) {
      void* frontend = check_socket(L, 1);
      void* backend = check_socket(L, 2);
      void* capture = to_socket(L, 3);
      void* control = to_socket(L, 4);
      if (zmq_proxy_steerable(frontend, backend, capture, control) == -1) {
        push_error(L);
      } else {
        luaX_push_success(L);
      }
    }

#ifdef HAVE_ZMQ_CURVE_KEYPAIR
    void impl_curve_keypair(lua_State* L) {
      std::vector<char> z85_public_key(41);
      std::vector<char> z85_secret_key(41);
      if (zmq_curve_keypair(&z85_public_key[0], &z85_secret_key[0]) == -1) {
        push_error(L);
      } else {
        lua_pushlstring(L, &z85_public_key[0], 40);
        lua_pushlstring(L, &z85_secret_key[0], 40);
      }
    }
#endif

#ifdef HAVE_ZMQ_CURVE_PUBLIC
    void impl_curve_public(lua_State* L) {
      size_t size = 0;
      const char* z85_secret_key = luaL_checklstring(L, 1, &size);
      if (size == 40) {
        std::vector<char> z85_public_key(41);
        if (zmq_curve_public(&z85_public_key[0], z85_secret_key) == -1) {
          push_error(L);
        } else {
          lua_pushlstring(L, &z85_public_key[0], 40);
          lua_pushvalue(L, 1);
        }
      } else {
        errno = EINVAL;
        push_error(L);
      }
    }
#endif

    void impl_z85_decode(lua_State* L) {
      size_t size = 0;
      const char* data = luaL_checklstring(L, 1, &size);
      if (size % 5 == 0) {
        std::vector<char> buffer(size * 4 / 5);
        if (zmq_z85_decode(reinterpret_cast<uint8_t*>(&buffer[0]), const_cast<char*>(data))) {
          lua_pushlstring(L, &buffer[0], buffer.size());
        } else {
          push_error(L);
        }
      } else {
        errno = EINVAL;
        push_error(L);
      }
    }

    void impl_z85_encode(lua_State* L) {
      size_t size = 0;
      const char* data = luaL_checklstring(L, 1, &size);
      if (size % 4 == 0) {
        std::vector<char> buffer(size * 5 / 4 + 1);
        if (zmq_z85_encode(&buffer[0], reinterpret_cast<uint8_t*>(const_cast<char*>(data)), size)) {
          luaX_push(L, &buffer[0]);
        } else {
          push_error(L);
        }
      } else {
        errno = EINVAL;
        push_error(L);
      }
    }
  }

  void initialize_main(lua_State* L) {
    luaX_set_field(L, -1, "version", impl_version);
#ifdef HAVE_ZMQ_HAS
    luaX_set_field(L, -1, "has", impl_has);
#endif
    luaX_set_field(L, -1, "poll", impl_poll);
    luaX_set_field(L, -1, "proxy", impl_proxy);
#ifdef HAVE_ZMQ_CURVE_KEYPAIR
    luaX_set_field(L, -1, "curve_keypair", impl_curve_keypair);
#endif
#ifdef HAVE_ZMQ_CURVE_PUBLIC
    luaX_set_field(L, -1, "curve_public", impl_curve_public);
#endif
    luaX_set_field(L, -1, "z85_decode", impl_z85_decode);
    luaX_set_field(L, -1, "z85_encode", impl_z85_encode);
  }
}
