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

local ctx = assert(zmq.context())
local socket = assert(ctx:socket(zmq.ZMQ_REP))
assert(socket:bind("tcp://*:5556"))

assert(socket:getsockopt(zmq.ZMQ_PLAIN_USERNAME) == "")
assert(socket:getsockopt(zmq.ZMQ_PLAIN_USERNAME, 16) == "")
assert(socket:getsockopt(zmq.ZMQ_PLAIN_PASSWORD, 16) == "")
assert(socket:getsockopt(zmq.ZMQ_MECHANISM) == zmq.ZMQ_NULL)

assert(socket:setsockopt(zmq.ZMQ_PLAIN_USERNAME, "username"))
assert(socket:setsockopt(zmq.ZMQ_PLAIN_PASSWORD, "password"))

assert(socket:getsockopt(zmq.ZMQ_PLAIN_USERNAME) == "username")
assert(socket:getsockopt(zmq.ZMQ_PLAIN_USERNAME, 16) == "username")
assert(socket:getsockopt(zmq.ZMQ_PLAIN_PASSWORD, 16) == "password")
assert(socket:getsockopt(zmq.ZMQ_MECHANISM) == zmq.ZMQ_PLAIN)

assert(socket:setsockopt(zmq.ZMQ_PLAIN_USERNAME))
assert(socket:setsockopt(zmq.ZMQ_PLAIN_PASSWORD, nil))
assert(socket:getsockopt(zmq.ZMQ_MECHANISM) == zmq.ZMQ_NULL)

local z85_secret_key, z85_public_key = assert(zmq.curve_keypair())
assert(socket:setsockopt(zmq.ZMQ_CURVE_PUBLICKEY, z85_public_key))
assert(socket:getsockopt(zmq.ZMQ_CURVE_PUBLICKEY) == z85_public_key)
assert(socket:getsockopt(zmq.ZMQ_CURVE_PUBLICKEY, 32) == zmq.z85_decode(z85_public_key))
assert(socket:getsockopt(zmq.ZMQ_CURVE_PUBLICKEY, 41) == z85_public_key)
assert(socket:setsockopt(zmq.ZMQ_CURVE_SECRETKEY, zmq.z85_decode(z85_secret_key)))
assert(socket:getsockopt(zmq.ZMQ_CURVE_SECRETKEY) == z85_secret_key)
assert(socket:getsockopt(zmq.ZMQ_CURVE_SECRETKEY, 32) == zmq.z85_decode(z85_secret_key))
assert(socket:getsockopt(zmq.ZMQ_CURVE_SECRETKEY, 41) == z85_secret_key)

assert(socket:close())
assert(ctx:term())
