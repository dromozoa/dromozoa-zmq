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

local unix = require "dromozoa.unix"
local zmq = require "dromozoa.zmq"

local verbose = os.getenv "VERBOSE" == "1"

local ctx = assert(zmq.context())
local socket = assert(ctx:socket(zmq.ZMQ_REP))
local result, message, code = socket:bind("no-such-protocol://*:0")
if verbose then
  print(result, message, code)
end
assert(not result)
assert(code == unix.EPROTONOSUPPORT)

assert(zmq.get_failure_policy() == "fail")
zmq.set_failure_policy("error")
assert(zmq.get_failure_policy() == "error")

local ctx = assert(zmq.context())
local socket = assert(ctx:socket(zmq.ZMQ_REP))
local result, message = pcall(function ()
  socket:bind("no-such-protocol://*:0")
end)
if verbose then
  print(result, message)
end
assert(not result)
