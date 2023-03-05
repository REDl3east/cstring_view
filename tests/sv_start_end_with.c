#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_check();
void print_x();

int test_starts_with_char_test(string_view sv, char c, int expected);
int test_ends_with_char_test(string_view sv, char c, int expected);
int test_starts_with_test(string_view sv1, string_view sv2, int expected);
int test_ends_with_test(string_view sv1, string_view sv2, int expected);

int main() {
  if (!test_starts_with_char_test(sv("hello there"), 'h', 1)) return 1;
  if (!test_starts_with_char_test(sv("w"), 'w', 1)) return 1;
  if (!test_starts_with_char_test(sv("Dalton Overmyer"), 'D', 1)) return 1;
  if (!test_starts_with_char_test(sv("what the heck dude"), 'g', 0)) return 1;
  if (!test_starts_with_char_test(sv(""), 'h', 0)) return 1;

  printf("\n");

  if (!test_starts_with_test(sv("hello there"), sv("hello there"), 1)) return 1;
  if (!test_starts_with_test(sv("hello there"), sv("hello th"), 1)) return 1;
  if (!test_starts_with_test(sv("hello there"), sv("hello"), 1)) return 1;
  if (!test_starts_with_test(sv("Dalton Overmyer"), sv("Dalton"), 1)) return 1;
  if (!test_starts_with_test(sv("hello there"), sv("hello there Dalton"), 0)) return 1;
  if (!test_starts_with_test(sv(""), sv(""), 1)) return 1;

  printf("\n");

  if (!test_ends_with_char_test(sv("hello there"), 'e', 1)) return 1;
  if (!test_ends_with_char_test(sv("w"), 'w', 1)) return 1;
  if (!test_ends_with_char_test(sv("Dalton Overmyer"), 'r', 1)) return 1;
  if (!test_ends_with_char_test(sv("There goes my hero"), 'O', 0)) return 1;
  if (!test_ends_with_char_test(sv(""), 'h', 0)) return 1;

  printf("\n");

  if (!test_ends_with_test(sv("hello there"), sv("hello there"), 1)) return 1;
  if (!test_ends_with_test(sv("hello there"), sv("there"), 1)) return 1;
  if (!test_ends_with_test(sv("hello there"), sv("hello"), 0)) return 1;
  if (!test_ends_with_test(sv("Dalton Overmyer"), sv("Overmyer"), 1)) return 1;
  if (!test_ends_with_test(sv("hello there"), sv("hello there Dalton"), 0)) return 1;
  if (!test_ends_with_test(sv(""), sv(""), 1)) return 1;

  return 0;
}

int test_starts_with_char_test(string_view sv, char c, int expected) {
  int tmp = sv_starts_with_char(sv, c);
  if (tmp == expected) {
    print_check();
    if (expected) {
      printf("'" sv_fmt "' starts with '%c'\n", sv_arg(sv), c);
    } else {
      printf("'" sv_fmt "' does not starts with '%c'\n", sv_arg(sv), c);
    }
    return 1;
  } else {
    print_x();
    if (expected) {
      printf("'" sv_fmt "' does not starts with '%c'\n", sv_arg(sv), c);
    } else {
      printf("'" sv_fmt "' starts with '%c'\n", sv_arg(sv), c);
    }
    return 0;
  }
}

int test_ends_with_char_test(string_view sv, char c, int expected) {
  int tmp = sv_ends_with_char(sv, c);
  if (tmp == expected) {
    print_check();
    if (expected) {
      printf("'" sv_fmt "' ends with '%c'\n", sv_arg(sv), c);
    } else {
      printf("'" sv_fmt "' does not end with '%c'\n", sv_arg(sv), c);
    }
    return 1;
  } else {
    print_x();
    if (expected) {
      printf("'" sv_fmt "' does not end with '%c'\n", sv_arg(sv), c);
    } else {
      printf("'" sv_fmt "' ends with '%c'\n", sv_arg(sv), c);
    }
    return 0;
  }
}

int test_starts_with_test(string_view sv1, string_view sv2, int expected) {
  int tmp = sv_starts_with(sv1, sv2);
  if (tmp == expected) {
    print_check();
    if (expected) {
      printf("'" sv_fmt "' starts with '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    } else {
      printf("'" sv_fmt "' does not start with '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    }
    return 1;
  } else {
    print_x();
    if (expected) {
      printf("'" sv_fmt "' does not start with '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    } else {
      printf("'" sv_fmt "' starts with '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    }
    return 0;
  }
}

int test_ends_with_test(string_view sv1, string_view sv2, int expected) {
  int tmp = sv_ends_with(sv1, sv2);
  if (tmp == expected) {
    print_check();
    if (expected) {
      printf("'" sv_fmt "' ends with '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    } else {
      printf("'" sv_fmt "' does not end with '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    }
    return 1;
  } else {
    print_x();
    if (expected) {
      printf("'" sv_fmt "' does not end with '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    } else {
      printf("'" sv_fmt "' ends with '" sv_fmt "'\n", sv_arg(sv1), sv_arg(sv2));
    }
    return 0;
  }
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}