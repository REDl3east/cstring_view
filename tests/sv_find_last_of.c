#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

void print_check();
void print_x();

int test_sv_find_last_of(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected);
int test_sv_find_last_not_of(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected);

int main() {
  if (!test_sv_find_last_of(sv("123456"), sv("12"), 3, 1)) return 1;
  if (!test_sv_find_last_of(sv("123456"), sv("12"), SV_NPOS, 1)) return 1;
  if (!test_sv_find_last_of(sv("delete"), sv("cdef"), SV_NPOS, 5)) return 1;
  if (!test_sv_find_last_of(sv("double"), sv("fghi"), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(sv("else"), sv("bcde"), 2, 0)) return 1;
  if (!test_sv_find_last_of(sv("explicit"), sv("abcd"), 4, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(sv("extern"), sv("e"), SV_NPOS, 3)) return 1;
  if (!test_sv_find_last_of(sv("0"), sv("x"), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(sv("inline"), sv("i"), 2, 0)) return 1;
  if (!test_sv_find_last_of(sv("mutable"), sv("a"), 2, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(sv(""), sv(""), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(sv("1234"), sv(""), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(sv(""), sv("1234"), SV_NPOS, SV_NPOS)) return 1;

  printf("\n");

  if (!test_sv_find_last_not_of(sv("BCDEF"), sv("DEF"), SV_NPOS, 1)) return 1;
  if (!test_sv_find_last_not_of(sv("BCDEFG"), sv("EFG"), 3, 2)) return 1;
  if (!test_sv_find_last_not_of(sv("ABBA"), sv("A"), SV_NPOS, 2)) return 1;
  if (!test_sv_find_last_not_of(sv("ABBA"), sv("A"), 0, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(sv("ABBA"), sv("A"), 1, 1)) return 1;
  if (!test_sv_find_last_not_of(sv("ABBA"), sv("AB"), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(sv("ABBAEEEEEGF"), sv("EFGAB"), 7, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(sv(""), sv(""), 0, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(sv("1234"), sv(""), SV_NPOS, 3)) return 1;
  if (!test_sv_find_last_not_of(sv("1234"), sv(""), 2, 2)) return 1;
  if (!test_sv_find_last_not_of(sv(""), sv("1234"), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(sv(""), sv("1234"), 0, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(sv("123456789"), sv("123456"), 0, SV_NPOS)) return 1;


  return 0;
}

int test_sv_find_last_of(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected) {
  sv_index_t tmp = sv_find_last_of(sv1, sv2, pos);

  if (expected == SV_NPOS && tmp == SV_NPOS) {
    print_check();
    printf("Could not find first of '" sv_fmt "' in '" sv_fmt "', sv_find returned SV_NPOS as expected\n", sv_arg(sv2), sv_arg(sv1));
    return 1;
  }

  if (tmp == SV_NPOS && expected != SV_NPOS) {
    print_x();
    printf("Could not find first of '" sv_fmt "' in '" sv_fmt "', sv_find returned SV_NPOS which was not expected\n", sv_arg(sv2), sv_arg(sv1));
    return 0;
  }

  if (tmp == expected) {
    print_check();
    printf("Found first of '" sv_fmt "' in '" sv_fmt "' at index: %ld, starting at index: %ld\n", sv_arg(sv2), sv_arg(sv1), expected, pos);
    return 1;
  } else {
    print_x();
    printf("Did not find first of '" sv_fmt "' in '" sv_fmt "' at index: %ld, found %ld\n", sv_arg(sv2), sv_arg(sv1), expected, tmp);
    return 0;
  }

  return 1;
}

int test_sv_find_last_not_of(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected) {
  sv_index_t tmp = sv_find_last_not_of(sv1, sv2, pos);

  if (expected == SV_NPOS && tmp == SV_NPOS) {
    print_check();
    printf("Could not find first of '" sv_fmt "' in '" sv_fmt "', sv_find returned SV_NPOS as expected\n", sv_arg(sv2), sv_arg(sv1));
    return 1;
  }

  if (tmp == SV_NPOS && expected != SV_NPOS) {
    print_x();
    printf("Could not find first of '" sv_fmt "' in '" sv_fmt "', sv_find returned SV_NPOS which was not expected\n", sv_arg(sv2), sv_arg(sv1));
    return 0;
  }

  if (tmp == expected) {
    print_check();
    printf("Found first of '" sv_fmt "' in '" sv_fmt "' at index: %ld, starting at index: %ld\n", sv_arg(sv2), sv_arg(sv1), expected, pos);
    return 1;
  } else {
    print_x();
    printf("Did not find first of '" sv_fmt "' in '" sv_fmt "' at index: %ld, found %ld\n", sv_arg(sv2), sv_arg(sv1), expected, tmp);
    return 0;
  }

  return 1;
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}