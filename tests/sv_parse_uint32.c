#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

int test_sv_parse_uint32(cstring_view input, int will_fail, uint32_t expected);
void print_check();
void print_x();

#define TEST_PARSE_UINT32(num)                              \
  do {                                                     \
    if (!test_sv_parse_uint32(svl(#num), 0, num)) return 1; \
  } while (0)

#define TEST_PARSE_UINT32_FAIL(num)                      \
  do {                                                  \
    if (!test_sv_parse_uint32(svl(num), 1, 0)) return 1; \
  } while (0)

int main() {
  TEST_PARSE_UINT32(4294967295);
  TEST_PARSE_UINT32(54345);
  TEST_PARSE_UINT32(454);
  TEST_PARSE_UINT32(2343);
  TEST_PARSE_UINT32(54545);
  TEST_PARSE_UINT32(34534);
  TEST_PARSE_UINT32(534534);
  TEST_PARSE_UINT32(5445);
  TEST_PARSE_UINT32(4545);
  TEST_PARSE_UINT32(0);
  TEST_PARSE_UINT32(1);

  TEST_PARSE_UINT32_FAIL("4294967296");  // overflow
  TEST_PARSE_UINT32_FAIL("-123"); // uint32 can't be negative
  TEST_PARSE_UINT32_FAIL("-123   ");
  TEST_PARSE_UINT32_FAIL("    -123");
  TEST_PARSE_UINT32_FAIL("    -123   s");
  TEST_PARSE_UINT32_FAIL("-12fd");
  TEST_PARSE_UINT32_FAIL("-3432.6");
  TEST_PARSE_UINT32_FAIL("-1.5E-1");
  TEST_PARSE_UINT32_FAIL("-122-343");
  TEST_PARSE_UINT32_FAIL("10000000000000000000000000000000000");
  TEST_PARSE_UINT32_FAIL("4654654651651651616516516165165165454654");
  TEST_PARSE_UINT32_FAIL("-12345646484131646165165184");
  TEST_PARSE_UINT32_FAIL("-12345646484131646164");

  return 0;
}

int test_sv_parse_uint32(cstring_view input, int will_fail, uint32_t expected) {
  uint32_t inputi;
  if (!sv_parse_uint32(input, &inputi)) {
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
    printf("Expected parse to fail: '" sv_fmt "' == %u\n", sv_arg(input), inputi);
    return 0;
  }

  if (expected == inputi) {
    print_check();
    printf("'" sv_fmt "' == %u\n", sv_arg(input), inputi);
    return 1;
  }

  print_check();
  printf("'" sv_fmt "' != %u\n", sv_arg(input), inputi);

  return 0;
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}