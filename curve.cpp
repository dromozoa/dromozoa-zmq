// Copyright (C) 2017 Tomoyuki Fujimori <moyu@dromozoa.com>
//
// This file is part of dromozoa-zmq.
//
// dromozoa-zmq is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// dromozoa-zmq is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with dromozoa-zmq.  If not, see <http://www.gnu.org/licenses/>.

#include "common.hpp"

namespace dromozoa {
  namespace {
    size_t initialize_curve_key_size_z85() {
      int major = 0;
      int minor = 0;
      int patch = 0;
      zmq_version(&major, &minor, &patch);
      if (major < 4 || (major == 4 && minor < 1)) {
        return 40;
      } else {
        return 41;
      }
    }
  }

  size_t curve_key_size_z85() {
    static const size_t size = initialize_curve_key_size_z85();
    return size;
  }
}
