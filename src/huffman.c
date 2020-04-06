#include "huffman.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "heap.h"
#include "tokens.h"

TreeNode* Huffman_from_list(Token* list) {
  if (list == NULL) {
    return NULL;
  }

  Heap* new_heap = CreateHeap(5);

  while (list != NULL) {
    Token* next = list->next;
    list->next = NULL;

    new_heap = insert(new_heap, list);
    list = next;
  }

  printHeap(new_heap);

  while (!isSizeOne(new_heap)) {
    TreeNode* temp1 = removeMin(new_heap);
    TreeNode* temp2 = removeMin(new_heap);

    TreeNode* new = create_tree_node(temp1->frequency + temp2->frequency, NULL);
    new->left = temp1;
    new->right = temp2;

    new_heap = insert_tree_node(new_heap, new);
  }

  return new_heap->arr[0];
}

void printCodes(char* path, TreeNode* treeNode) {
  int fd = creat(path, 0777);

  if (treeNode != NULL) {
    printCodesHelper(fd, treeNode, "");
  }

  close(fd);
}

void printCodesHelper(int fd, TreeNode* treeNode, char* prefix) {
  if (treeNode == NULL) {
    return;
  }
  
  if (treeNode->left == NULL && treeNode->right == NULL) {
    // prefix, tab, word, new line, null char
    int length = strlen(prefix) + 1 + strlen(treeNode->word) + 2;
    char* out_string = malloc(sizeof(char) * length);
    
    // if the node is root
    if (strlen(prefix) == 0) {
      prefix = "0";
    }

    strcpy(out_string, prefix);
    strcat(out_string, "\t");
    strcat(out_string, treeNode->word);
    strcat(out_string, "\n");

    // printf("%s", out_string);
    write(fd, out_string, strlen(out_string));

    free(out_string);

    return;
  }

  if (treeNode->left != NULL) {
    char* new_string = malloc(strlen(prefix) + 1 + 1);
    // zeroes out array
    memset(new_string, '\0', strlen(prefix) + 1 + 1);
    strcpy(new_string, prefix);
    strcat(new_string, "0");

    printCodesHelper(fd, treeNode->left, new_string);
  }

  if (treeNode->right != NULL) {
    // makes new string
    char* new_string = malloc(strlen(prefix) + 1 + 1);
    // zeroes out array
    memset(new_string, '\0', strlen(prefix) + 1 + 1);
    strcpy(new_string, prefix);
    strcat(new_string, "1");

    printCodesHelper(fd, treeNode->right, new_string);
  }

  if (strlen(prefix) != 0) {
    free(prefix);
  }
}

TreeNode* Huffman_insert(TreeNode* huff, char* prefix, char* word) {
  if (strlen(prefix) == 0) {
    return create_tree_node(0, word);
  }

  if (huff == NULL) {
    huff = create_tree_node(0, NULL);
  }

  if (prefix[0] == '0') {
    huff->left = Huffman_insert(huff->left, prefix + 1, word);
  }

  if (prefix[0] == '1') {
    huff->right = Huffman_insert(huff->right, prefix + 1, word);
  }

  return huff;
}

TreeNode* Huffman_from_codebook(char* codebook_path) {
  Token* tokens = Token_read_file(codebook_path);
  TreeNode* huff = NULL;

  while (tokens != NULL) {
    char* encoding = tokens->token;
    // skip tab
    tokens = tokens->next->next;

    char* word = tokens->token;

    // skip new line
    tokens = tokens->next->next;

    huff = Huffman_insert(huff, encoding, word);
  }

  return huff;
}