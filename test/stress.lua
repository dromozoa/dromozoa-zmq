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

local worker_script = [[
local multi = require "dromozoa.multi"
local zmq = require "dromozoa.zmq"

local ptr, n = ...

local ctx = assert(zmq.context(ptr))
local socket = assert(ctx:socket(zmq.ZMQ_REQ))
assert(socket:connect "inproc://socket")

local thread_id = multi.this_thread_id()
local recv_msg = zmq.message()

for i = 1, n do
  local send_msg = assert(zmq.message "open")
  assert(send_msg:send(socket))
  assert(send_msg:close())

  assert(recv_msg:recv(socket))
  local fd = tonumber(tostring(recv_msg))

  -- print(thread_id, i, fd)

  local send_msg = assert(zmq.message("close:" .. fd))
  assert(send_msg:send(socket))
  assert(send_msg:close())

  assert(recv_msg:recv(socket))
  assert(tostring(recv_msg) == "OK")
end

local send_msg = assert(zmq.message "exit")
assert(send_msg:send(socket))
assert(send_msg:close())

assert(recv_msg:recv(socket))
assert(tostring(recv_msg) == "OK")
]]

local ctx = assert(zmq.context())
local ptr = ctx:share()
local m = 10
local n = 1000

local socket = assert(ctx:socket(zmq.ZMQ_REP))
assert(socket:bind "inproc://socket")

local threads = {}
for i = 1, m do
  local state = multi.state():load(worker_script)
  threads[i] = multi.thread(state, ptr, n)
end

local fd = 0
local opened = {}
local closed = {}
local exit_count = 0
local recv_msg = zmq.message()
repeat
  assert(recv_msg:recv(socket))
  local s = tostring(recv_msg)
  if s == "open" then
    fd = fd + 1
    assert(not opened[fd])
    assert(not closed[fd])
    opened[fd] = true
    local send_msg = assert(zmq.message(tostring(fd)))
    assert(send_msg:send(socket))
    assert(send_msg:close())
  elseif s == "exit" then
    exit_count = exit_count + 1
    local send_msg = assert(zmq.message "OK")
    assert(send_msg:send(socket))
    assert(send_msg:close())
  else
    local fd = assert(s:match "^close:(%d+)$")
    fd = tonumber(fd)
    assert(opened[fd])
    assert(not closed[fd])
    opened[fd] = nil
    closed[fd] = true
    local send_msg = assert(zmq.message "OK")
    assert(send_msg:send(socket))
    assert(send_msg:close())
  end
until exit_count == m

for i = 1, m do
  assert(threads[i]:join())
end
