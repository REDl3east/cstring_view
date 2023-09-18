#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

int test_sv_parse_int(string_view input, int will_fail, int expected);
void print_check();
void print_x();

#define TEST_PARSE_INT(num)                             \
  do {                                                  \
    if (!test_sv_parse_int(sv(#num), 0, num)) return 1; \
  } while (0)

#define TEST_PARSE_INT_FAIL(num)                     \
  do {                                               \
    if (!test_sv_parse_int(sv(num), 1, 0)) return 1; \
  } while (0)

int main() {
  TEST_PARSE_INT(123);
  TEST_PARSE_INT(-123);
  TEST_PARSE_INT(9999);
  TEST_PARSE_INT(-659894);
  TEST_PARSE_INT(2147483647);
  TEST_PARSE_INT(2147483646);
  TEST_PARSE_INT(2147483645);
  TEST_PARSE_INT(2147483644);
  TEST_PARSE_INT(1140083644);
  TEST_PARSE_INT(-2147483648);
  TEST_PARSE_INT(-2147483647);
  TEST_PARSE_INT(-2147483646);
  TEST_PARSE_INT(-2147483645);
  TEST_PARSE_INT(-2140003645);

  TEST_PARSE_INT_FAIL("2147483648");  // overflow
  TEST_PARSE_INT_FAIL("-2147483649"); // underflow
  TEST_PARSE_INT_FAIL("-123   ");
  TEST_PARSE_INT_FAIL("    -123");
  TEST_PARSE_INT_FAIL("    -123   s");
  TEST_PARSE_INT_FAIL("-12fd");
  TEST_PARSE_INT_FAIL("-3432.6");
  TEST_PARSE_INT_FAIL("-1.5E-1");
  TEST_PARSE_INT_FAIL("-122-343");
  TEST_PARSE_INT_FAIL("10000000000000000000000000000000000");
  TEST_PARSE_INT_FAIL("10000000000000000");
  TEST_PARSE_INT_FAIL("-12345646484131646165165184");
  TEST_PARSE_INT_FAIL("-12345646484131646164");

  return 0;
}

int test_sv_parse_int(string_view input, int will_fail, int expected) {
  int inputi;
  if (!sv_parse_int(input, &inputi)) {
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
    printf("Expected parse to fail: '" sv_fmt "' == %d\n", sv_arg(input), inputi);
    return 0;
  }

  if (expected == inputi) {
    print_check();
    printf("'" sv_fmt "' == %d\n", sv_arg(input), inputi);
    return 1;
  }

  print_check();
  printf("'" sv_fmt "' != %d\n", sv_arg(input), inputi);

  return 0;
}

void print_check() {
  printf("[\xE2\x9C\x93] ");
}

void print_x() {
  printf("[x] ");
}