#include "sv.h"

#include <stdio.h>

int has_html_extension(const char* file) {
  return sv_ends_with(sv_create_from_cstr(file), sv(".html"));
}

int main() {
  const char* file = "index.html";
  if (has_html_extension(file)) {
    printf("'%s' has an .html extension.\n", file);
  } else {
    printf("'%s' does not have an .html extension.\n", file);
  }

  file = "index.css";
  if (has_html_extension(file)) {
    printf("'%s' has an .html extension.\n", file);
  } else {
    printf("'%s' does not have an .html extension.\n", file);
  }

  file = "/home/dalton/documents/home.html";
  if (has_html_extension(file)) {
    printf("'%s' has an .html extension.\n", file);
  } else {
    printf("'%s' does not have an .html extension.\n", file);
  }
  return 0;
}