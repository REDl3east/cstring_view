#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>
#include <errno.h>

int main() {

  string_view sv;
  if(!sv_read_file(__FILE__, &sv)){
    printf("Failed to read file: %s\n", strerror(errno));
    return 1;
  }

  printf(sv_fmt"\n", sv_arg(sv));

  // must free the data allocated by sv_read_file
  sv_read_file_free(sv);

  return 0;
}