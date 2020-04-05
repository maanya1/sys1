#include "src/flags.h"
#include "src/tokens.h"
#include "src/huffman.h"
#include "src/binary_tree.h"
#include "src/recursive.h"

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

  return 0;
}