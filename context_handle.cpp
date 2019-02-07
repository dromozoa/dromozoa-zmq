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
#ifndef HAVE_ZMQ_ATOMIC_COUNTER_NEW
  class atomic_counter_impl {
  public:
    atomic_counter_impl() : count_() {}

    int increment() {
      lock_guard<> lock(mutex_);
      return count_++;
    }

    int decrement() {
      lock_guard<> lock(mutex_);
      return --count_ > 0 ? 1 : 0;
    }

  private:
    int count_;
    mutex mutex_;
    atomic_counter_impl(const atomic_counter_impl&);
    atomic_counter_impl& operator=(const atomic_counter_impl&);
  };
#endif


  context_handle_impl::context_handle_impl() : counter_(), handle_() {
#ifdef HAVE_ZMQ_ATOMIC_COUNTER_NEW
    counter_ = zmq_atomic_counter_new();
#else
    counter_.reset(new atomic_counter_impl());
#endif
    if (!counter_) {
      throw_failure();
      return;
    }

    handle_ = zmq_ctx_new();
    if (!handle_) {
#ifdef HAVE_ZMQ_ATOMIC_COUNTER_NEW
      zmq_atomic_counter_destroy(&counter_);
#else
      counter_.reset();
#endif
      throw_failure();
      return;
    }
  }

  context_handle_impl::~context_handle_impl() {
    lock_guard<> lock(mutex_);
#ifdef HAVE_ZMQ_ATOMIC_COUNTER_NEW
    zmq_atomic_counter_destroy(&counter_);
#else
    counter_.reset();
#endif
    if (handle_) {
      void* handle = handle_;
      handle_ = 0;
      if (zmq_ctx_term(handle) == -1) {
        DROMOZOA_UNEXPECTED(zmq_strerror(zmq_errno()));
      }
    }
  }

  void context_handle_impl::add_ref() {
#ifdef HAVE_ZMQ_ATOMIC_COUNTER_NEW
    zmq_atomic_counter_inc(counter_);
#else
    counter_->increment();
#endif
  }

  void context_handle_impl::release() {
#ifdef HAVE_ZMQ_ATOMIC_COUNTER_NEW
    bool reached_zero = zmq_atomic_counter_dec(counter_) == 0;
#else
    bool reached_zero = counter_->decrement() == 0;
#endif
    if (reached_zero) {
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
