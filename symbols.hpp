#ifndef DROMOZOA_SYMBOLS_HPP
#define DROMOZOA_SYMBOLS_HPP

#include "common.hpp"

namespace dromozoa {
  enum getsockopt_option_enum {
    getsockopt_option_unknown,
    getsockopt_option_binary_data,
    getsockopt_option_binary_data_or_Z85_text_string,
    getsockopt_option_character_string,
    getsockopt_option_int,
    getsockopt_option_int64_t,
    getsockopt_option_uint64_t,
  };

  enum setsockopt_option_enum {
    setsockopt_option_unknown,
    setsockopt_option_binary_data,
    setsockopt_option_binary_data_or_Z85_text_string,
    setsockopt_option_character_string,
    setsockopt_option_gid_t,
    setsockopt_option_int,
    setsockopt_option_int64_t,
    setsockopt_option_pid_t,
    setsockopt_option_uid_t,
    setsockopt_option_uint64_t,
  };

  void initialize_symbols(lua_State* L);
  getsockopt_option_enum getsockopt_option(int name);
  setsockopt_option_enum setsockopt_option(int name);
}

#endif
