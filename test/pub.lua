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

local name = ...

local ctx = assert(zmq.context())

local pub = assert(ctx:socket(zmq.ZMQ_PUB))
assert(pub:connect "tcp://127.0.0.1:5555")

local control = assert(ctx:socket(zmq.ZMQ_SUB))
assert(control:bind("ipc://test-" .. name .. ".sock"))
assert(control:setsockopt(zmq.ZMQ_SUBSCRIBE, ""))

local prefixes = { "X", "Y", "Z" }
for i = 0, 9999 do
  local msg = ("%s:%04d:%s"):format(prefixes[i % 3 + 1], i, name)
  assert(pub:send(msg))
  if verbose then
    io.stderr:write("send " .. msg .. "\n")
    io.stderr:flush()
  end

  local msg = assert(zmq:message())
  local result, message, code = msg:recv(control, zmq.ZMQ_DONTWAIT)
  if result then
    assert(tostring(msg) == "TERMINATE")
    break
  else
    assert(code == unix.EAGAIN, message)
  end

  unix.nanosleep(0.1)
end

assert(pub:setsockopt(zmq.ZMQ_LINGER, 0))
assert(pub:close())
assert(control:close())
assert(ctx:term())

assert(os.remove("test-" .. name .. ".sock"))
