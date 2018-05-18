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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include <stdint.h>

#include <vector>

#include "common.hpp"

#if defined(HAVE_ZMQ_CURVE_KEYPAIR) && !HAVE_DECL_ZMQ_CURVE_KEYPAIR
#include <zmq_utils.h>
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

#ifdef HAVE_ZMQ_HAS
    void impl_has(lua_State* L) {
      const char* capability = luaL_checkstring(L, 1);
      luaX_push(L, zmq_has(capability));
    }
#endif

    void impl_z85_decode(lua_State* L) {
      luaX_string_reference source = luaX_check_string(L, 1);
      if (source.size() % 5 == 0) {
        std::vector<uint8_t> buffer(source.size() * 4 / 5);
        // 2nd parameter of zmq_z85_decode did not have const qualifier in zeromq 5.0.4
        if (zmq_z85_decode(&buffer[0], const_cast<char*>(source.data()))) {
          luaX_push(L, luaX_string_reference(&buffer[0], buffer.size()));
        } else {
          push_error(L);
        }
      } else {
        errno = EINVAL;
        push_error(L);
      }
    }

    void impl_z85_encode(lua_State* L) {
      luaX_string_reference source = luaX_check_string(L, 1);
      if (source.size() % 4 == 0) {
        std::vector<char> buffer(source.size() * 5 / 4 + 1);
        // 2nd parameter of zmq_z85_encode did not have const qualifier in zeromq 5.0.4
        if (zmq_z85_encode(&buffer[0], reinterpret_cast<uint8_t*>(const_cast<char*>(source.data())), source.size())) {
          luaX_push(L, &buffer[0]);
        } else {
          push_error(L);
        }
      } else {
        errno = EINVAL;
        push_error(L);
      }
    }

#ifdef HAVE_ZMQ_CURVE_KEYPAIR
    void impl_curve_keypair(lua_State* L) {
      char z85_public_key[41] = { 0 };
      char z85_secret_key[41] = { 0 };
      if (zmq_curve_keypair(z85_public_key, z85_secret_key) == -1) {
        push_error(L);
      } else {
        luaX_push(L, luaX_string_reference(z85_public_key, 40), luaX_string_reference(z85_secret_key, 40));
      }
    }
#endif

#ifdef HAVE_ZMQ_CURVE_PUBLIC
    void impl_curve_public(lua_State* L) {
      luaX_string_reference z85_secret_key = luaX_check_string(L, 1);
      if (z85_secret_key.size() == 40) {
        char z85_public_key[41] = { 0 };
        if (zmq_curve_public(z85_public_key, z85_secret_key.data()) == -1) {
          push_error(L);
        } else {
          luaX_push(L, luaX_string_reference(z85_public_key, 40));
        }
      } else {
        errno = EINVAL;
        push_error(L);
      }
    }
#endif
  }

  void initialize_main(lua_State* L) {
    luaX_set_field(L, -1, "version", impl_version);
    luaX_set_field(L, -1, "proxy", impl_proxy);
#ifdef HAVE_ZMQ_HAS
    luaX_set_field(L, -1, "has", impl_has);
#endif
    luaX_set_field(L, -1, "z85_decode", impl_z85_decode);
    luaX_set_field(L, -1, "z85_encode", impl_z85_encode);
#ifdef HAVE_ZMQ_CURVE_KEYPAIR
    luaX_set_field(L, -1, "curve_keypair", impl_curve_keypair);
#endif
#ifdef HAVE_ZMQ_CURVE_PUBLIC
    luaX_set_field(L, -1, "curve_public", impl_curve_public);
#endif
  }
}
