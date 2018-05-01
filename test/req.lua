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

local ctx = assert(zmq.context())
local socket = assert(ctx:socket(zmq.ZMQ_REQ))
assert(socket:connect "tcp://127.0.0.1:5555")

local msg = assert(zmq.message "hello")
assert(msg:send(socket))
assert(msg:close())

local msg = zmq.message()
assert(msg:recv(socket) == 5)
assert(tostring(msg) == "world")
assert(msg:get(zmq.ZMQ_MORE) == 0)
if msg.gets then
  assert(msg:gets "Socket-Type" == "REP")
end
assert(msg:more() == 0)

assert(socket:disconnect "tcp://127.0.0.1:5555")
assert(socket:close())

assert(ctx:term())
