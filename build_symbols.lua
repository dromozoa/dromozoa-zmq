-- Copyright (C) 2018,2019,2024 Tomoyuki Fujimori <moyu@dromozoa.com>
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

local source_dir = ...

local function parse_doc(filename)
  local result = {}
  local enums = {}
  local item
  local prev
  local mode
  local count = 0

  for line in io.lines(filename) do
    count = count + 1
    if line:find "^~+$" then
      local name, description = assert(prev:match "^(ZMQ_[%w_]+):%s+(.*)")
      item = { name = name, description = description }
    elseif line == "[horizontal]" then
      mode = "H"
    elseif mode == "H" then
      if line == "" then
        mode = nil
        if item.name == "ZMQ_THREAD_SAFE" then
          -- zeromq 4.3.2の不備に対応する。
          if item.option_value_type == "boolean" then
            assert(item.option_value_type == "boolean", "filename="..filename)
            assert(not item.option_value_unit)
            item.option_value_type = "int"
            item.option_value_unit = "boolean"
          end
        end
        assert(item.name)
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
        result[#result + 1] = item
      else
        local k, v = line:match "(.-):: (.*)"
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
        elseif k == "Maximum value" then
          item.maximum_value = v
        elseif not k and item.name == "ZMQ_RECONNECT_STOP" then
          assert(item.applicable_socket_types)
          item.applicable_socket_types = item.applicable_socket_types.." "..line
        else
          error(("could not parse line at file %s line %d: %q"):format(filename, count, line))
        end
      end
    end
    prev = line
  end

  return result, enums
end

local header_file = source_dir .. "/include/zmq.h"
local getsockopt_file = source_dir .. "/doc/zmq_getsockopt.txt"
local setsockopt_file = source_dir .. "/doc/zmq_setsockopt.txt"

local out = assert(io.open("symbols.cpp", "w"))

out:write [[
#include "common.hpp"
#include "symbols.hpp"

namespace dromozoa_zmq {
  void initialize_symbols(lua_State* L) {
]]

local buffer
for line in io.lines(header_file) do
  local name = line:match "^#define (ZMQ_[%w_]+) "
  if name == "ZMQ_EXPORT" then
    name = nil
  end

  if not name then
    local check
    name, check = line:match "^#define (E[%w_]+) (%S*)"
    if name then
      assert(check == "(ZMQ_HAUSNUMERO")
    end
  end

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

for i = 1, #getsockopts do
  local item = getsockopts[i]
  local name = item.name
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

for i = 1, #setsockopts do
  local item = setsockopts[i]
  local name = item.name
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
#ifndef DROMOZOA_SYMBOLS_HPP
#define DROMOZOA_SYMBOLS_HPP

#include "common.hpp"

namespace dromozoa_zmq {
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

local out = assert(io.open("docs/option.html", "w"))

out:write [[
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
<title>dromozoa-zmq</title>
<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/github-markdown-css@5.5.1/github-markdown.min.css">
<style>
.markdown-body {
  box-sizing: border-box;
  min-width: 200px;
  margin: 0 auto;
  padding: 45px;
}
@media (max-width: 767px) {
  .markdown-body {
    padding: 15px;
  }
}
</style>
</head>
<body>
<div class="markdown-body">

<h1>dromozoa-zmq</h1>

<h2>zmq_getsockopt</h2>

<table>
  <tr>
    <th>Name</th>
    <th>Type</th>
    <th>Unit</th>
    <th>Size</th>
    <th>Default</th>
  </tr>
]]

for i = 1, #getsockopts do
  local item = getsockopts[i]
  local name = item.name
  out:write(([[
  <tr>
    <td>%s</td>
    <td>%s</td>
    <td>%s</td>
    <td>%s</td>
    <td>%s</td>
  </tr>
]]):format(
    item.name,
    item.option_value_type,
    item.option_value_unit or "",
    item.option_value_size or "",
    item.default_value))
end

out:write [[
</table>

<h2>zmq_setsockopt</h2>

<table>
  <tr>
    <th>Name</th>
    <th>Type</th>
    <th>Unit</th>
    <th>Size</th>
    <th>Default</th>
  </tr>
]]

for i = 1, #setsockopts do
  local item = setsockopts[i]
  local name = item.name
  out:write(([[
  <tr>
    <td>%s</td>
    <td>%s</td>
    <td>%s</td>
    <td>%s</td>
    <td>%s</td>
  </tr>
]]):format(
    item.name,
    item.option_value_type,
    item.option_value_unit or "",
    item.option_value_size or "",
    item.default_value))
end

out:write [[
</table>

</div>
</body>
</html>
]]

out:close()
