// Copyright (C) 2017-2019,2024 Tomoyuki Fujimori <moyu@dromozoa.com>
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
#include <string.h>
#include <vector>

#include "common.hpp"

#if defined(HAVE_ZMQ_CURVE_KEYPAIR) && !HAVE_DECL_ZMQ_CURVE_KEYPAIR
#include <zmq_utils.h>
#endif

namespace dromozoa_zmq {
  namespace {
    void impl_version(lua_State* L) {
      int major = 0;
      int minor = 0;
      int patch = 0;
      zmq_version(&major, &minor, &patch);
      luaX_push(L, major, minor, patch);
    }

    void impl_proxy(lua_State* L) {
      void* frontend = check_socket(L, 1);
      void* backend = check_socket(L, 2);
      void* capture = to_socket(L, 3);
      void* control = to_socket(L, 4);
      if (zmq_proxy_steerable(frontend, backend, capture, control) == -1) {
        throw_failure();
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
          throw_failure();
        }
      } else {
        errno = EINVAL;
        throw_failure();
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
          throw_failure();
        }
      } else {
        errno = EINVAL;
        throw_failure();
      }
    }

#ifdef HAVE_ZMQ_CURVE_KEYPAIR
    void impl_curve_keypair(lua_State* L) {
      char z85_public_key[41] = { 0 };
      char z85_secret_key[41] = { 0 };
      if (zmq_curve_keypair(z85_public_key, z85_secret_key) == -1) {
        throw_failure();
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
          throw_failure();
        } else {
          luaX_push(L, luaX_string_reference(z85_public_key, 40));
        }
      } else {
        errno = EINVAL;
        throw_failure();
      }
    }
#endif

    void impl_poll(lua_State* L) {
      luaL_checktype(L, 1, LUA_TTABLE);
      long timeout = luaX_opt_integer<long>(L, 2, -1);

      std::vector<zmq_pollitem_t> items;
      for (int i = 1; ; ++i) {
        luaX_get_field(L, 1, i);
        if (lua_isnil(L, -1)) {
          lua_pop(L, 1);
          break;
        } else if (lua_istable(L, -1)) {
          zmq_pollitem_t item;

          luaX_get_field(L, -1, "socket");
          item.socket = to_socket(L, -1);
          lua_pop(L, 1);

          item.fd = luaX_opt_integer_field<int>(L, -1, "fd", -1);
          item.events = luaX_opt_integer_field<short>(L, -1, "events", 0);
          item.revents = luaX_opt_integer_field<short>(L, -1, "revents", 0);

          items.push_back(item);

          lua_pop(L, 1);
        } else {
          luaX_field_error(L, i, "not a table");
          return;
        }
      }

      int result = zmq_poll(items.data(), items.size(), timeout);
      if (result == -1) {
        throw_failure();
        return;
      }

      for (size_t i = 0; i < items.size(); ++i) {
        luaX_get_field(L, 1, i + 1);
        luaX_set_field(L, -1, "revents", items[i].revents);
        lua_pop(L, 1);
      }

      luaX_push(L, result);
    }

    static const char* registry_key = "dromozoa.zmq.falure_policy";

    void impl_set_failure_policy(lua_State* L) {
      lua_pushvalue(L, 1);
      luaX_set_field(L, LUA_REGISTRYINDEX, registry_key);
    }

    void impl_get_failure_policy(lua_State* L) {
      lua_getfield(L, LUA_REGISTRYINDEX, registry_key);
    }

    void impl_strerror(lua_State* L) {
      int code = luaX_opt_integer<int>(L, 1, zmq_errno());
      luaX_push(L, zmq_strerror(code));
    }

    void impl_errno(lua_State* L) {
      luaX_push(L, zmq_errno());
    }
  }

  bool failure_policy_is_error(lua_State* L){
    luaX_top_saver saver(L);
    lua_getfield(L, LUA_REGISTRYINDEX, registry_key);
    luaX_string_reference failure_policy = luaX_to_string(L, -1);
    return failure_policy.size() == 5 && strncmp(failure_policy.data(), "error", 5) == 0;
  }

  void throw_failure() {
    int code = zmq_errno();
    luaX_throw_failure(zmq_strerror(code), code);
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
    luaX_set_field(L, -1, "poll", impl_poll);

    luaX_set_field(L, LUA_REGISTRYINDEX, registry_key, "fail");
    luaX_set_field(L, -1, "set_failure_policy", impl_set_failure_policy);
    luaX_set_field(L, -1, "get_failure_policy", impl_get_failure_policy);

    luaX_set_field(L, -1, "strerror", impl_strerror);
    luaX_set_field(L, -1, "errno", impl_errno);
  }
}
