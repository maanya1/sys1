#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>

#include "flags.h"
#include "tokens.h"

// Takes in a 'basePath' and a 'function'.
// Calls the function on every single path.
void listFilesRecursive(char *basePath, void (*some_function)(char*)) {
  // Try to open directory.
  DIR *dir = opendir(basePath);

  // Unable to open as directory - must be a file.
  if (dir == NULL) {
    // If it's a file, call the function with the path.
    some_function(basePath);
    return;
  }

  struct dirent *dp;
  char path[1000];
  while((dp = readdir(dir)) != NULL){
    if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
      // construct a new path from our base path
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dp->d_name);

      // recurse on that path
      listFilesRecursive(path, some_function);
    }
  }

  closedir(dir);
}

void compress(char* pathname) {
  printf("compressing %s\n", pathname);
  
}

void decompress(char* pathname) {
  printf("decompressing %s\n", pathname);
}


/*

BUILD CODEBOOK

the end product should look like this:

`HuffmanCodebook`

token     binary
-------------------
a         0
b         101
...


1) get file name (char* filename)
2) read filez into a linked list (Token_read_file_distinct)
 - every linked list node has a frequency and a value
  typedef struct Token {
    char* token;
    int frequency;
    struct Token* next;
  } Token;

3) insert every linked list value into a min heap
insert(heap, token)

*make functon that taken in a list and converts to a
huffman tree?*

while the heap has more than 1 node:
  4) extract the minimum two elements
  5) combine them into one node
  6) add them back to the min heap

7) the last node in the min heap is the final huffman tree
8) use this huffman tree to create a codebook


*/
void buildCodebook(char* pathname) {
  printf("building codebook for %s\n", pathname);
  Token* frequencies = Token_read_file_distinct(pathname);
}

int main(int argc, char** argv) {
  Flags* flags = get_flags(argc, argv);

  listFilesRecursive( flags->file_path, compress );
  listFilesRecursive( flags->file_path, decompress );
  listFilesRecursive( flags->file_path, buildCodebook );

  // Token* tokens = Token_read_file_distinct(flags->file_path);
  // Token_print(tokens);

  // if (flags->build_codebook) {}

  // if (flags->compress) {}

  // if (flags->decompress) {}

  return 0;
}