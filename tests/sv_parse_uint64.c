#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

int test_sv_parse_uint64(string_view input, int will_fail, uint64_t expected);
void print_check();
void print_x();

#define TEST_PARSE_UINT64(num)                                                   \
  do {                                                                           \
    if (!test_sv_parse_uint64(sv_remove_suffix(svl(#num), 2), 0, num)) return 1; \
  } while (0)

#define TEST_PARSE_UINT64_FAIL(num)                      \
  do {                                                   \
    if (!test_sv_parse_uint64(svl(num), 1, 0)) return 1; \
  } while (0)

int main() {
  TEST_PARSE_UINT64(123UL);
  TEST_PARSE_UINT64(18446744073709551615UL);
  TEST_PARSE_UINT64(8446744073709551616UL);
  TEST_PARSE_UINT64(5623547895632145896UL);
  TEST_PARSE_UINT64(234234234UL);
  TEST_PARSE_UINT64(234343UL);
  TEST_PARSE_UINT64(45453456UL);
  TEST_PARSE_UINT64(23UL);
  TEST_PARSE_UINT64(0UL);

  TEST_PARSE_UINT64_FAIL("18446744073709551616"); // overflow
  TEST_PARSE_UINT64_FAIL("-123");                 // uint64 can't be negative
  TEST_PARSE_UINT64_FAIL("-123   ");
  TEST_PARSE_UINT64_FAIL("    -123");
  TEST_PARSE_UINT64_FAIL("    -123   s");
  TEST_PARSE_UINT64_FAIL("-12fd");
  TEST_PARSE_UINT64_FAIL("-3432.6");
  TEST_PARSE_UINT64_FAIL("-1.5E-1");
  TEST_PARSE_UINT64_FAIL("-122-343");
  TEST_PARSE_UINT64_FAIL("10000000000000000000000000000000000");
  TEST_PARSE_UINT64_FAIL("4654654651651651616516516165165165454654");
  TEST_PARSE_UINT64_FAIL("-12345646484131646165165184");
  TEST_PARSE_UINT64_FAIL("-12345646484131646164");

  return 0;
}

int test_sv_parse_uint64(string_view input, int will_fail, uint64_t expected) {
  uint64_t inputi;
  if (!sv_parse_uint64(input, &inputi)) {
    if (will_fail) {
      print_check();
      printf("Expected parse failure: '" sv_fmt "'\n", sv_arg(input));
      return 1;
    } else {
      print_x();
      printf("Unexpected parse failure: '" sv_fmt "'\n", sv_arg(input));
      return 0;
    }
  }

  if (will_fail) {
    print_x();
    printf("Expected parse to fail: '" sv_fmt "' == %lu\n", sv_arg(input), inputi);
    return 0;
  }

  if (expected == inputi) {
    print_check();
    printf("'" sv_fmt "' == %lu\n", sv_arg(input), inputi);
    return 1;
  }

  print_check();
  printf("'" sv_fmt "' != %lu\n", sv_arg(input), inputi);

  return 0;
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}