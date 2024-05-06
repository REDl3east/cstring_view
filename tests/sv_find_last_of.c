#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

void print_check();
void print_x();

int test_sv_find_last_of(cstring_view sv1, cstring_view sv2, sv_index_t pos, sv_index_t expected);
int test_sv_find_last_not_of(cstring_view sv1, cstring_view sv2, sv_index_t pos, sv_index_t expected);

int main() {
  if (!test_sv_find_last_of(svl("123456"), svl("12"), 3, 1)) return 1;
  if (!test_sv_find_last_of(svl("123456"), svl("12"), SV_NPOS, 1)) return 1;
  if (!test_sv_find_last_of(svl("delete"), svl("cdef"), SV_NPOS, 5)) return 1;
  if (!test_sv_find_last_of(svl("double"), svl("fghi"), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(svl("else"), svl("bcde"), 2, 0)) return 1;
  if (!test_sv_find_last_of(svl("explicit"), svl("abcd"), 4, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(svl("extern"), svl("e"), SV_NPOS, 3)) return 1;
  if (!test_sv_find_last_of(svl("0"), svl("x"), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(svl("inline"), svl("i"), 2, 0)) return 1;
  if (!test_sv_find_last_of(svl("mutable"), svl("a"), 2, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(svl(""), svl(""), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(svl("1234"), svl(""), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_of(svl(""), svl("1234"), SV_NPOS, SV_NPOS)) return 1;

  printf("\n");

  if (!test_sv_find_last_not_of(svl("BCDEF"), svl("DEF"), SV_NPOS, 1)) return 1;
  if (!test_sv_find_last_not_of(svl("BCDEFG"), svl("EFG"), 3, 2)) return 1;
  if (!test_sv_find_last_not_of(svl("ABBA"), svl("A"), SV_NPOS, 2)) return 1;
  if (!test_sv_find_last_not_of(svl("ABBA"), svl("A"), 0, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(svl("ABBA"), svl("A"), 1, 1)) return 1;
  if (!test_sv_find_last_not_of(svl("ABBA"), svl("AB"), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(svl("ABBAEEEEEGF"), svl("EFGAB"), 7, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(svl(""), svl(""), 0, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(svl("1234"), svl(""), SV_NPOS, 3)) return 1;
  if (!test_sv_find_last_not_of(svl("1234"), svl(""), 2, 2)) return 1;
  if (!test_sv_find_last_not_of(svl(""), svl("1234"), SV_NPOS, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(svl(""), svl("1234"), 0, SV_NPOS)) return 1;
  if (!test_sv_find_last_not_of(svl("123456789"), svl("123456"), 0, SV_NPOS)) return 1;


  return 0;
}

int test_sv_find_last_of(cstring_view sv1, cstring_view sv2, sv_index_t pos, sv_index_t expected) {
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

int test_sv_find_last_not_of(cstring_view sv1, cstring_view sv2, sv_index_t pos, sv_index_t expected) {
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