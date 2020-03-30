#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "flags.h"
#include "tokens.h"
typedef struct direct{
  
}

void listFilesRecursive(char *basePath){
  char path[1000];
  struct direct *dp;
  DIR *dir = opendir(basePath);

  //Unable to open directory stream
  if(!dir)
    return;

  while((dp = readdir(dir)) != NULL){
    if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
      printf("%s\n", dp->d_name);
      //construct new path from our base path
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dp->d_name);

      listFilesRecursive(path);
    }
  }
  closeddir(dir);
}

int main(int argc, char** argv) {
  Flags* flags = get_flags(argc, argv);

  TokenNode* tokens = file_to_list(flags->file_path);
  print_tokens(tokens);

  return 0;
}