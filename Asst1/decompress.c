#include "decompress.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "src/binary_tree.h"
#include "src/flags.h"
#include "src/free.h"
#include "src/huffman.h"
#include "src/recursive.h"
#include "src/tokens.h"
#include "src/warning.h"

void decompress(Flags* flags) {
  TreeNode* huff = Huffman_from_codebook(flags->codebook_path);

  if (flags->recursive) {
    listFilesRecursive(flags->file_path, decompress_helper, huff);
  } else {
    decompress_helper(flags->file_path, huff);
  }

  Free_binary_tree(huff);
}

void decompress_helper(char* filename, void* data) {
  TreeNode* tree = data;

  char* file_ending = strrchr(filename, '.');
  if (strcmp(file_ending, ".hcz") != 0) return;

  char* file_path = strndup(filename, strlen(filename) - 4);
  int read_fd = open(filename, O_RDONLY, 0777);

  if (read_fd < 0) {
    Warning_print_warning("File could not be opened.");
    return;
  }

  int write_fd = creat(file_path, 0777);
  free(file_path);

  if (write_fd < 0) {
    Warning_print_warning("File could not be decompressed.");
    return;
  }

  char* buffer = malloc(sizeof(char));
  while (read(read_fd, buffer, 1) > 0) {
    char token = buffer[0];

    if (token == '0') tree = tree->left;
    if (token == '1') tree = tree->right;
    if (tree->left == NULL && tree->right == NULL) {
      write(write_fd, tree->word, strlen(tree->word));
      tree = data;
    }
  }

  free(buffer);
  close(write_fd);
  close(read_fd);
}