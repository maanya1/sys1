#include "src/flags.h"

#ifndef BUILD_CODEBOOK_H
#define BUILD_CODEBOOK_H

void build_codebook(Flags* flags);
void build_codebook_helper(char* pathname, void* data);

#endif