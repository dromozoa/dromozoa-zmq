# Copyright (C) 2017-2019,2024 Tomoyuki Fujimori <moyu@dromozoa.com>
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

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
	.gitignore \
	README.md \
	bind \
	build_symbols.lua \
	docs \
	dromozoa-zmq-*.rockspec \
	m4/update \
	module.map \
	test \
	$(TESTS)
TESTS = test.sh

luaexec_LTLIBRARIES = zmq.la

noinst_HEADERS = common.hpp symbols.hpp

zmq_la_CPPFLAGS = -I$(top_srcdir)/bind
zmq_la_LDFLAGS = -module -avoid-version -shared
if HAVE_LD_VERSION_SCRIPT
zmq_la_LDFLAGS += -Wl,--version-script=module.map
endif
zmq_la_SOURCES = \
	context.cpp \
	context_handle.cpp \
	main.cpp \
	message.cpp \
	message_handle.cpp \
	module.cpp \
	socket.cpp \
	socket_getsockopt.cpp \
	socket_handle.cpp \
	socket_setsockopt.cpp \
	symbols.cpp
