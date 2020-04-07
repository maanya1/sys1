#include "compress.h"

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

void compress(Flags* flags) {
  TreeNode* tree = NULL;
  Token* tokens = Token_read_file(flags->codebook_path);

  if (tokens == NULL) {
    Warning_print_warning("Codebook was empty.");
    return;
  }

  Token* ptr = tokens;
  while (ptr != NULL) {
    char* encoded = ptr->token;
    ptr = ptr->next->next;  // Tab

    char* word = ptr->token;
    ptr = ptr->next->next;  // Newline

    TreeNode* new = TreeNode_create_encoding(encoded, word);
    tree = Tree_insert(tree, new);
  }

  if (flags->recursive) {
    listFilesRecursive(flags->file_path, compress_helper, tree);
  } else {
    compress_helper(flags->file_path, tree);
  }

  Free_tokens_list(tokens);
  Free_binary_tree(tree);
}

void compress_helper(char* pathname, void* data) {
  TreeNode* tree = data;

  char* file_extension = strrchr(pathname, '.');
  if (strcmp(file_extension, ".hcz") == 0) return;

  Token* tokens = Token_read_file(pathname);

  if (tokens == NULL) {
    Warning_print_warning("File was empty and was not compressed.");
  }

  char* output_filename = malloc(strlen(pathname) + strlen(".hcz") + 1);
  strcpy(output_filename, pathname);
  strcat(output_filename, ".hcz");

  int fd = creat(output_filename, 0777);

  free(output_filename);
  Token* ptr = tokens;
  while (ptr != NULL) {
    TreeNode* node = Tree_search(tree, ptr->token);
    char* encoding = node->code;

    write(fd, encoding, strlen(encoding));
    ptr = ptr->next;
  }

  Free_tokens_list(tokens);
  close(fd);
}