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

local basename = require "dromozoa.commons.basename"

local source_dir = ...

local header_file = source_dir .. "/include/zmq.h"

local out = assert(io.open("symbols.cpp", "w"))

out:write(([[
// generated from %s

#include "common.hpp"

namespace dromozoa {
  void initialize_symbols(lua_State* L) {
]]):format(basename(source_dir)))

local buffer
for line in io.lines(header_file) do
  local name, value = line:match("^%s*#%s*define%s+(ZMQ_[%w_]+)%s+(.*)")
  if name then
    if name ~= "ZMQ_EXPORT" then
      out:write(([[
#ifdef %s
    luaX_set_field(L, -1, "%s", %s);
#endif
]]):format(name, name, name))
    end
  end
end

out:write([[
  }
}
]])

out:close()
