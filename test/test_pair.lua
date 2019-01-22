-- Copyright (C) 2019 Tomoyuki Fujimori <moyu@dromozoa.com>
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

local multi = require "dromozoa.multi"
local zmq = require "dromozoa.zmq"

local verbose = os.getenv "VERBOSE" == "1"

local ctx = assert(zmq.context())
local p1 = assert(ctx:socket(zmq.ZMQ_PAIR))
assert(p1:bind "inproc://p1")

local s = multi.state():load [[
local multi = require "dromozoa.multi"
local unix = require "dromozoa.unix"
local zmq = require "dromozoa.zmq"

local verbose = os.getenv "VERBOSE" == "1"

local ctx = assert(zmq.context())
local p1 = assert(ctx:socket(zmq.ZMQ_PAIR))
assert(p1:connect "inproc://p1")

if verbose then
  print(multi.this_thread_id(), "send ready")
end
assert(p1:send "ready")

if verbose then
  print(multi.this_thread_id(), "done")
end
]]

local t = multi.thread(s)

local msg = assert(zmq.message())
assert(msg:recv(p1))
if verbose then
  print(multi.this_thread_id(), "recv ready", tostring(msg))
end

t:join()
