#! /bin/sh -e

# Copyright (C) 2017,2018,2024 Tomoyuki Fujimori <moyu@dromozoa.com>
#
# This file is part of dromozoa-zmq.
#
# dromozoa-zmq is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# dromozoa-zmq is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with dromozoa-zmq.  If not, see <http://www.gnu.org/licenses/>.

mkdir -p .test
(cd .test && ln -f -s ../.libs dromozoa)

LUA_CPATH=".test/?.so;;"
export LUA_CPATH

for i in test/test*.lua
do
  case X$# in
    X0) lua "$i";;
    *) "$@" "$i";;
  esac
done
