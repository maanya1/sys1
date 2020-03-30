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
  printf("compressing %s...\n", pathname);
}
void decompress(char* pathname) {
  printf("decompressing %s...\n", pathname);
}
void buildCodebook(char* pathname) {
  printf("buidling codebook for %s...\n", pathname);
}

int main(int argc, char** argv) {
  Flags* flags = get_flags(argc, argv);

  listFilesRecursive( flags->file_path, compress );
  listFilesRecursive( flags->file_path, decompress );
  listFilesRecursive( flags->file_path, buildCodebook );

  // TokenNode* tokens = file_to_list(flags->file_path);
  // print_tokens(tokens);

  return 0;
}