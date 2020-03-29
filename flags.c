#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "flags.h"

// parse flags separately
Flags* get_flags(int argc, char** argv) {
  Flags* flags = malloc(sizeof(Flags));

  flags->build_codebook = false;
  flags->compress = false;
  flags->decompress = false;
  flags->recursive = false;

  flags->codebook_path = NULL;
  flags->file_path = NULL;

  for (int i = 1; i < argc; i++) {
    // if flag is "-b", "-c", "-d", or "-R"
    if (strncmp(argv[i], "-", 1) == 0 && strlen(argv[i]) == 2) {
      char flag = argv[i][1];

      if (flag == 'b') {
        flags->build_codebook = true;
      } else if (flag == 'c') {
        flags->compress = true;
      } else if (flag == 'd') {
        flags->decompress = true;
      } else if (flag == 'R') {
        flags->recursive = true;
      }
    }

    // if path starts with "."
    if (strncmp(argv[i], ".", 1) == 0) {
      if (flags->file_path == NULL) {
        flags->file_path = argv[i];
      } else {
        flags->codebook_path = argv[i];
      }
    }
  }

  return flags;
}