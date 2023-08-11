#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

int sv_glob(string_view sv, string_view pattern){
    
    return 0;
}

int main() {
  string_view sv = sv("hello world\n");

  printf(sv_fmt, sv_arg(sv));

  return 0;
}