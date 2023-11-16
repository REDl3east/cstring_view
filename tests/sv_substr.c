#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_check();
void print_x();

int test_sv_substr(string_view sv1, sv_index_t pos, sv_index_t count, string_view expected);

int main() {
  if (!test_sv_substr(svl(""), 0, 0, svl(""))) return 1;
  if (!test_sv_substr(svl("there we go"), 0, SV_NPOS, svl("there we go"))) return 1;
  if (!test_sv_substr(svl("hello there"), 0, 5, svl("hello"))) return 1;
  if (!test_sv_substr(svl("hello there"), 0, SV_NPOS, svl("hello there"))) return 1;
  if (!test_sv_substr(svl("hello there"), 5, 1, svl(" "))) return 1;
  if (!test_sv_substr(svl("hello there"), 1, SV_NPOS, svl("ello there"))) return 1;
  if (!test_sv_substr(svl("hello there"), 6, SV_NPOS, svl("there"))) return 1;
  if (!test_sv_substr(svl("5 + 2 / 88"), 2, 1, svl("+"))) return 1;
  if (!test_sv_substr(svl("5 + 2 / 88"), 2, 0, svl(""))) return 1;
  if (!test_sv_substr(svl("5 + 2 / 88"), 8, SV_NPOS, svl("88"))) return 1;

  // UB
  // if(!test_sv_substr(svl(""), 0, 2, svl("88"))) return 1;

  return 0;
}

int test_sv_substr(string_view sv1, sv_index_t pos, sv_index_t count, string_view expected) {
  string_view tmp = sv_substr(sv1, pos, count);
  if (sv_compare(expected, tmp)) {
    print_check();
    printf("'" sv_fmt "' == '" sv_fmt "'\n", sv_arg(tmp), sv_arg(expected));
    return 1;
  } else {
    print_x();
    printf("'" sv_fmt "' != '" sv_fmt "'\n", sv_arg(tmp), sv_arg(expected));
    return 0;
  }
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}