#include "recursive.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// Takes in a 'basePath' and a 'function'.
// Calls the function on every single path.
void listFilesRecursive(char *basePath, void (*some_function)(char *, void *),
                        void *data) {
  DIR *dir = opendir(basePath);

  // Unable to open as directory - must be a file.
  if (dir == NULL) {
    some_function(basePath, data);
    return;
  }

  struct dirent *dp;
  char path[1000];
  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dp->d_name);

      listFilesRecursive(path, some_function, data);
    }
  }

  closedir(dir);
}