package = "dromozoa-zmq"
version = "1.5-1"
source = {
  url = "https://github.com/dromozoa/dromozoa-zmq/releases/download/v1.5/dromozoa-zmq-1.5.tar.gz";
}
description = {
  summary = "Lua bindings for ZeroMQ";
  license = "GPL-3";
  homepage = "https://github.com/dromozoa/dromozoa-zmq/";
  maintainer = "Tomoyuki Fujimori <moyu@dromozoa.com>";
}
build = {
  type = "command";
  build_command = "env PATH=\"$(LUA_BINDIR):$PATH\" CPPFLAGS=\"$CPPFLAGS -I$(LUA_INCDIR)\" CXXFLAGS=\"$CXXFLAGS -Wall -W -Wno-missing-field-initializers $(CFLAGS)\" LDFLAGS=\"$LDFLAGS -L$(LUA_LIBDIR)\" LUA='$(LUA)' ./configure --prefix='$(PREFIX)' && make";
  install_command = "make luadir='$(LUADIR)' luaexecdir='$(LIBDIR)/dromozoa' install";
}
