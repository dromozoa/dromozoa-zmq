// Copyright (C) 2017-2019 Tomoyuki Fujimori <moyu@dromozoa.com>
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
  context_handle_impl::context_handle_impl() : counter_(), handle_() {
    counter_ = zmq_atomic_counter_new();
    if (!counter_) {
      throw_failure();
      return;
    }
    handle_ = zmq_ctx_new();
    if (!handle_) {
      zmq_atomic_counter_destroy(&counter_);
      throw_failure();
      return;
    }
  }

  context_handle_impl::~context_handle_impl() {
    lock_guard<> lock(mutex_);
    zmq_atomic_counter_destroy(&counter_);
    if (handle_) {
      void* handle = handle_;
      handle_ = 0;
      if (zmq_ctx_term(handle) == -1) {
        DROMOZOA_UNEXPECTED(zmq_strerror(zmq_errno()));
      }
    }
  }

  void context_handle_impl::add_ref() {
    zmq_atomic_counter_inc(counter_);
  }

  void context_handle_impl::release() {
    if (zmq_atomic_counter_dec(counter_) == 0) {
      delete this;
    }
  }

  void* context_handle_impl::get() {
    lock_guard<> lock(mutex_);
    return handle_;
  }

  int context_handle_impl::term() {
    lock_guard<> lock(mutex_);
    void* handle = handle_;
    handle_ = 0;
    return zmq_ctx_term(handle);
  }

  context_handle::context_handle(context_handle_impl* impl) : impl_(impl) {
    impl_->add_ref();
  }

  context_handle::~context_handle() {
    impl_->release();
  }

  void* context_handle::get() const {
    return impl_->get();
  }

  context_handle_impl* context_handle::share() const {
    return impl_;
  }

  int context_handle::term() {
    return impl_->term();
  }
}
