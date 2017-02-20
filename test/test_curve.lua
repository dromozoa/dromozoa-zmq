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

local bin_public_key = string.char(
  0xBB, 0x88, 0x47, 0x1D, 0x65, 0xE2, 0x65, 0x9B,
  0x30, 0xC5, 0x5A, 0x53, 0x21, 0xCE, 0xBB, 0x5A,
  0xAB, 0x2B, 0x70, 0xA3, 0x98, 0x64, 0x5C, 0x26,
  0xDC, 0xA2, 0xB2, 0xFC, 0xB4, 0x3F, 0xC5, 0x18)
local z85_public_key = "Yne@$w-vo<fVvi]a<NY6T1ed:M$fCG*[IaLV{hID"
local z85_secret_key = "D:)Q[IlAW!ahhC2ac:9*A}h:p?([4%wOTJ%JR%cs"

assert(zmq.curve_public(z85_secret_key) == z85_public_key)
assert(zmq.z85_encode(bin_public_key) == z85_public_key)
assert(zmq.z85_decode(z85_public_key) == bin_public_key)

local p1, s1 = zmq.curve_keypair()
print(p1)
print(s1)
local p2, s2 = zmq.curve_public(s1)
assert(p1 == p2)
assert(s1 == s2)
