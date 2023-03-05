#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_check();
void print_x();
int test_is_empty(string_view sv);
int test_is_not_empty(string_view sv);

int main() {
  if (!test_is_empty(sv(""))) return 1;
  if (!test_is_empty(sv_create("", 0))) return 1;
  if (!test_is_empty(sv_create("There goes my hero", 0))) return 1;
  if (!test_is_empty(sv_create_from_cstr(""))) return 1;
  if (!test_is_empty(sv_substr(sv("hello there"), 0, 0))) return 1;
  if (!test_is_empty(sv_substr(sv("hello there"), 1, 0))) return 1;
  if (!test_is_empty(sv_substr(sv("hello there"), 5, 0))) return 1;
  if (!test_is_empty(sv_remove_prefix(sv("12345"), 5))) return 1;
  if (!test_is_empty(sv_remove_prefix(sv("12345fffff"), 10))) return 1;
  if (!test_is_empty(sv_remove_suffix(sv("12345"), 5))) return 1;
  if (!test_is_empty(sv_remove_suffix(sv("12345asd"), 8))) return 1;

  if (!test_is_not_empty(sv("asdf"))) return 1;
  if (!test_is_not_empty(sv_create("d", 1))) return 1;
  if (!test_is_not_empty(sv_create("There goes my hero", 10))) return 1;
  if (!test_is_not_empty(sv_create_from_cstr("hello"))) return 1;
  if (!test_is_not_empty(sv_substr(sv("hello there"), 0, 1))) return 1;
  if (!test_is_not_empty(sv_substr(sv("hello there"), 1, 2))) return 1;
  if (!test_is_not_empty(sv_substr(sv("hello there"), 5, 3))) return 1;
  if (!test_is_not_empty(sv_remove_prefix(sv("12345"), 3))) return 1;
  if (!test_is_not_empty(sv_remove_prefix(sv("12345fffff"), 5))) return 1;
  if (!test_is_not_empty(sv_remove_suffix(sv("12345"), 2))) return 1;
  if (!test_is_not_empty(sv_remove_suffix(sv("12345asd"), 3))) return 1;

  return 0;
}

int test_is_empty(string_view sv) {
  if (sv_is_empty(sv)) {
    print_check();
    return 1;
  } else {
    print_x();
    return 0;
  }
}

int test_is_not_empty(string_view sv) {
  if (!sv_is_empty(sv)) {
    print_check();
    return 1;
  } else {
    print_x();
    return 0;
  }
}

void print_check() {
  printf("[\xE2\x9C\x93]\n");
}

void print_x() {
  printf("[x]\n");
}