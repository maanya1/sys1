#include "build_codebook.h"

#include <string.h>

#include "src/flags.h"
#include "src/free.h"
#include "src/heap.h"
#include "src/huffman.h"
#include "src/recursive.h"
#include "src/tokens.h"

void build_codebook(Flags* flags) {
  Token* head = Token_create(NULL);

  if (flags->recursive) {
    listFilesRecursive(flags->file_path, build_codebook_helper, head);
  } else {
    build_codebook_helper(flags->file_path, head);
  }

  Token* tokens = head->next;
  Token_print(tokens);

  if (tokens != NULL) {
    TreeNode* huff = Huffman_from_list(tokens);
    printCodes("./HuffmanCodes", huff);
    Free_binary_tree(huff);
  }

  Free_tokens_list(head);
}

void build_codebook_helper(char* pathname, void* data) {
  char* file_extension = strrchr(pathname, '.');
  if (strcmp(file_extension, ".hcz") == 0) return;

  Token* head = data;
  Token* list = head->next;

  Token* frequencies = Token_read_file_distinct(pathname);

  head->next = Token_merge(list, frequencies);
}