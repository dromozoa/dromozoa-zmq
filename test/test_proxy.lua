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
local PATH = os.getenv("PATH")

local lua
if _G["dromozoa.bind.driver"] then
  lua = "lua"
else
  lua = arg[-1]
end

local ctx = assert(zmq.context())

local xsub = assert(ctx:socket(zmq.ZMQ_XSUB))
assert(xsub:bind("tcp://127.0.0.1:5555"))

local xpub = assert(ctx:socket(zmq.ZMQ_XPUB))
assert(xpub:bind("tcp://127.0.0.1:5556"))

local control = assert(ctx:socket(zmq.ZMQ_SUB))
assert(control:bind "tcp://127.0.0.1:5557")
assert(control:setsockopt(zmq.ZMQ_SUBSCRIBE, ""))

local names = { "A", "B", "C" }
local processes = {}
for i = 1, #names do
  local process = assert(unix.process())
  assert(process:forkexec(PATH, { lua, "test/pub.lua", names[i] }))
  if verbose then
    io.stderr:write("forkexec test/pub.lua " .. names[i] .. " " .. process[1] .. "\n")
    io.stderr:flush()
  end
  processes[#processes + 1] = process
end
do
  local process = assert(unix.process())
  assert(process:forkexec(PATH, { lua, "test/sub.lua", (table.unpack or unpack)(names) }))
  if verbose then
    io.stderr:write("forkexec test/sub.lua " .. table.concat(names, " ") .. " " .. process[1] .. "\n")
    io.stderr:flush()
  end
  processes[#processes + 1] = process
end

assert(zmq.proxy(xsub, xpub, nil, control))

assert(xsub:close())
assert(xpub:close())
assert(control:close())

local m = #processes
local n = m
repeat
  for i = 1, m do
    local process = processes[i]
    if process then
      local result, message, code = unix.wait(process[1], unix.WNOHANG)
      if result then
        if result ~= 0 then
          processes[i] = nil
          n = n - 1
          assert(result == process[1])
          assert(message == "exit")
          assert(code == 0)
        end
      else
        assert(code == unix.EAGAIN)
      end
    end
  end
  unix.nanosleep(0.1)
until n == 0
