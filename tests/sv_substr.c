#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_check();
void print_x();

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

int main() {

  if(!test_sv_substr(sv(""), 0, 0, sv(""))) return 1;
  if(!test_sv_substr(sv("there we go"), 0, SV_NPOS, sv("there we go"))) return 1;
  if(!test_sv_substr(sv("hello there"), 0, 5, sv("hello"))) return 1;
  if(!test_sv_substr(sv("hello there"), 0, SV_NPOS, sv("hello there"))) return 1;
  if(!test_sv_substr(sv("hello there"), 5, 1, sv(" "))) return 1;
  if(!test_sv_substr(sv("hello there"), 1, SV_NPOS, sv("ello there"))) return 1;
  if(!test_sv_substr(sv("hello there"), 6, SV_NPOS, sv("there"))) return 1;
  if(!test_sv_substr(sv("5 + 2 / 88"), 2, 1, sv("+"))) return 1;
  if(!test_sv_substr(sv("5 + 2 / 88"), 2, 0, sv(""))) return 1;
  if(!test_sv_substr(sv("5 + 2 / 88"), 8, SV_NPOS, sv("88"))) return 1;
  
  // UB
  // if(!test_sv_substr(sv(""), 0, 2, sv("88"))) return 1;

  return 0;
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}