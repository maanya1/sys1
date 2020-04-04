#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>

#include "flags.h"
#include "tokens.h"
#include "huffman.h"

// Takes in a 'basePath' and a 'function'.
// Calls the function on every single path.
void listFilesRecursive(char *basePath, void (*some_function)(char*, void*), void* data) {
  // Try to open directory.
  DIR *dir = opendir(basePath);

  // Unable to open as directory - must be a file.
  if (dir == NULL) {
    // If it's a file, call the function with the path.
 
    some_function(basePath, data);
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
      listFilesRecursive(path, some_function, data);
    }
  }

  closedir(dir);
}

void compress(char* pathname, void* data) {

  printf("compressing %s\n", pathname);
  
}

void decompress(char* pathname, void* data) {
  printf("decompressing %s\n", pathname);

}

void buildCodebook(char* pathname, void* data) {
  printf("building codebook for %s\n", pathname);
  Token* head = data;
  Token* list = head->next;

  Token* frequencies = Token_read_file_distinct(pathname);

  head->next = Token_merge(list, frequencies);
}

int main(int argc, char** argv) {
  Flags* flags = get_flags(argc, argv);

  if (flags->build_codebook) {
    Token* head = Token_create(NULL);

    if (flags->recursive) {
      listFilesRecursive(flags->file_path, buildCodebook, head);
    } else {
      buildCodebook(flags->file_path, head);
    }

    Token* tokens = head->next;
    TreeNode* huff = Huffman_from_list(tokens);;
    printCodes("./HuffmanCodes", huff);
  }

  if (flags->compress) {
    
  }

  if (flags->decompress) {}

  return 0;
}