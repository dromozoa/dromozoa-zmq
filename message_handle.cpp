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

#include <utility>

#include "common.hpp"

namespace dromozoa {
  namespace {
    void free_calback(void* data, void*) {
      free(data);
    }
  }

  message_handle::message_handle() : initialized_() {}

  message_handle::~message_handle() {
    if (initialized_) {
      if (close() == -1) {
        DROMOZOA_UNEXPECTED(zmq_strerror(zmq_errno()));
      }
    }
  }

  int message_handle::init() {
    if (initialized_) {
      errno = EINVAL;
      return -1;
    } else {
      if (zmq_msg_init(&message_) == -1) {
        return -1;
      } else {
        initialized_ = true;
        return 0;
      }
    }
  }

  int message_handle::init_data(const void* data, size_t size) {
    if (initialized_) {
      errno = EINVAL;
      return -1;
    } else {
      if (void* buffer = malloc(size)) {
        memcpy(buffer, data, size);
        if (zmq_msg_init_data(&message_, buffer, size, free_calback, 0) == -1) {
          free(buffer);
          return -1;
        } else {
          initialized_ = true;
          return 0;
        }
      } else {
        return -1;
      }
    }
  }

  int message_handle::close() {
    if (initialized_) {
      initialized_ = false;
      return zmq_msg_close(&message_);
    } else {
      errno = EINVAL;
      return -1;
    }
  }

  zmq_msg_t* message_handle::get() {
    if (initialized_) {
      return &message_;
    } else {
      return 0;
    }
  }

  void message_handle::swap(message_handle& that) {
    std::swap(initialized_, that.initialized_);

    zmq_msg_t message;
    memcpy(&message, &message_, sizeof(message));
    memcpy(&message_, &that.message_, sizeof(message));
    memcpy(&that.message_, &message, sizeof(message));
  }
}
