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

m4_include([dromozoa-zmq-version.m4])
AC_INIT([dromozoa-zmq],[DROMOZOA_ZMQ_VERSION],[moyu@dromozoa.com],[],[https://github.com/dromozoa/dromozoa-zmq/])
AM_INIT_AUTOMAKE
LT_INIT
gl_LD_VERSION_SCRIPT

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_PROG_CXX

AX_ZMQ([4.0.0], [], [AC_MSG_ERROR([could not find zmq])])
CPPFLAGS="$CPPFLAGS $ZMQ_CPPFLAGS"
LDFLAGS="$LDFLAGS $ZMQ_LDFLAGS"
LIBS="$LIBS $ZMQ_LIBS"

AC_CHECK_FUNCS([zmq_curve_keypair])
AC_CHECK_FUNCS([zmq_curve_public])
AC_CHECK_FUNCS([zmq_has])
AC_CHECK_FUNCS([zmq_msg_gets])
AC_CHECK_FUNCS([zmq_atomic_counter_new])

AC_CHECK_DECLS([zmq_curve_keypair], [], [], [#include <zmq.h>])

AX_PTHREAD([], [AC_MSG_ERROR([could not find pthread])])
CXXFLAGS="$CXXFLAGS $PTHREAD_CFLAGS"
LIBS="$LIBS $PTHREAD_LIBS"
AC_SEARCH_LIBS([pthread_create], [pthread])

AX_PROG_LUA([5.1], [], [], [AC_MSG_ERROR([could not find lua])])
AX_LUA_HEADERS([], [AC_MSG_ERROR([could not find lua])])

AC_OUTPUT
