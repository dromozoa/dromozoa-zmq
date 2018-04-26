-- Copyright (C) 2018 Tomoyuki Fujimori <moyu@dromozoa.com>
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

local linked_hash_table = require "dromozoa.commons.linked_hash_table"

local source_dir = ...

local function parse_doc(filename)
  local result = linked_hash_table()
  local enums = {}
  local name
  local item
  local prev
  local mode
  for line in io.lines(filename) do
    if line:find "^~+$" then
      item = {}
      name, item.description = assert(prev:match "^(ZMQ_[%w_]+):%s+(.*)")
    elseif line == "[horizontal]" then
      mode = "H"
    elseif mode == "H" then
      if line == "" then
        mode = nil
        if name == "ZMQ_THREAD_SAFE" then
          assert(item.option_value_type == "boolean")
          assert(not item.option_value_unit)
          item.option_value_type = "int"
          item.option_value_unit = "boolean"
        end
        assert(name)
        assert(item.option_value_type)
        assert(item.option_value_unit or item.option_value_size)
        local enum = item.option_value_type
        if enum == "int on POSIX systems, SOCKET on Windows" then
          enum = "int"
        elseif enum == "NULL-terminated character string" then
          enum = "character string"
        end
        enum = enum:gsub("%W", "_")
        enums[enum] = true
        item.option_value_enum = enum
        result[name] = item
      else
        local k, v = assert(line:match "(.-):: (.*)")
        if k == "Option value type" then
          item.option_value_type = v
        elseif k == "Option value unit" then
          item.option_value_unit = v
        elseif k == "Option value size" then
          item.option_value_size = v
        elseif k == "Default value" then
          item.default_value = v
        elseif k == "Applicable socket types" then
          item.applicable_socket_types = v
        else
          error "could not parse line"
        end
      end
    end
    prev = line
  end

  return result, enums
end

local function generate_md(filename, title, data)
  local out = assert(io.open(filename, "w"))
  out:write(([[
# %s

Name|Type|Unit|Size|Default|Description
----|----|----|----|----|----
]]):format(title))
  for name, item in data:each() do
    local unit = item.option_value_unit
    if unit == nil then
      unit = ""
    end
    local size = item.option_value_size
    if size == nil then
      size = ""
    end
    out:write(("%s|%s|%s|%s|%s|%s\n"):format(name, item.option_value_type, unit, size, item.default_value or "", item.description))
  end
  out:close()
end

local header_file = source_dir .. "/include/zmq.h"
local getsockopt_file = source_dir .. "/doc/zmq_getsockopt.txt"
local setsockopt_file = source_dir .. "/doc/zmq_setsockopt.txt"

local out = assert(io.open("symbols.cpp", "w"))

out:write [[
#include "common.hpp"
#include "symbols.hpp"

namespace dromozoa {
  void initialize_symbols(lua_State* L) {
]]

local buffer
for line in io.lines(header_file) do
  local name = line:match "^#define (ZMQ_[%w_]+) "
  if name then
    out:write(([[
#ifdef %s
    luaX_set_field(L, -1, "%s", %s);
#endif
]]):format(name, name, name))
  end
end

out:write [[
  }

  getsockopt_option_enum getsockopt_option(int name) {
    switch (name) {
]]

local getsockopts, getsockopt_enums = parse_doc(getsockopt_file)
generate_md("docs/getsockopt.md", "zmq_getsockopt", getsockopts)

for name, item in getsockopts:each() do
  out:write(([[
#ifdef %s
      case %s:
        return getsockopt_option_%s;
#endif
]]):format(name, name, item.option_value_enum))
end

out:write([[
      default:
        return getsockopt_option_unknown;
    }
  }

  setsockopt_option_enum setsockopt_option(int name) {
    switch (name) {
]])

local setsockopts, setsockopt_enums = parse_doc(setsockopt_file)
generate_md("docs/setsockopt.md", "zmq_setsockopt", setsockopts)

for name, item in setsockopts:each() do
  out:write(([[
#ifdef %s
      case %s:
        return setsockopt_option_%s;
#endif
]]):format(name, name, item.option_value_enum))
end

out:write([[
      default:
        return setsockopt_option_unknown;
    }
  }
}
]])

out:close()

local out = assert(io.open("symbols.hpp", "w"))

out:write [[
// generated from %s

#ifndef DROMOZOA_SYMBOLS_HPP
#define DROMOZOA_SYMBOLS_HPP

#include "common.hpp"

namespace dromozoa {
  enum getsockopt_option_enum {
    getsockopt_option_unknown,
]]

local enums = {}
for enum in pairs(getsockopt_enums) do
  enums[#enums + 1] = enum
end
table.sort(enums)
for i = 1, #enums do
  out:write("    getsockopt_option_", enums[i], ",\n")
end

out:write([[
  };

  enum setsockopt_option_enum {
    setsockopt_option_unknown,
]])

local enums = {}
for enum in pairs(setsockopt_enums) do
  enums[#enums + 1] = enum
end
table.sort(enums)
for i = 1, #enums do
  out:write("    setsockopt_option_", enums[i], ",\n")
end

out:write([[
  };

  void initialize_symbols(lua_State* L);
  getsockopt_option_enum getsockopt_option(int name);
  setsockopt_option_enum setsockopt_option(int name);
}

#endif
]])

out:close()
