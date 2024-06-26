#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_check();
void print_x();
int test_sv_create(cstring_view sv1, cstring_view sv2);

int main() {
  cstring_view sv;
  const char* cstr;

  sv = sv_create("hello world", 11);
  if (!test_sv_create(sv, svl("hello world"))) return 1;

  sv = sv_create("hello world", 10);
  if (!test_sv_create(sv, svl("hello worl"))) return 1;

  sv = sv_create("hello world extra text", 5);
  if (!test_sv_create(sv, svl("hello"))) return 1;

  sv = sv_create("hello", 1);
  if (!test_sv_create(sv, svl("h"))) return 1;

  sv = sv_create("hello world", 0);
  if (!test_sv_create(sv, svl(""))) return 1;

  sv = sv_create("a bunch of random text", 0);
  if (!test_sv_create(sv, sv_empty)) return 1;

  sv = sv_create_from_cstr("This is a bit of text");
  if (!test_sv_create(sv, svl("This is a bit of text"))) return 1;

  cstr = "This is a bit of text";
  sv   = sv_create_from_cstr(cstr);
  if (!test_sv_create(sv, svl("This is a bit of text"))) return 1;

  cstr = "This    text    ";
  sv   = sv_create_from_cstr(cstr);
  if (!test_sv_create(sv, svl("This    text    "))) return 1;

  sv = sv_create_from_cstr("");
  if (!test_sv_create(sv, svl(""))) return 1;

  sv = sv_create_from_cstr("");
  if (!test_sv_create(sv, sv_empty)) return 1;

  cstr = "";
  sv   = sv_create_from_cstr(cstr);
  if (!test_sv_create(sv, sv_empty)) return 1;

  char* dynstr1 = malloc(sizeof(char) * 16);
  strcpy(dynstr1, "Dalton Overmyer");
  sv = sv_create(dynstr1, 6);
  if (!test_sv_create(sv, svl("Dalton"))) return 1;
  sv = sv_create(dynstr1, 3);
  if (!test_sv_create(sv, svl("Dal"))) return 1;
  free(dynstr1);

  return 0;
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}

int test_sv_create(cstring_view sv1, cstring_view sv2) {
  if (sv_compare(sv1, sv2)) {
    print_check();
    printf("'" sv_fmt "' == '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    return 1;
  } else {
    print_x();
    printf("'" sv_fmt "' != '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    return 0;
  }
}