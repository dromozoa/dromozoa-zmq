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
local zmq = require "dromozoa.zmq"

local verbose = os.getenv "VERBOSE" == "1"

if zmq.has then
  local capabilities = { "ipc", "pgm", "tipc", "norm", "curve", "gssapi", "draft" }
  for i = 1, #capabilities do
    local capability = capabilities[i]
    local capable = zmq.has(capability)
    if verbose then
      io.stderr:write(("%s: %s\n"):format(capability, capable))
    end
    assert(capable == 0 or capable == 1)
  end
end

local major, minor, patch = zmq.version()
local version = ("%d.%d.%d"):format(major, minor, patch)
if verbose then
  io.stderr:write(version, "\n")
end
assert(major >= 4)

if verbose then
  io.stderr:write(([[
EINTR
  unix: %s
  zmq: %s
ETIMEDOUT
  unix: %s
  zmq: %s
ETERM
  unix: %s
  zmq: %s
]]):format(
      unix.strerror(unix.EINTR),
      zmq.strerror(unix.EINTR),
      unix.strerror(zmq.ETIMEDOUT),
      zmq.strerror(zmq.ETIMEDOUT),
      unix.strerror(zmq.ETERM),
      zmq.strerror(zmq.ETERM)))
end

assert(unix.EINTR)
assert(unix.ETIMEDOUT)
assert(zmq.ETIMEDOUT == unix.ETIMEDOUT)
assert(zmq.ETERM)
assert(zmq.strerror)
assert(unix.strerror(unix.EINTR) == zmq.strerror(unix.EINTR))
assert(unix.strerror(zmq.ETIMEDOUT) == zmq.strerror(zmq.ETIMEDOUT))

if verbose then
  io.stderr:write(([[
errno
  unix: %d
  zmq: %d
]]):format(unix.get_errno(), zmq.errno()))
end

assert(zmq.errno)
assert(unix.get_errno(), zmq.errno())
