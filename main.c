#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "flags.h"
#include "huffman.h"
#include "tokens.h"

// Takes in a 'basePath' and a 'function'.
// Calls the function on every single path.
void listFilesRecursive(char* basePath, void (*some_function)(char*, void*),
                        void* data) {
  // Try to open directory.
  DIR* dir = opendir(basePath);

  // Unable to open as directory - must be a file.
  if (dir == NULL) {
    // If it's a file, call the function with the path.

    some_function(basePath, data);
    return;
  }

  struct dirent* dp;
  char path[1000];
  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
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

void decompress_helper(char* filename, void* data) {
  char* file_ending = strrchr(filename, '.');
  if (strcmp(file_ending, ".hez") != 0) return;

  char* file_path = strndup(filename, strlen(filename) - 4);

  TreeNode* tree = data;
  int open_fd = open(filename, O_RDONLY, 0777);
  int write_fd = creat(file_path, 0777);

  char* buffer = malloc(sizeof(char));
  while (read(open_fd, buffer, 1) > 0) {
    char token = buffer[0];

    if (token == '0') tree = tree->left;
    if (token == '1') tree = tree->right;
    if (tree->left == NULL && tree->right == NULL) {
      write(write_fd, tree->word, strlen(tree->word));
      tree = data;
    }
  }
}

void decompress(Flags* flags) {
  TreeNode* huff = Huffman_from_codebook(flags->codebook_path);

  if (flags->recursive) {
    listFilesRecursive(flags->file_path, decompress_helper, huff);
  } else {
    decompress_helper(flags->file_path, huff);
  }
}

void compress(char* pathname, void* data) {
  printf("compressing %s\n", pathname);
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
    if (flags->recursive) {
      Token* head = Token_create(NULL);
      listFilesRecursive(flags->file_path, buildCodebook, head);

      Token* tokens = head->next;
      TreeNode* huff = Huffman_from_list(tokens);
      printCodes("./HuffmanCodes.txt", huff);
    } else {
      Token* tokens = Token_read_file_distinct(flags->file_path);
      TreeNode* huff = Huffman_from_list(tokens);
      ;
      printCodes("./HuffmanCodes.txt", huff);
    }
  }

  if (flags->decompress) {
    decompress(flags);
  }

  // listFilesRecursive( flags->file_path, compress );
  // listFilesRecursive( flags->file_path, decompress );
  // listFilesRecursive( flags->file_path, buildCodebook );

  // Token* tokens = Token_read_file_distinct(flags->file_path);

  // TreeNode* huff = Huffman_from_list(tokens);

  // printCodes(huff);

  // if (flags->build_codebook) {}

  // if (flags->compress) {}

  // if (flags->decompress) {}

  return 0;
}