-- Copyright (C) 2017,2018 Tomoyuki Fujimori <moyu@dromozoa.com>
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

local verbose = os.getenv "VERBOSE" == "1"

local ctx = assert(zmq.context())

assert(ctx:get(zmq.ZMQ_IO_THREADS) == 1)
if verbose then
  io.stderr:write(ctx:get(zmq.ZMQ_MAX_SOCKETS), "\n")
end
assert(ctx:set(zmq.ZMQ_MAX_SOCKETS, 256))
assert(ctx:get(zmq.ZMQ_MAX_SOCKETS) == 256)

local socket = assert(ctx:socket(zmq.ZMQ_REP))
assert(socket:bind "tcp://127.0.0.1:5555")

assert(socket:getsockopt(zmq.ZMQ_BACKLOG) == 100)
assert(socket:setsockopt(zmq.ZMQ_BACKLOG, 200))
assert(socket:getsockopt(zmq.ZMQ_BACKLOG) == 200)

assert(socket:getsockopt(zmq.ZMQ_AFFINITY))
assert(socket:getsockopt(zmq.ZMQ_MAXMSGSIZE))

local buffer = assert(socket:recv(10))
assert(buffer == "hello")
assert(socket:send "world")

local endpoint = assert(socket:getsockopt(zmq.ZMQ_LAST_ENDPOINT))
if verbose then
  io.stderr:write(endpoint, "\n")
end
assert(endpoint == "tcp://127.0.0.1:5555")
assert(socket:unbind(endpoint))

assert(socket:close())

assert(ctx:term())
