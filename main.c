#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "flags.h"
#include "tokens.h"

int main(int argc, char** argv) {
  Flags* flags = get_flags(argc, argv);

  TokenNode* tokens = file_to_list(flags->file_path);
  print_tokens(tokens);

  return 0;
}