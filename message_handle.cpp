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

  class message_handle_impl {
  public:
    message_handle_impl() : state_(state_constructed) {}

    ~message_handle_impl() {
      if (state_ == state_initialized) {
        if (close() == -1) {
          DROMOZOA_UNEXPECTED(zmq_strerror(zmq_errno()));
        }
      }
    }

    int init() {
      if (state_ == state_constructed) {
        if (zmq_msg_init(&message_) == -1) {
          return -1;
        } else {
          state_ = state_initialized;
          return 0;
        }
      } else {
        errno = EINVAL;
        return -1;
      }
    }

    int init_data(const void* data, size_t size) {
      if (state_ == state_constructed) {
        if (void* buffer = malloc(size)) {
          memcpy(buffer, data, size);
          if (zmq_msg_init_data(&message_, buffer, size, free_calback, 0) == -1) {
            free(buffer);
            return -1;
          } else {
            state_ = state_initialized;
            return 0;
          }
        } else {
          return -1;
        }
      } else {
        errno = EINVAL;
        return -1;
      }
    }

    int close() {
      if (state_ == state_initialized) {
        state_ = state_closed;
        return zmq_msg_close(&message_);
      } else {
        errno = EINVAL;
        return -1;
      }
    }

    zmq_msg_t* get() {
      if (state_ == state_initialized) {
        return &message_;
      } else {
        return 0;
      }
    }

  private:
    int state_;
    zmq_msg_t message_;
  };

  message_handle_impl* message_handle::init() {
    scoped_ptr<message_handle_impl> impl(new message_handle_impl());
    if (impl->init() == -1) {
      return 0;
    } else {
      return impl.release();
    }
  }

  message_handle_impl* message_handle::init_data(const void* data, size_t size) {
    scoped_ptr<message_handle_impl> impl(new message_handle_impl());
    if (impl->init_data(data, size) == -1) {
      return 0;
    } else {
      return impl.release();
    }
  }

  message_handle::message_handle(message_handle_impl* impl) : impl_(impl) {}

  message_handle::~message_handle() {}

  int message_handle::close() {
    return impl_->close();
  }

  zmq_msg_t* message_handle::get() {
    return impl_->get();
  }
}
