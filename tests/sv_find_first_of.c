#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

void print_check();
void print_x();

int test_sv_find_first_of(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected);
int test_sv_find_first_not_of(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected);

int main() {
  if (!test_sv_find_first_of(sv("123456789"), sv("45"), 0, 3)) return 1;
  if (!test_sv_find_first_of(sv("123456789"), sv("54"), 0, 3)) return 1;
  if (!test_sv_find_first_of(sv("alignas"), sv("klmn"), 0, 1)) return 1;
  if (!test_sv_find_first_of(sv("alignof"), sv("wxyz"), 1, SV_NPOS)) return 1;
  if (!test_sv_find_first_of(sv("concept"), sv("bcde"), 1, 3)) return 1;
  if (!test_sv_find_first_of(sv("constexpr"), sv("x"), 4, 6)) return 1;
  if (!test_sv_find_first_of(sv("constinit"), sv("x"), 4, SV_NPOS)) return 1;
  if (!test_sv_find_first_of(sv("co await"), sv("cba"), 42, SV_NPOS)) return 1;
  if (!test_sv_find_first_of(sv("co awa\nit"), sv("\n\t"), 0, 6)) return 1;
  if (!test_sv_find_first_of(sv(""), sv("abce"), 0, SV_NPOS)) return 1;
  if (!test_sv_find_first_of(sv(""), sv(""), 0, SV_NPOS)) return 1;
  if (!test_sv_find_first_of(sv("12345"), sv(""), 0, SV_NPOS)) return 1;

  printf("\n");

  if (!test_sv_find_first_not_of(sv("123456789"), sv("123456"), 0, 6)) return 1;
  if (!test_sv_find_first_not_of(sv("123456789"), sv("123456"), 3, 6)) return 1;
  if (!test_sv_find_first_not_of(sv("BCDEF"), sv("ABC"), 3, 3)) return 1;
  if (!test_sv_find_first_not_of(sv("BCDEF"), sv("ABC"), 4, 4)) return 1;
  if (!test_sv_find_first_not_of(sv("BCDBEFB"), sv("B"), 1, 1)) return 1;
  if (!test_sv_find_first_not_of(sv("BCDBEFBE"), sv("B"), 4, 4)) return 1;
  if (!test_sv_find_first_not_of(sv("123"), sv("123"), 0, SV_NPOS)) return 1;
  if (!test_sv_find_first_not_of(sv("123"), sv("123456"), 0, SV_NPOS)) return 1;
  if (!test_sv_find_first_not_of(sv(""), sv(""), 0, 0)) return 1;
  if (!test_sv_find_first_not_of(sv(""), sv("1234"), 0, SV_NPOS)) return 1;
  if (!test_sv_find_first_not_of(sv("1234"), sv(""), 0, 0)) return 1;


  return 0;
}

int test_sv_find_first_of(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected) {
  sv_index_t tmp = sv_find_first_of(sv1, sv2, pos);

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

int test_sv_find_first_not_of(string_view sv1, string_view sv2, sv_index_t pos, sv_index_t expected) {
  sv_index_t tmp = sv_find_first_not_of(sv1, sv2, pos);

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