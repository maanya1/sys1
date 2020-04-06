#include "build_codebook.h"

#include "src/tokens.h"
#include "src/flags.h"
#include "src/huffman.h"
#include "src/heap.h"
#include "src/recursive.h"

void build_codebook(Flags* flags) {
  Token* head = Token_create(NULL);

  if (flags->recursive) {
    listFilesRecursive(flags->file_path, build_codebook_helper, head);
  } else {
    build_codebook_helper(flags->file_path, head);
  }



  Token* tokens = head->next;
  Token_print(tokens);
  free(head);

  if (tokens != NULL) {
    TreeNode* huff = Huffman_from_list(tokens);
    printCodes("./HuffmanCodes", huff);
  }
}

void build_codebook_helper(char* pathname, void* data) {
  printf("Buidling for %s...\n", pathname);

  Token* head = data;
  Token* list = head->next;

  Token* frequencies = Token_read_file_distinct(pathname);

  head->next = Token_merge(list, frequencies);
}