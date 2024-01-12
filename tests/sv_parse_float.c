#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

int test_sv_parse_float(string_view input, int will_fail, float expected);
void print_check();
void print_x();

#define TEST_PARSE_FLOAT(num)                              \
  do {                                                     \
    if (!test_sv_parse_float(svl(#num), 0, num)) return 1; \
  } while (0)

#define TEST_PARSE_FLOAT_FAIL(num)                      \
  do {                                                  \
    if (!test_sv_parse_float(svl(num), 1, 0)) return 1; \
  } while (0)

int main() {
  TEST_PARSE_FLOAT(10.5);

  return 0;
}

int test_sv_parse_float(string_view input, int will_fail, float expected) {
  int inputi;
  if (!sv_parse_float(input, &inputi)) {
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