#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  cstring_view sv;

  if (!sv_read_file_stdin(&sv)) {
    fprintf(stderr, "sv_read_file_stdin failed\n");
    return 1;
  }

  printf("\n" sv_fmt "\n", sv_arg(sv));

  sv_read_file_free(sv);

  return 0;
}