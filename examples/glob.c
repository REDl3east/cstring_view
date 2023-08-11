#define SV_IMPLEMENTATION
#include "sv.h"

#include <stdio.h>

int sv_glob(string_view sv, string_view pattern){

    // find first *, consume repeating

    return 0;
}

int main() {
  string_view sv = sv("hello world");
  string_view pattern = sv("hello?world");

  if(sv_glob(sv, pattern)){
  string_view sv = sv("hello world");
    printf("'" sv_fmt "' matches pattern '" sv_fmt "'\n", sv_arg(sv), sv_arg(pattern));
  }else{
    printf("'" sv_fmt "' does not match pattern '" sv_fmt "'\n", sv_arg(sv), sv_arg(pattern));
  }

  return 0;
}