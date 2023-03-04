#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_check();
void print_x();
int test_sv_create(string_view sv1, string_view sv2);

int main() {
  string_view sv;
  const char* cstr;

  sv = sv_create("hello world", 11);
  if (!test_sv_create(sv, sv("hello world"))) return 1;

  sv = sv_create("hello world", 10);
  if (!test_sv_create(sv, sv("hello worl"))) return 1;

  sv = sv_create("hello world extra text", 5);
  if (!test_sv_create(sv, sv("hello"))) return 1;

  sv = sv_create("hello", 1);
  if (!test_sv_create(sv, sv("h"))) return 1;

  sv = sv_create("hello world", 0);
  if (!test_sv_create(sv, sv(""))) return 1;

  sv = sv_create("a bunch of random text", 0);
  if (!test_sv_create(sv, sv_empty)) return 1;

  sv = sv_create_from_cstr("This is a bit of text");
  if (!test_sv_create(sv, sv("This is a bit of text"))) return 1;

  cstr = "This is a bit of text";
  sv   = sv_create_from_cstr(cstr);
  if (!test_sv_create(sv, sv("This is a bit of text"))) return 1;

  cstr = "This    text    ";
  sv   = sv_create_from_cstr(cstr);
  if (!test_sv_create(sv, sv("This    text    "))) return 1;

  sv = sv_create_from_cstr("");
  if (!test_sv_create(sv, sv(""))) return 1;

  sv = sv_create_from_cstr("");
  if (!test_sv_create(sv, sv_empty)) return 1;

  cstr = "";
  sv   = sv_create_from_cstr(cstr);
  if (!test_sv_create(sv, sv_empty)) return 1;

  char* dynstr1 = malloc(sizeof(char) * 16);
  strcpy(dynstr1, "Dalton Overmyer");
  sv = sv_create(dynstr1, 6);
  if (!test_sv_create(sv, sv("Dalton"))) return 1;
  sv = sv_create(dynstr1, 3);
  if (!test_sv_create(sv, sv("Dal"))) return 1;
  free(dynstr1);

  return 0;
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}

int test_sv_create(string_view sv1, string_view sv2) {
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