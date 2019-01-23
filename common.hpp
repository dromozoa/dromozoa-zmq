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

#ifndef DROMOZOA_COMMON_HPP
#define DROMOZOA_COMMON_HPP

#include <stddef.h>

#include <zmq.h>

#include <dromozoa/bind.hpp>
#include <dromozoa/bind/mutex.hpp>

namespace dromozoa {
  class context_handle_impl {
  public:
    context_handle_impl();
    ~context_handle_impl();
    void initialize(void*, void*);
    void add_ref();
    void release();
    int term();
    void* get();
  private:
    void* counter_;
    void* handle_;
    mutex mutex_;
    context_handle_impl(const context_handle_impl&);
    context_handle_impl& operator=(const context_handle_impl&);
  };

  class context_handle {
  public:
    explicit context_handle(context_handle_impl*);
    ~context_handle();
    int term();
    void* get() const;
    context_handle_impl* share() const;
  private:
    context_handle_impl* impl_;
    context_handle(const context_handle&);
    context_handle& operator=(const context_handle&);
  };

  context_handle* check_context_handle(lua_State*, int);
  void* check_context(lua_State*, int);

  class socket_handle {
  public:
    explicit socket_handle(void*);
    ~socket_handle();
    int close();
    void* get() const;
  private:
    void* handle_;
    socket_handle(const socket_handle&);
    socket_handle& operator=(const socket_handle&);
  };

  socket_handle* check_socket_handle(lua_State*, int);
  void* check_socket(lua_State*, int);
  void* to_socket(lua_State*, int);
  void new_socket(lua_State*, void*);

  class message_handle_impl;

  class message_handle {
  public:
    static message_handle_impl* init();
    static message_handle_impl* init_data(const void*, size_t);
    explicit message_handle(message_handle_impl*);
    ~message_handle();
    int close();
    zmq_msg_t* get() const;
  private:
    scoped_ptr<message_handle_impl> impl_;
    message_handle(const message_handle&);
    message_handle& operator=(const message_handle&);
  };

  message_handle* check_message_handle(lua_State*, int);
  zmq_msg_t* check_message(lua_State*, int);

  void push_error(lua_State*);
  void throw_failure();
}

#endif
