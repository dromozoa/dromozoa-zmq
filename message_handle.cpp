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
#include <stdlib.h>
#include <string.h>

#include "common.hpp"

namespace dromozoa_zmq {
  namespace {
    void free_calback(void* data, void*) {
      free(data);
    }
  }

  message_handle_impl::message_handle_impl() : closed_() {
    if (zmq_msg_init(&message_) == -1) {
      throw_failure();
      return;
    }
  }

  message_handle_impl::message_handle_impl(const void* data, size_t size) : closed_() {
    void* buffer = malloc(size);
    if (!buffer) {
      throw_failure();
      return;
    }
    memcpy(buffer, data, size);
    if (zmq_msg_init_data(&message_, buffer, size, free_calback, 0) == -1) {
      free(buffer);
      throw_failure();
      return;
    }
  }

  message_handle_impl::~message_handle_impl() {
    if (!closed_) {
      if (close() == -1) {
        DROMOZOA_UNEXPECTED(zmq_strerror(zmq_errno()));
      }
    }
  }

  int message_handle_impl::close() {
    if (!closed_) {
      closed_ = true;
      return zmq_msg_close(&message_);
    } else {
      errno = EINVAL;
      return -1;
    }
  }

  zmq_msg_t* message_handle_impl::get() {
    if (!closed_) {
      return &message_;
    } else {
      return 0;
    }
  }

  message_handle::message_handle(message_handle_impl* impl) : impl_(impl) {}

  message_handle::~message_handle() {}

  int message_handle::close() {
    return impl_->close();
  }

  zmq_msg_t* message_handle::get() const {
    return impl_->get();
  }
}
