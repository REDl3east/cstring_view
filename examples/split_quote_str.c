#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

int main() {
  cstring_view input1 = svl("      keyword    \"  quoted string  \" \"\"  keyword \"\"");

  printf("input 1: '" sv_fmt "'\n", sv_arg(input1));

  SV_FOR_SPLIT_QUOTE(tok, input1, '"', '"', svl(" \n")) {
    // detect if empty string
    if (sv_compare(tok, svl("\"\""))) {
      printf("'' ");
    } else {
      printf("'" sv_fmt "' ", sv_arg(tok));
    }
  }
  printf("\n");


  cstring_view input2 = svl("      keyword    (   quoted string   ) ()  keyword ()");

  printf("input 2: '" sv_fmt "'\n", sv_arg(input2));

  SV_FOR_SPLIT_QUOTE(tok, input2, '(', ')', svl(" \n")) {
    // detect if empty string
    if (sv_compare(tok, svl("()"))) {
      printf("'' ");
    } else {
      printf("'" sv_fmt "' ", sv_arg(tok));
    }
  }
  printf("\n");

  return 0;
}
