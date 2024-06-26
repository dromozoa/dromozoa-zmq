// Copyright (C) 2017,2024 Tomoyuki Fujimori <moyu@dromozoa.com>
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
#include "symbols.hpp"

namespace dromozoa_zmq {
  void initialize_context(lua_State* L);
  void initialize_main(lua_State* L);
  void initialize_message(lua_State* L);
  void initialize_socket(lua_State* L);

  void initialize(lua_State* L) {
    initialize_context(L);
    initialize_main(L);
    initialize_message(L);
    initialize_socket(L);
    initialize_symbols(L);
  }
}

extern "C" int luaopen_dromozoa_zmq(lua_State* L) {
  lua_newtable(L);
  dromozoa_zmq::initialize(L);
  return 1;
}
