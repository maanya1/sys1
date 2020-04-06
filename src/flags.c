#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "flags.h"
#include "warning.h"

// parse flags separately
Flags* get_flags(int argc, char** argv) {
  int arg_count = argc - 1;

  if (arg_count < 2) {
    Warning_print_fatal_error("You need at least two arguments. Try `-b`, `-c` or `-d` and a file name.");
  }

  Flags* flags = malloc(sizeof(Flags));

  flags->build_codebook = false;
  flags->compress = false;
  flags->decompress = false;
  flags->recursive = false;

  flags->codebook_path = NULL;
  flags->file_path = NULL;

  int flagCount = 0;
  int i = 1;
  for (; i < argc; i++) {
    // if flag is "-b", "-c", "-d", or "-R"
    if (strncmp(argv[i], "-", 1) == 0) {
      if (strlen(argv[i]) == 2) {
        char flag = argv[i][1];

        if (flag == 'b') {
          flags->build_codebook = true;
        } else if (flag == 'c') {
          flags->compress = true;
        } else if (flag == 'd') {
          flags->decompress = true;
        } else if (flag == 'R') {
          if (flagCount > 0) {
            Warning_print_warning("Recursive flag needs to go first.");
          }

          flags->recursive = true;
        } else {
          Warning_print_warning("Unknown flag.");
        }
      } else {
        Warning_print_warning("Can't combine arguments! i.e. Instead of `-bR` try `-b -R`.");
      }

      flagCount++;
    } else if (strncmp(argv[i], ".", 1) == 0 || strncmp(argv[i], "/", 1) == 0) {
      if (flags->file_path == NULL) {
        flags->file_path = argv[i];
      } else {
        flags->codebook_path = argv[i];
      }
    } else {
      Warning_print_warning("Valid flags include '-b', '-c', '-d', and '-R'. All files must start with '.' or '/'.");
    }
  }

  if (flagCount > 2) {
    Warning_print_warning("You can't have more than 2 flags!");
  }

  if ((flags->compress || flags-> decompress ) && flags->codebook_path == NULL) {
    Warning_print_fatal_error("Compress and decompress must specify a codebook.");
  }

  return flags;
}