-- Copyright (C) 2017 Tomoyuki Fujimori <moyu@dromozoa.com>
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

local process_req = assert(unix.process())
local process_rep = assert(unix.process())
assert(process_req:forkexec(PATH, { arg[-1], "test/req.lua" }))
assert(process_rep:forkexec(PATH, { arg[-1], "test/rep.lua" }))

local a, b, c = assert(unix.wait())
print(a, b, c)
assert(a == process_req[1] or a == process_rep[1])
assert(b == "exit")
assert(c == 0)

local a, b, c = assert(unix.wait())
print(a, b, c)
assert(a == process_req[1] or a == process_rep[1])
assert(b == "exit")
assert(c == 0)
