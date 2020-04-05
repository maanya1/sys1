#include "boolean.h"

#ifndef FLAGS_H
#define FLAGS_H

typedef struct Flags {
  boolean build_codebook;
  boolean compress;
  boolean decompress;
  boolean recursive;

  char* file_path;
  char* codebook_path;
} Flags;

Flags* get_flags(int argc, char** argv);

#endif