#include <stdlib.h>

#include "src/flags.h"

#include "build_codebook.h"
#include "decompress.h"
#include "compress.h"

int main(int argc, char** argv) {
  Flags* flags = get_flags(argc, argv);

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