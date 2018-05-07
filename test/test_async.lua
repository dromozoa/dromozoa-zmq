-- Copyright (C) 2018 Tomoyuki Fujimori <moyu@dromozoa.com>
--
-- This file is part of dromozoa-zmq.
--
-- dromozoa-zmq is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- dromozoa-zmq is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with dromozoa-zmq.  If not, see <http://www.gnu.org/licenses/>.

local unix = require "dromozoa.unix"
local zmq = require "dromozoa.zmq"

local verbose = os.getenv "VERBOSE" == "1"
local curve = true

local selector = assert(unix.selector())

local ctx = assert(zmq.context())

local server_public_key, server_secret_key = zmq.curve_keypair()
if verbose then
  io.stderr:write("server_public_key ", server_public_key, "\n")
  io.stderr:write("server_secret_key ", server_secret_key, "\n")
end

local client_public_key, client_secret_key = zmq.curve_keypair()
if verbose then
  io.stderr:write("client_public_key ", client_public_key, "\n")
  io.stderr:write("client_secret_key ", client_secret_key, "\n")
end

local rep = assert(ctx:socket(zmq.ZMQ_REP))
if curve then
  assert(rep:setsockopt(zmq.ZMQ_CURVE_SERVER, 1))
  assert(rep:setsockopt(zmq.ZMQ_CURVE_SECRETKEY, server_secret_key))
end
assert(rep:bind "inproc://test_async")
local rep_fd = assert(rep:getsockopt(zmq.ZMQ_FD))
if verbose then
  io.stderr:write("rep_fd ", rep_fd, "\n")
end

local req = assert(ctx:socket(zmq.ZMQ_REQ))
if curve then
  assert(req:setsockopt(zmq.ZMQ_CURVE_SERVERKEY, server_public_key))
  assert(req:setsockopt(zmq.ZMQ_CURVE_PUBLICKEY, client_public_key))
  assert(req:setsockopt(zmq.ZMQ_CURVE_SECRETKEY, client_secret_key))
end
assert(req:connect "inproc://test_async")
local req_fd = assert(req:getsockopt(zmq.ZMQ_FD))
if verbose then
  io.stderr:write("req_fd ", req_fd, "\n")
end

assert(selector:add(rep_fd, unix.SELECTOR_READ))

assert(req:send "hello")

local done
repeat
  local result = assert(selector:select(0.1))
  for i = 1, result do
    local fd, event = selector:event(i)
    if verbose then
      io.stderr:write("fd ", fd, "\n")
    end
    assert(fd == rep_fd)
    assert(event == unix.SELECTOR_READ)
    local events = assert(rep:getsockopt(zmq.ZMQ_EVENTS))
    if verbose then
      io.stderr:write("events ", events, "\n")
    end
    if unix.band(events, zmq.ZMQ_POLLIN) ~= 0 then
      local msg = zmq.message()
      assert(msg:recv(rep, zmq.ZMQ_DONTWAIT) == 5)
      assert(tostring(msg) == "hello")
      assert(selector:del(rep_fd))
      assert(selector:add(req_fd, unix.SELECTOR_READ))
      rep:send "world"
      done = true
    end
  end
until done

local done
repeat
  local result = assert(selector:select(0.1))
  for i = 1, result do
    local fd, event = selector:event(i)
    if verbose then
      io.stderr:write("fd ", fd, "\n")
    end
    assert(fd == req_fd)
    assert(event == unix.SELECTOR_READ)
    local events = assert(req:getsockopt(zmq.ZMQ_EVENTS))
    if verbose then
      io.stderr:write("events ", events, "\n")
    end
    if unix.band(events, zmq.ZMQ_POLLIN) ~= 0 then
      local msg = zmq.message()
      assert(msg:recv(req, zmq.ZMQ_DONTWAIT) == 5)
      assert(tostring(msg) == "world")
      assert(selector:del(req_fd))
      done = true
    end
  end
until done
