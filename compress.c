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

#include "compress.h"

void compress(Flags* flags) {
  TreeNode* tree = NULL;
  Token* tokens = Token_read_file(flags->codebook_path);

  while (tokens != NULL) {
    char* encoded = tokens->token;
    tokens = tokens->next->next; // skip tab

    char* word = tokens->token;
    tokens = tokens->next->next; // skip new line

    TreeNode* new = compress_create_node(encoded, word);
    tree = Tree_insert(tree, new);
  }

  if (flags->recursive) {
    listFilesRecursive(flags->file_path, compress_helper, tree);
  } else {
    compress_helper(flags->file_path, tree);
  }
}

void compress_helper(char* pathname, void* data) {
  TreeNode* tree = data;

  // https://stackoverflow.com/questions/5309471/getting-file-extension-in-c
  char *file_extension = strrchr(pathname, '.');
  if (strcmp(file_extension, ".hcz") == 0) return;

  Token* tokens = Token_read_file(pathname);

  if (tokens == NULL) {
    printf("Fatal Error: file\"");
    printf("%s\" ", pathname);
    printf("does not exist\n");
  }

  char* output_filename = malloc(strlen(pathname) + strlen(".hcz") + 1);
  strcpy(output_filename, pathname);
  strcat(output_filename, ".hcz");

  int fd = creat(output_filename, 0777);

  while (tokens != NULL) {
    TreeNode* node = Tree_search(tree, tokens->token);
    char* encoding = node->code;
    
    write(fd, encoding, strlen(encoding));

    tokens = tokens->next;
  }
}