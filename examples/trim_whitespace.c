#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

string_view sv_trim_left_whitesapce(string_view sv);
string_view sv_trim_right_whitesapce(string_view sv);
string_view sv_trim_whitespace(string_view sv);

int main() {
  string_view sv;

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

string_view sv_trim_left_whitesapce(string_view sv) {
  return sv_consume_until_first_not_of(sv, svl(" \t\n\v\f\r"));
}

string_view sv_trim_right_whitesapce(string_view sv) {
  return sv_consume_until_last_not_of(sv, svl(" \t\n\v\f\r"));
}

string_view sv_trim_whitespace(string_view sv) {
  return sv_trim_left_whitesapce(sv_trim_right_whitesapce(sv));
}