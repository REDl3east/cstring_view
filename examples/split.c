#include "sv.h"

#include <stdio.h>

void split_by_char(const char* input, char c);
void split_by_any_of(const char* input, const char* one_of);

int main() {
  split_by_char("hello,th,ere,dude", ',');
  split_by_char("|||||||||Well|Hello|There||||||||", '|');
  split_by_char("There    once       was a dog named     Jimb.", ' ');
  split_by_char("10-24-2012", '-');
  split_by_char("06/26/1996", '/');
  split_by_char("../home/./home/dalton/./Desktop/main.c", '/');

  split_by_any_of("...hello.../...there/man/.and.....woman", "/.");
  split_by_any_of("Dalton was here\n\tThat's cool\t\t\t\tDude\n", " \n\t");
  split_by_any_of("aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ", "abcdefghijklmnopqrstuvwxyz");

  return 0;
}

void split_by_char(const char* input, char c) {
  string_view sv = sv_create_from_cstr(input);

  while (!sv_is_empty(sv)) {
    sv_index_t index = sv_find_char(sv, c, 0);
    if (index == 0) {
      sv = sv_remove_prefix(sv, index + 1);
      continue;
    }

    string_view el = sv_substr(sv, 0, index);
    printf("'" sv_fmt "' ", sv_arg(el));

    if (index == SV_NPOS) break;

    sv = sv_remove_prefix(sv, index + 1);
  }
  printf("\n");
}

void split_by_any_of(const char* input, const char* one_of) {
  string_view input_sv = sv_create_from_cstr(input);
  string_view one_sv   = sv_create_from_cstr(one_of);

  while (!sv_is_empty(input_sv)) {
    sv_index_t index = sv_find_first_of(input_sv, one_sv, 0);
    if (index == 0) {
      input_sv = sv_remove_prefix(input_sv, index + 1);
      continue;
    }

    string_view el = sv_substr(input_sv, 0, index);
    printf("'" sv_fmt "' ", sv_arg(el));

    if (index == SV_NPOS) break;

    input_sv = sv_remove_prefix(input_sv, index + 1);
  }
  printf("\n");
}