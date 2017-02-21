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

#include "common.hpp"

namespace dromozoa {
  socket_handle::socket_handle(void* handle) : handle_(handle) {}

  socket_handle::~socket_handle() {
    if (handle_) {
      if (close() == -1) {
        DROMOZOA_UNEXPECTED(zmq_strerror(zmq_errno()));
      }
    }
  }

  int socket_handle::close() {
    int result = zmq_close(handle_);
    if (result == 0) {
      handle_ = 0;
    }
    return result;
  }

  void* socket_handle::get() {
    return handle_;
  }
}
