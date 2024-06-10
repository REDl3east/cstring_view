#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

#define SV_FOR_SPLIT_QUOTE(token, input, open, close, delim)                            \
  for (cstring_view token, sv = sv_split_next_quote(input, delim, open, close, &token); \
       !sv_is_empty(sv) || !sv_is_empty(token);                                         \
       sv = sv_split_next_quote(sv, delim, open, close, &token))

cstring_view sv_split_next_quote(cstring_view input, cstring_view delim, char open_quote, char close_quote, cstring_view* token) {
  // trim left delims
  input = sv_consume_until_first_not_of(input, delim);

  // input was all delims
  if (sv_is_empty(input)) {
    *token = sv_empty;
    return sv_empty;
  }

  if (sv_starts_with_char(input, open_quote)) {
    sv_index_t pos = sv_find_first_of_char(sv_remove_prefix(input, 1), close_quote, 0);

    // empty quoted string
    // will return token with included open close quotes,
    // so the user can detect if it is empty
    if (pos == 0) {
      *token = sv_substr(input, 0, 2);
      return sv_remove_prefix(input, token->length);
    }

    // fallback to keyword
    if (pos == SV_NPOS) {
      sv_index_t pos = sv_find_first_of(input, delim, 0);

      if (pos == SV_NPOS) {
        *token = input;
        return sv_empty;
      }

      *token = sv_substr(input, 0, pos);
      return sv_remove_prefix(input, token->length);
    }

    *token = sv_substr(sv_remove_prefix(input, 1), 0, pos);
    return sv_remove_prefix(sv_remove_prefix(input, 1), token->length + 1); // + 1 for end quote
  } else {
    sv_index_t pos = sv_find_first_of(input, delim, 0);

    // no delim found
    if (pos == SV_NPOS) {
      *token = input;
      return sv_empty;
    }

    *token = sv_substr(input, 0, pos);
    return sv_remove_prefix(input, token->length);
  }
}

int main() {
  cstring_view input1 = svl("      keyword    \"quoted string\" \"\"  keyword \"\"");

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


  cstring_view input2 = svl("      keyword    (quoted string) ()  keyword ()");

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