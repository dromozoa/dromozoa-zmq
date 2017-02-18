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

#ifndef DROMOZOA_COMMON_HPP
#define DROMOZOA_COMMON_HPP

#include <zmq.h>

#include <dromozoa/bind.hpp>

namespace dromozoa {
  class context_handle {
  public:
    context_handle(void* handle);
    ~context_handle();
    int term();
    void* get();
  private:
    void* handle_;
    context_handle(const context_handle&);
    context_handle& operator=(const context_handle&);
  };

  context_handle* check_context_handle(lua_State* L, int arg);
  void* check_context(lua_State* L, int arg);

  void push_error(lua_State* L);
}

#endif
