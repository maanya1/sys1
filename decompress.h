#include "src/flags.h"

#ifndef DECOMPRESS_H
#define DECOMPRESS_H

void decompress_helper(char* filename, void* data);
void decompress(Flags* flags);

#endif