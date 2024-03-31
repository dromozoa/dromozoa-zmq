-- Copyright (C) 2024 Tomoyuki Fujimori <moyu@dromozoa.com>
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

local zmq = require "dromozoa.zmq"
zmq.set_failure_policy("error")

local verbose = os.getenv "VERBOSE" == "1"

assert(zmq.poll({}, 100) == 0)

local ctx = zmq.context()
local req = ctx:socket(zmq.ZMQ_REQ)
req:connect "tcp://127.0.0.1:5555"
local rep = ctx:socket(zmq.ZMQ_REP)
rep:bind "tcp://127.0.0.1:5555"

zmq.message("hello"):send(req)

local items = {
  { socket = req, events = 0 };
  { socket = rep, events = zmq.ZMQ_POLLIN };
}
local result = zmq.poll(items)
assert(result == 1)
assert(items[1].revents == 0)
assert(items[2].revents == zmq.ZMQ_POLLIN)

local msg, size = zmq.message():recv(rep, zmq.ZMQ_DONTWAIT)
assert(tostring(msg) == "hello")

items[1].events = 0
items[2].events = zmq.ZMQ_POLLOUT
local result = zmq.poll(items)
assert(result == 1)
assert(items[1].revents == 0)
assert(items[2].revents == zmq.ZMQ_POLLOUT)

zmq.message("world"):send(rep)

items[1].events = zmq.ZMQ_POLLIN
items[2].events = 0
local result = zmq.poll(items)
assert(result == 1)
assert(items[1].revents == zmq.ZMQ_POLLIN)
assert(items[2].revents == 0)

local msg = zmq.message():recv(req, zmq.ZMQ_DONTWAIT)
assert(tostring(msg) == "world")

req:close()
rep:close()
ctx:term()
