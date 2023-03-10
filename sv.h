#ifndef _SV_H_
#define _SV_H_

#define SV_NPOS (sv_index_t)(-1)

#define sv(cstr_literal) sv_create(cstr_literal, sizeof(cstr_literal) - 1)
#define svc(cstr)        sv_create_from_cstr(cstr)
#define sv_empty         sv("")
#define sv_fmt           "%.*s"
#define sv_arg(sv)       (int)sv.length, sv.data

typedef unsigned long int sv_index_t;

typedef struct string_view {
  const char* data;
  sv_index_t length;
} string_view;

#ifdef __cplusplus
extern "C" {
#endif

string_view sv_create(const char* data, sv_index_t length);
string_view sv_create_from_cstr(const char* data);
const char* sv_begin(string_view sv);
const char* sv_end(string_view sv);
char sv_at(string_view sv, sv_index_t index);
char sv_front(string_view sv);
char sv_back(string_view sv);
int sv_is_empty(string_view sv);
string_view sv_remove_prefix(string_view sv, sv_index_t n);
string_view sv_remove_suffix(string_view sv, sv_index_t n);
void sv_swap(string_view sv1, string_view sv2);
string_view sv_substr(string_view sv, sv_index_t pos, sv_index_t count);
int sv_compare(string_view sv1, string_view sv2);
int sv_starts_with(string_view sv1, string_view sv2);
int sv_starts_with_char(string_view sv1, char c);
int sv_ends_with(string_view sv1, string_view sv2);
int sv_ends_with_char(string_view sv1, char c);
int sv_contains(string_view sv1, string_view sv2);

sv_index_t sv_find_char(string_view sv1, char c, sv_index_t pos);
sv_index_t sv_find(string_view sv1, string_view sv2, sv_index_t pos);
sv_index_t sv_rfind_char(string_view sv1, char c, sv_index_t pos);
sv_index_t sv_rfind(string_view sv1, string_view sv2, sv_index_t pos);

sv_index_t sv_find_first_of_char(string_view sv, char c, sv_index_t pos);
sv_index_t sv_find_first_of(string_view sv1, string_view sv2, sv_index_t pos);
sv_index_t sv_find_last_of_char(string_view sv, char c, sv_index_t pos);
sv_index_t sv_find_last_of(string_view sv1, string_view sv2, sv_index_t pos);
sv_index_t sv_find_first_not_of_char(string_view sv, char c, sv_index_t pos);
sv_index_t sv_find_first_not_of(string_view sv1, string_view sv2, sv_index_t pos);
sv_index_t sv_find_last_not_of_char(string_view sv, char c, sv_index_t pos);
sv_index_t sv_find_last_not_of(string_view sv1, string_view sv2, sv_index_t pos);

string_view sv_consume_until_first_of(string_view sv1, string_view sv2);
string_view sv_consume_until_first_not_of(string_view sv1, string_view sv2);
string_view sv_consume_until_last_of(string_view sv1, string_view sv2);
string_view sv_consume_until_last_not_of(string_view sv1, string_view sv2);

int sv_parse_int(string_view sv, int* value);

char* sv_strdup(string_view sv);

#ifdef __cplusplus
}
#endif

#ifdef SV_IMPLEMENTATION

  #ifdef __cplusplus
    #include <cstdlib>
    #include <cstring>
    #include <cstdint>
    #include <climits>
  #else
    #include <stdlib.h>
    #include <string.h>
    #include <stdint.h>
    #include <limits.h>
  #endif

string_view sv_create(const char* data, sv_index_t length) {
  string_view sv = {
      .data   = data,
      .length = length,
  };
  return sv;
}

string_view sv_create_from_cstr(const char* data) {
  return sv_create(data, strlen(data));
}

const char* sv_begin(string_view sv) {
  return sv.data;
}

const char* sv_end(string_view sv) {
  return sv.data + (sv.length - 1);
}

char sv_at(string_view sv, sv_index_t index) {
  return sv.data[index];
}

char sv_front(string_view sv) {
  return sv_begin(sv)[0];
}

char sv_back(string_view sv) {
  return sv_end(sv)[0];
}

int sv_is_empty(string_view sv) {
  return sv.length == 0;
}

string_view sv_remove_prefix(string_view sv, sv_index_t n) {
  return sv_create(sv.data + n, sv.length - n);
}

string_view sv_remove_suffix(string_view sv, sv_index_t n) {
  return sv_create(sv.data, sv.length - n);
}

void sv_swap(string_view sv1, string_view sv2) {
  string_view tmp = sv1;
  sv1             = sv2;
  sv2             = tmp;
}

string_view sv_substr(string_view sv, sv_index_t pos, sv_index_t count) {
  if (count == SV_NPOS) count = sv.length;
  return sv_create(sv.data + pos, count < sv.length - pos ? count : sv.length - pos);
}

int sv_compare(string_view sv1, string_view sv2) {
  if (sv1.length != sv2.length) return 0;

  for (int i = 0; i < (int)sv1.length; i++) {
    if (sv1.data[i] != sv2.data[i]) return 0;
  }

  return 1;
}

int sv_starts_with_char(string_view sv1, char c) {
  return !sv_is_empty(sv1) && sv_front(sv1) == c;
}

int sv_starts_with(string_view sv1, string_view sv2) {
  if (sv2.length > sv1.length) return 0;

  for (int i = 0; i < (int)sv2.length; i++) {
    if (sv1.data[i] != sv2.data[i]) return 0;
  }

  return 1;
}

int sv_ends_with_char(string_view sv1, char c) {
  return !sv_is_empty(sv1) && sv_back(sv1) == c;
}

int sv_ends_with(string_view sv1, string_view sv2) {
  if (sv2.length > sv1.length) return 0;

  for (int i = 0; i < (int)sv2.length; i++) {
    if ((sv_end(sv1) - sv2.length + 1)[i] != sv2.data[i]) return 0;
  }

  return 1;
}

int sv_contains(string_view sv1, string_view sv2) {
  return sv_find(sv1, sv2, 0) != SV_NPOS;
}

sv_index_t sv_find_char(string_view sv1, char c, sv_index_t pos) {
  if (sv_is_empty(sv1)) return SV_NPOS;
  if (pos == SV_NPOS) pos = 0;

  for (int i = pos; i < (int)sv1.length; i++) {
    if (sv1.data[i] == c) return i;
  }

  return SV_NPOS;
}

sv_index_t sv_find(string_view sv1, string_view sv2, sv_index_t pos) {
  if (sv_is_empty(sv2) && sv_is_empty(sv1)) return 0;
  if (sv2.length > sv1.length) return SV_NPOS;

  if (pos == SV_NPOS) pos = 0;

  for (int i = pos; i < (int)sv1.length; i++) {
    string_view v = sv_substr(sv1, i, sv2.length);
    if (sv_starts_with(v, sv2)) return i;
  }

  return SV_NPOS;
}

sv_index_t sv_rfind_char(string_view sv1, char c, sv_index_t pos) {
  if (sv_is_empty(sv1)) return SV_NPOS;

  if (pos == SV_NPOS) pos = sv1.length - 1;

  for (int i = pos; i >= 0; i--) {
    if (sv1.data[i] == c) return i;
  }

  return SV_NPOS;
}

sv_index_t sv_rfind(string_view sv1, string_view sv2, sv_index_t pos) {
  if (sv_is_empty(sv2) && sv_is_empty(sv1)) return 0;
  if (sv2.length > sv1.length) return SV_NPOS;

  if (pos == SV_NPOS) pos = sv1.length - 1;

  for (int i = pos; i >= 0; i--) {
    string_view v = sv_substr(sv1, i, SV_NPOS);
    if (sv_starts_with(v, sv2)) return i;
  }

  return SV_NPOS;
}

sv_index_t sv_find_first_of_char(string_view sv, char c, sv_index_t pos) {
  return sv_find_char(sv, c, pos);
}

sv_index_t sv_find_first_of(string_view sv1, string_view sv2, sv_index_t pos) {
  if (sv_is_empty(sv2) || sv_is_empty(sv1)) return SV_NPOS;

  for (int i = pos; i < (int)sv1.length; i++) {
    for (int j = 0; j < (int)sv2.length; j++) {
      if (sv1.data[i] == sv2.data[j]) return i;
    }
  }

  return SV_NPOS;
}

sv_index_t sv_find_last_of_char(string_view sv, char c, sv_index_t pos) {
  return sv_rfind_char(sv, c, pos);
}

sv_index_t sv_find_last_of(string_view sv1, string_view sv2, sv_index_t pos) {
  if (sv_is_empty(sv2) || sv_is_empty(sv1)) return SV_NPOS;

  if (pos == SV_NPOS) pos = sv1.length - 1;

  for (int i = pos; i >= 0; i--) {
    for (int j = 0; j < (int)sv2.length; j++) {
      if (sv1.data[i] == sv2.data[j]) return i;
    }
  }

  return SV_NPOS;
}

sv_index_t sv_find_first_not_of_char(string_view sv, char c, sv_index_t pos) {
  if (sv_is_empty(sv)) return SV_NPOS;

  for (int i = pos; i < (int)sv.length; i++) {
    if (sv.data[i] != c) return i;
  }

  return SV_NPOS;
}

sv_index_t sv_find_first_not_of(string_view sv1, string_view sv2, sv_index_t pos) {
  if (sv_is_empty(sv1) && sv_is_empty(sv2)) return 0;

  if (sv_is_empty(sv2)) return 0;

  for (int i = pos; i < (int)sv1.length; i++) {
    int j;
    for (j = 0; j < (int)sv2.length; j++) {
      if (sv1.data[i] == sv2.data[j]) break;
    }
    if (j == (int)sv2.length) return i;
  }

  return SV_NPOS;
}

sv_index_t sv_find_last_not_of_char(string_view sv, char c, sv_index_t pos) {
  if (sv_is_empty(sv)) return SV_NPOS;

  if (pos == SV_NPOS) pos = sv.length - 1;

  for (int i = pos; i >= 0; i--) {
    if (sv.data[i] != c) return i;
  }

  return SV_NPOS;
}

sv_index_t sv_find_last_not_of(string_view sv1, string_view sv2, sv_index_t pos) {
  if (sv_is_empty(sv2) && sv_is_empty(sv1)) return SV_NPOS;
  if (pos == 0) return SV_NPOS;

  if (pos == SV_NPOS) pos = sv1.length - 1;

  if (sv_is_empty(sv2)) return pos;

  for (int i = pos; i >= 0; i--) {
    int j;
    for (j = 0; j < (int)sv2.length; j++) {
      if (sv1.data[i] == sv2.data[j]) break;
    }
    if (j == (int)sv2.length) return i;
  }

  return SV_NPOS;
}

string_view sv_consume_until_first_of(string_view sv1, string_view sv2) {
  sv_index_t index = sv_find_first_of(sv1, sv2, 0);
  if (index == SV_NPOS) return sv_empty;
  return sv_remove_prefix(sv1, index);
}

string_view sv_consume_until_first_not_of(string_view sv1, string_view sv2) {
  sv_index_t index = sv_find_first_not_of(sv1, sv2, 0);
  if (index == SV_NPOS) return sv_empty;
  return sv_remove_prefix(sv1, index);
}

string_view sv_consume_until_last_of(string_view sv1, string_view sv2) {
  sv_index_t index = sv_find_last_of(sv1, sv2, SV_NPOS);
  if (index == SV_NPOS) return sv_empty;
  return sv_remove_suffix(sv1, sv1.length - index - 1);
}

string_view sv_consume_until_last_not_of(string_view sv1, string_view sv2) {
  sv_index_t index = sv_find_last_not_of(sv1, sv2, SV_NPOS);
  if (index == SV_NPOS) return sv_empty;
  return sv_remove_suffix(sv1, sv1.length - index - 1);
}

int sv_parse_int(string_view sv, int* value) {
  if(sv_is_empty(sv)) return 0;

  int negative = 0;

  if(sv_front(sv) == '-'){
    negative = 1;
    sv = sv_remove_prefix(sv, 1);
    if(sv_is_empty(sv)) return 0;
  }

  if (sv_find_first_not_of(sv, sv("0123456789"), 0) != SV_NPOS) return 0;

  uint64_t tmp = 0;
  for (size_t i = 0; i < sv.length; ++i) {
    uint64_t a = tmp * 10;
    uint64_t b = (uint64_t)sv.data[i] - '0';
    if (a > INT_MAX - b) return 0; // overflow
    tmp = a + b;
  }

  *value = tmp;
  if(negative){
    *value *= -1;
  }

  return 1;
}

char* sv_strdup(string_view sv) {
  char* str = malloc(sv.length + 1);
  if (!str) return NULL;
  memcpy(str, sv.data, sv.length + 1);
  str[sv.length] = '\0';
  return str;
}

#endif

#endif
