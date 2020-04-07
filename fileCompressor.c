#include <stdlib.h>

#include "build_codebook.h"
#include "compress.h"
#include "decompress.h"
#include "src/flags.h"

int main(int argc, char** argv) {
  Flags* flags = Flags_parse(argc, argv);

  if (flags->build_codebook) {
    build_codebook(flags);
  }

  if (flags->compress) {
    compress(flags);
  }

  if (flags->decompress) {
    decompress(flags);
  }

  free(flags);

  return 0;
}