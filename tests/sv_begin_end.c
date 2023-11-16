#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_check();
void print_x();
int test_sv_begin_end_equal(string_view sv);
int test_sv_begin_end_not_equal(string_view sv);

int main() {
  string_view sv;

  sv = sv_empty;
  if (sv_is_empty(sv)) { // good to note that if a string_view is empty, then it is UB to access the end ptr of the data.
    print_check();
    printf("sv is empty\n");
  } else {
    print_x();
    printf("sv is not empty\n");
    return 1;
  }

  sv = svl("1");
  if (!test_sv_begin_end_equal(sv)) return 1;
  if (!test_sv_begin_end_equal(sv_create("hello", 1))) return 1;
  if (!test_sv_begin_end_equal(sv_create_from_cstr("X"))) return 1;
  if (!test_sv_begin_end_equal(sv_create_from_cstr("Dalton" + 5))) return 1;

  char* dynstr = malloc(sizeof(char) * 1);
  *dynstr      = '!';
  sv           = sv_create(dynstr, 1);
  if (!test_sv_begin_end_equal(sv)) return 1;
  free(dynstr);

  sv = svl("12");
  if (!test_sv_begin_end_not_equal(sv)) return 1;
  if (!test_sv_begin_end_not_equal(sv_create("hello", 2))) return 1;
  if (!test_sv_begin_end_not_equal(sv_create_from_cstr(":)"))) return 1;
  if (!test_sv_begin_end_not_equal(sv_create_from_cstr("Dalton"))) return 1;

  dynstr    = malloc(sizeof(char) * 2);
  dynstr[0] = '!';
  dynstr[1] = '!';
  sv        = sv_create(dynstr, 2);
  if (!test_sv_begin_end_not_equal(sv)) return 1;
  free(dynstr);

  return 0;
}

int test_sv_begin_end_equal(string_view sv) {
  if (sv_begin(sv) != sv_end(sv)) {
    print_x();
    printf("'" sv_fmt "' begin != '" sv_fmt "' end\n", sv_arg(sv), sv_arg(sv));
    return 0;
  } else {
    print_check();
    printf("'" sv_fmt "' begin == '" sv_fmt "' end\n", sv_arg(sv), sv_arg(sv));
    return 1;
  }
}

int test_sv_begin_end_not_equal(string_view sv) {
  if (sv_begin(sv) == sv_end(sv)) {
    print_x();
    printf("'" sv_fmt "' begin == '" sv_fmt "' end\n", sv_arg(sv), sv_arg(sv));
    return 0;
  } else {
    print_check();
    printf("'" sv_fmt "' begin != '" sv_fmt "' end\n", sv_arg(sv), sv_arg(sv));
    return 1;
  }
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}