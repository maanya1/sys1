#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "src/flags.h"
#include "src/tokens.h"
#include "src/huffman.h"
#include "src/binary_tree.h"
#include "src/recursive.h"

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