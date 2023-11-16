#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_check();
void print_x();

int test_at(string_view sv, sv_index_t index, char expected);
int test_front(string_view sv, char expected);
int test_back(string_view sv, char expected);

int main() {
  string_view sv;

  sv = svl("What is some random text?");
  if (!test_at(sv, 0, 'W')) return 1;
  if (!test_at(sv, 1, 'h')) return 1;
  if (!test_at(sv, 2, 'a')) return 1;
  if (!test_at(sv, 3, 't')) return 1;
  if (!test_at(sv, 24, '?')) return 1;
  if (!test_at(sv, 20, 't')) return 1;
  if (!test_front(sv, 'W')) return 1;
  if (!test_back(sv, '?')) return 1;
  sv = sv_create_from_cstr("!dZhZxZZbZZxZxZZZZxZZtnxrx");
  if (!test_at(sv, 5, 'x')) return 1;
  if (!test_at(sv, 11, 'x')) return 1;
  if (!test_at(sv, 18, 'x')) return 1;
  if (!test_at(sv, 25, 'x')) return 1;
  if (!test_front(sv, '!')) return 1;
  if (!test_back(sv, 'x')) return 1;

  sv = sv_create("hello there person", 6);
  if (!test_at(sv, 4, 'o')) return 1;
  if (!test_front(sv, 'h')) return 1;
  if (!test_back(sv, ' ')) return 1;
  return 0;
}

int test_at(string_view sv, sv_index_t index, char expected) {
  if (sv_at(sv, index) == expected) {
    print_check();
    printf("'" sv_fmt "' at %ld == '%c'\n", sv_arg(sv), index, expected);
    return 1;
  } else {
    print_x();
    printf("'" sv_fmt "' at %ld != '%c'\n", sv_arg(sv), index, expected);
    return 0;
  }
}

int test_front(string_view sv, char expected) {
  if (sv_front(sv) == expected) {
    print_check();
    printf("'" sv_fmt "' front == '%c'\n", sv_arg(sv), expected);
    return 1;
  } else {
    print_x();
    printf("'" sv_fmt "' front != '%c'\n", sv_arg(sv), expected);
    return 0;
  }
}

int test_back(string_view sv, char expected) {
  if (sv_back(sv) == expected) {
    print_check();
    printf("'" sv_fmt "' back == '%c'\n", sv_arg(sv), expected);
    return 1;
  } else {
    print_x();
    printf("'" sv_fmt "' back != '%c'\n", sv_arg(sv), expected);
    return 0;
  }
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}