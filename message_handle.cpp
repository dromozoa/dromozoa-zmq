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
#include <stdlib.h>
#include <string.h>

#include "common.hpp"

namespace dromozoa {
  namespace {
    enum {
      state_constructed,
      state_initialized,
      state_closed,
    };

    void free_calback(void* data, void*) {
      free(data);
    }
  }

  message_handle::message_handle() : state_(state_constructed) {}

  message_handle::~message_handle() {
    if (state_ == state_initialized) {
      if (close() == -1) {
        DROMOZOA_UNEXPECTED(zmq_strerror(zmq_errno()));
      }
    }
  }

  int message_handle::init() {
    int result = -1;
    if (state_ == state_constructed) {
      result = zmq_msg_init(&message_);
      if (result != -1) {
        state_ = state_initialized;
      }
    } else {
      errno = EINVAL;
    }
    return result;
  }

  int message_handle::init_data(const void* data, size_t size) {
    int result = -1;
    if (state_ == state_constructed) {
      if (void* buffer = malloc(size)) {
        memcpy(buffer, data, size);
        result = zmq_msg_init_data(&message_, buffer, size, free_calback, 0);
        if (result == -1) {
          free(buffer);
        } else {
          state_ = state_initialized;
        }
      }
    } else {
      errno = EINVAL;
    }
    return result;
  }

  int message_handle::close() {
    int result = -1;
    if (state_ == state_initialized) {
      result = zmq_msg_close(&message_);
      if (result != -1) {
        state_ = state_closed;
      }
    } else {
      errno = EINVAL;
    }
    return result;
  }

  zmq_msg_t* message_handle::get() {
    if (state_ == state_initialized) {
      return &message_;
    } else {
      return 0;
    }
  }

  void message_handle::swap(message_handle& that) {
    int state = state_;
    state_ = that.state_;
    that.state_ = state;

    zmq_msg_t message;
    memcpy(&message, &message_, sizeof(message));
    memcpy(&message_, &that.message_, sizeof(message));
    memcpy(&that.message_, &message, sizeof(message));
  }
}
