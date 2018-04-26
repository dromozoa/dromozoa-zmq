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

local unix = require "dromozoa.unix"

local PATH = os.getenv("PATH")

local lua
if _G["dromozoa.bind.driver"] then
  lua = "lua"
else
  lua = arg[-1]
end

local process_req = assert(unix.process())
local process_rep = assert(unix.process())
assert(process_req:forkexec(PATH, { lua, "test/req.lua" }))
assert(process_rep:forkexec(PATH, { lua, "test/rep.lua" }))

local pid, reason, status = assert(unix.wait())
assert(pid == process_req[1] or pid == process_rep[1])
assert(reason == "exit")
assert(status == 0)

local pid, reason, status = assert(unix.wait())
assert(pid == process_req[1] or pid == process_rep[1])
assert(reason == "exit")
assert(status == 0)
