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

local zmq = require "dromozoa.zmq"

local verbose = os.getenv "VERBOSE" == "1"

local ctx = assert(zmq.context())

local sub = assert(ctx:socket(zmq.ZMQ_SUB))
assert(sub:connect "tcp://127.0.0.1:5556")
assert(sub:setsockopt(zmq.ZMQ_SUBSCRIBE, "X"))

local controls = { control }
do
  local control = assert(ctx:socket(zmq.ZMQ_PUB))
  assert(control:connect "tcp://127.0.0.1:5557")
  controls[#controls + 1] = control
end
for i = 1, #arg do
  local control = assert(ctx:socket(zmq.ZMQ_PUB))
  assert(control:connect("ipc://test-" .. arg[i] .. ".sock"))
  controls[#controls + 1] = control
end

local msg = assert(zmq:message())
for i = 1, 10 do
  assert(msg:recv(sub))
  if verbose then
    io.stderr:write("recv " .. tostring(msg) .. "\n")
    io.stderr:flush()
  end
  local n = assert(tostring(msg):match("^X:(%d+):"))
  assert(n % 3 == 0)
end

assert(sub:close())
for i = 1, #controls do
  local control = controls[i]
  assert(control:send "TERMINATE")
  assert(control:close())
end
