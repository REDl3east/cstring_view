#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

cstring_view sv_trim_left_whitesapce(cstring_view sv);
cstring_view sv_trim_right_whitesapce(cstring_view sv);
cstring_view sv_trim_whitespace(cstring_view sv);

int main() {
  cstring_view sv;

  sv = sv_trim_whitespace(svl(""));
  printf("'" sv_fmt "'\n", sv_arg(sv));

  sv = sv_trim_whitespace(svl("    \n\t     "));
  printf("'" sv_fmt "'\n", sv_arg(sv));

  sv = sv_trim_whitespace(svl("   \t\n   Dalton Overmyer  \r\v  "));
  printf("'" sv_fmt "'\n", sv_arg(sv));

  sv = sv_trim_whitespace(svl("       There goes my hero\n\n\n\n\n\n"));
  printf("'" sv_fmt "'\n", sv_arg(sv));

  sv = sv_trim_whitespace(svl("There goes my hero"));
  printf("'" sv_fmt "'\n", sv_arg(sv));

}

cstring_view sv_trim_left_whitesapce(cstring_view sv) {
  return sv_consume_until_first_not_of(sv, svl(" \t\n\v\f\r"));
}

cstring_view sv_trim_right_whitesapce(cstring_view sv) {
  return sv_consume_until_last_not_of(sv, svl(" \t\n\v\f\r"));
}

cstring_view sv_trim_whitespace(cstring_view sv) {
  return sv_trim_left_whitesapce(sv_trim_right_whitesapce(sv));
}