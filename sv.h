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

string_view sv_create(const char* data, sv_index_t length);
string_view sv_create_from_cstr(const char* data);
const char* sv_begin(string_view sv);
const char* sv_end(string_view sv);
char sv_at(string_view sv, sv_index_t index);
char sv_front(string_view sv);
char sv_back(string_view sv);
sv_index_t sv_size(string_view sv);
sv_index_t sv_length(string_view sv);
int sv_is_empty(string_view sv);
string_view sv_remove_prefix(string_view sv, sv_index_t n);
string_view sv_remove_suffix(string_view sv, sv_index_t n);
void sv_swap(string_view sv1, string_view sv2);
string_view sv_substr(string_view sv, sv_index_t pos, sv_index_t count);
int sv_compare(string_view sv1, string_view sv2);
int sv_starts_with(string_view sv1, string_view sv2);
int sv_ends_with(string_view sv1, string_view sv2);
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
sv_index_t sv_cstrlen(const char* str);

string_view sv_create(const char* data, sv_index_t length) {
  string_view sv = {
      .data   = data,
      .length = length,
  };
  return sv;
}

string_view sv_create_from_cstr(const char* data) {
  return sv_create(data, sv_cstrlen(data));
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

sv_index_t sv_size(string_view sv) {
  return sv.length;
}

sv_index_t sv_length(string_view sv) {
  return sv.length;
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
  if (pos == SV_NPOS) count = sv.length - 1;
  return sv_create(sv.data + pos, count < sv.length - pos ? count : sv.length - pos);
}

int sv_compare(string_view sv1, string_view sv2) {
  if (sv1.length != sv2.length) return 0;

  for (int i = 0; i < (int)sv1.length; i++) {
    if (sv1.data[i] != sv2.data[i]) return 0;
  }

  return 1;
}

int sv_starts_with(string_view sv1, string_view sv2) {
  if (sv2.length > sv1.length) return 0;

  for (int i = 0; i < (int)sv2.length; i++) {
    if (sv1.data[i] != sv2.data[i]) return 0;
  }

  return 1;
}

int sv_ends_with(string_view sv1, string_view sv2) {
  if (sv2.length > sv1.length) return 0;

  for (int i = 0; i < (int)sv2.length; i++) {
    if ((sv_end(sv1) - sv2.length + 1)[i] != sv2.data[i]) return 0;
  }

  return 1;
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
  if (sv_is_empty(sv2) || sv_is_empty(sv1)) return SV_NPOS;
  if (sv2.length > sv1.length) return SV_NPOS;

  if (pos == SV_NPOS) pos = 0;

  for (int i = pos; i < (int)sv2.length; i++) {
    string_view v = sv_substr(sv1, pos + i, SV_NPOS);
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
  if (sv_is_empty(sv2) || sv_is_empty(sv1)) return SV_NPOS;
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

  if (pos == SV_NPOS) pos = 0;

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

  if (pos == SV_NPOS) pos = 0;

  for (int i = pos; i < (int)sv.length; i++) {
    if (sv.data[i] != c) return i;
  }

  return SV_NPOS;
}

sv_index_t sv_find_first_not_of(string_view sv1, string_view sv2, sv_index_t pos) {
  if (sv_is_empty(sv2) || sv_is_empty(sv1)) return SV_NPOS;

  if (pos == SV_NPOS) pos = 0;

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
  if (sv_is_empty(sv2) || sv_is_empty(sv1)) return SV_NPOS;

  if (pos == SV_NPOS) pos = sv1.length - 1;

  for (int i = pos; i >= 0; i--) {
    int j;
    for (j = 0; j < (int)sv2.length; j++) {
      if (sv1.data[i] == sv2.data[j]) break;
    }
    if (j == (int)sv2.length) return i;
  }

  return SV_NPOS;
}

sv_index_t sv_cstrlen(const char* str) {
  const char* s;
  for (s = str; *s; ++s)
    ;
  return (s - str);
}

// int main() {
// printf("%d\n", sv_find(sv(" long long int;"), sv("long"), 0));
// printf("%d\n", sv_find(sv(" long long int;"), sv("long"), 2));
// printf("%d\n", sv_find_char(sv(" long long int;"), ' ', 0));
// printf("%d\n", sv_find_char(sv(" long long int;"), 'o', 2));
// printf("%d\n", sv_find(sv(" long long int;"), sv("on"), 1));

// printf("%d\n", sv_rfind(sv("AB AB AB"), sv("AB"), SV_NPOS));
// printf("%d\n", sv_rfind(sv("AB AB AB"), sv("AB"), 5));
// printf("%d\n", sv_rfind(sv("B AB AB"), sv("AB"), 2));
// printf("%d\n", sv_rfind(sv("B AB AB"), sv("AB"), 1));

// printf("%d\n", sv_rfind_char(sv("B AB AB"), 'A', SV_NPOS));
// printf("%d\n", sv_rfind_char(sv("AB AB AB"), 'B', 4));
// printf("%d\n", sv_rfind_char(sv("AB AB AB"), 'C', SV_NPOS));

// printf("%d\n", sv_find_first_of(sv("alignas"), sv("klmn"), SV_NPOS));
// printf("%d\n", sv_find_first_of(sv("alignof"), sv("wxyz"), SV_NPOS));
// printf("%d\n", sv_find_first_of(sv("concept"), sv("bcde"),  1));
// printf("%d\n", sv_find_first_of(sv("consteval"), sv("oxyz"), 2));
// printf("%d\n", sv_find_first_of_char(sv("constexpr"), 'x', SV_NPOS));
// printf("%d\n", sv_find_first_of_char(sv("constinit"), 'x', SV_NPOS));
// printf("%d\n", sv_find_first_of_char(sv("const_cast"), 'c', 4));
// printf("%d\n", sv_find_first_of_char(sv("continue"), 'c', 42));
// printf("%d\n", sv_find_first_of(sv("co_await"), sv("cba"), 4));
// printf("%d\n", sv_find_first_of(sv("co_awa\nit"), sv("\n"), 4));

// printf("%d\n", sv_find_last_of(sv("delete"), sv("cdef"), SV_NPOS));
// printf("%d\n", sv_find_last_of(sv("double"), sv("fghi"), SV_NPOS));
// printf("%d\n", sv_find_last_of(sv("else"), sv("bcde"), 2));
// printf("%d\n", sv_find_last_of(sv("explicit"), sv("abcd"), 4));
// printf("%d\n", sv_find_last_of_char(sv("extern"), 'e', SV_NPOS));
// printf("%d\n", sv_find_last_of_char(sv("0"), 'x', SV_NPOS));
// printf("%d\n", sv_find_last_of_char(sv("inline"), 'i', 2));
// printf("%d\n", sv_find_last_of_char(sv("mutable"), 'a', 2));

// printf("%d\n", sv_find_first_not_of(sv("BCDEF"), sv("ABC"), SV_NPOS));
// printf("%d\n", sv_find_first_not_of(sv("BCDEF"), sv("ABC"), 4));
// printf("%d\n", sv_find_first_not_of_char(sv("BCDEF"), 'B', SV_NPOS));
// printf("%d\n", sv_find_first_not_of_char(sv("BCDEF"), 'D', 2));

// printf("%d\n", sv_find_last_not_of(sv("BCDEF"), sv("DEF"), SV_NPOS));
// printf("%d\n", sv_find_last_not_of(sv("BCDEFG"), sv("EFG"), 3));
// printf("%d\n", sv_find_last_not_of_char(sv("ABBA"), 'A', SV_NPOS));
// printf("%d\n", sv_find_last_not_of_char(sv("ABBA"), 'A', 1));

//   return 0;
// }

#endif