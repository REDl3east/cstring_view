#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_check();
void print_x();

int test_sv_find_char(string_view sv, char c, sv_index_t pos, sv_index_t expected);
int test_sv_find(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected);
int test_sv_rfind_char(string_view sv, char c, sv_index_t pos, sv_index_t expected);
int test_sv_rfind(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected);

int main() {
  if (!test_sv_find_char(svl("there we go"), 'w', 0, 6)) return 1;
  if (!test_sv_find_char(svl("MMMMMMMM"), 'M', 4, 4)) return 1;
  if (!test_sv_find_char(svl("A    B     C   A"), 'A', 0, 0)) return 1;
  if (!test_sv_find_char(svl("A    B     C   A"), 'A', 6, 15)) return 1;
  if (!test_sv_find_char(svl("Dalton Overmyer"), 'Z', 0, SV_NPOS)) return 1;
  if (!test_sv_find_char(svl("ABCDEFGHIJKLMNOPQSTUVWXYZ"), 'R', 0, SV_NPOS)) return 1;

  printf("\n");

  if (!test_sv_find(svl("there we go"), svl("we"), 0, 6)) return 1;
  if (!test_sv_find(svl("there we go"), svl("goo"), 0, SV_NPOS)) return 1;
  if (!test_sv_find(svl("AB AB AB AB"), svl("AB"), 0, 0)) return 1;
  if (!test_sv_find(svl("AB AB AB AB"), svl("AB"), 1, 3)) return 1;
  if (!test_sv_find(svl("AB AB AB AB"), svl("AB"), 5, 6)) return 1;
  if (!test_sv_find(svl("AB AB AB ABC"), svl("ABC"), 7, 9)) return 1;
  if (!test_sv_find(svl("Dalton Overmyer"), svl("Overmyer"), 2, 7)) return 1;
  if (!test_sv_find(svl("AB AB AB ABC"), svl("ABC "), 0, SV_NPOS)) return 1;
  if (!test_sv_find(svl("AB AB AB ABC"), svl(""), 0, 0)) return 1;
  if (!test_sv_find(svl(""), svl(""), 0, 0)) return 1;
  if (!test_sv_find(svl(""), svl("asdf"), 0, SV_NPOS)) return 1;

  printf("\n");

  if (!test_sv_rfind_char(svl("B AB AB"), 'A', SV_NPOS, 5)) return 1;
  if (!test_sv_rfind_char(svl("AB AB AB"), 'A', 4, 3)) return 1;
  if (!test_sv_rfind_char(svl("AB AB AB"), 'C', SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_rfind_char(svl(""), 'C', SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_rfind_char(svl("ABCDEFGHIJKLMNOPQSTUVWXYZ"), 'R', SV_NPOS, SV_NPOS)) return 1;

  printf("\n");

  if (!test_sv_rfind(svl("AB AB AB"), svl("AB"), SV_NPOS, 6)) return 1;
  if (!test_sv_rfind(svl("AB AB AB"), svl("AB"), 5, 3)) return 1;
  if (!test_sv_rfind(svl("B AB AB"), svl("AB"), 2, 2)) return 1;
  if (!test_sv_rfind(svl("B AB AB"), svl("AB"), 1, SV_NPOS)) return 1;
  if (!test_sv_rfind(svl(""), svl(""), 0, 0)) return 1;
  if (!test_sv_rfind(svl("ABCDE"), svl(""), 0, 0)) return 1;
  if (!test_sv_rfind(svl(""), svl("ABCDEFG"), 0, SV_NPOS)) return 1;

  return 0;
}

int test_sv_find_char(string_view sv, char c, sv_index_t pos, sv_index_t expected) {
  sv_index_t tmp = sv_find_char(sv, c, pos);

  if (expected == SV_NPOS && tmp == SV_NPOS) {
    print_check();
    printf("Could not find '%c' in '" sv_fmt "', sv_find returned SV_NPOS as expected\n", c, sv_arg(sv));
    return 1;
  }

  if (tmp == SV_NPOS && expected != SV_NPOS) {
    print_x();
    printf("Could not find '%c' in '" sv_fmt "', sv_find returned SV_NPOS which was not expected\n", c, sv_arg(sv));
    return 0;
  }

  if (tmp == expected) {
    print_check();
    printf("Found '%c' in '" sv_fmt "' at index: %ld, starting at index: %ld\n", c, sv_arg(sv), expected, pos);
    return 1;
  } else {
    print_x();
    printf("Did not find '%c' in '" sv_fmt "' at index: %ld, found %ld\n", c, sv_arg(sv), expected, tmp);
    return 0;
  }
}

int test_sv_find(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected) {
  sv_index_t tmp = sv_find(sv1, sv2, pos);

  if (expected == SV_NPOS && tmp == SV_NPOS) {
    print_check();
    printf("Could not find '" sv_fmt "' in '" sv_fmt "', sv_find returned SV_NPOS as expected\n", sv_arg(sv2), sv_arg(sv1));
    return 1;
  }

  if (tmp == SV_NPOS && expected != SV_NPOS) {
    print_x();
    printf("Could not find '" sv_fmt "' in '" sv_fmt "', sv_find returned SV_NPOS which was not expected\n", sv_arg(sv2), sv_arg(sv1));
    return 0;
  }

  if (tmp == expected) {
    print_check();
    printf("Found '" sv_fmt "' in '" sv_fmt "' at index: %ld, starting at index: %ld\n", sv_arg(sv2), sv_arg(sv1), expected, pos);
    return 1;
  } else {
    print_x();
    printf("Did not find '" sv_fmt "' in '" sv_fmt "' at index: %ld, found %ld\n", sv_arg(sv2), sv_arg(sv1), expected, tmp);
    return 0;
  }
}

int test_sv_rfind_char(string_view sv, char c, sv_index_t pos, sv_index_t expected) {
  sv_index_t tmp = sv_rfind_char(sv, c, pos);

  if (expected == SV_NPOS && tmp == SV_NPOS) {
    print_check();
    printf("Could not find '%c' in '" sv_fmt "', sv_find returned SV_NPOS as expected\n", c, sv_arg(sv));
    return 1;
  }

  if (tmp == SV_NPOS && expected != SV_NPOS) {
    print_x();
    printf("Could not find '%c' in '" sv_fmt "', sv_find returned SV_NPOS which was not expected\n", c, sv_arg(sv));
    return 0;
  }

  if (tmp == expected) {
    print_check();
    printf("Found '%c' in '" sv_fmt "' at index: %ld, starting at index: %ld\n", c, sv_arg(sv), expected, pos);
    return 1;
  } else {
    print_x();
    printf("Did not find '%c' in '" sv_fmt "' at index: %ld, found %ld\n", c, sv_arg(sv), expected, tmp);
    return 0;
  }
}

int test_sv_rfind(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected) {
  sv_index_t tmp = sv_rfind(sv1, sv2, pos);

  if (expected == SV_NPOS && tmp == SV_NPOS) {
    print_check();
    printf("Could not find '" sv_fmt "' in '" sv_fmt "', sv_find returned SV_NPOS as expected\n", sv_arg(sv2), sv_arg(sv1));
    return 1;
  }

  if (tmp == SV_NPOS && expected != SV_NPOS) {
    print_x();
    printf("Could not find '" sv_fmt "' in '" sv_fmt "', sv_find returned SV_NPOS which was not expected\n", sv_arg(sv2), sv_arg(sv1));
    return 0;
  }

  if (tmp == expected) {
    print_check();
    printf("Found '" sv_fmt "' in '" sv_fmt "' at index: %ld, starting at index: %ld\n", sv_arg(sv2), sv_arg(sv1), expected, pos);
    return 1;
  } else {
    print_x();
    printf("Did not find '" sv_fmt "' in '" sv_fmt "' at index: %ld, found %ld\n", sv_arg(sv2), sv_arg(sv1), expected, tmp);
    return 0;
  }
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}