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

local zmq = require "dromozoa.zmq"

assert(zmq.poll({}, 100) == 0)

local result, items = assert(zmq.poll({
  { fd = 0, events = zmq.ZMQ_POLLIN };
  { fd = 1, events = zmq.ZMQ_POLLOUT };
}))
assert(result == 1)
assert(items[1].revents == 0)
assert(items[2].revents == zmq.ZMQ_POLLOUT)
