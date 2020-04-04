#include "tokens.h"
#include "heap.h"
#include "huffman.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

TreeNode* Huffman_from_list(Token* list) {
  Heap* new_heap = CreateHeap(5);

  while(list != NULL){
      Token* next = list->next;
      list->next = NULL;
      printf("token: %s\n", list->token);

      insert(new_heap, list);

      list = next;
  }


   while (!isSizeOne(new_heap)) {
    TreeNode* temp1 = removeMin(new_heap);
    printf("temp1: %s\n", temp1->word);
    TreeNode* temp2 = removeMin(new_heap);
    printf("temp2: %s\n", temp2->word);

    TreeNode* new = create_tree_node(temp1->frequency + temp2->frequency, NULL);
    new->left = temp1;
    new->right = temp2;

    insert_tree_node(new_heap, new);
  }
  
  return new_heap->arr[0];
}

void printCodes(char* path, TreeNode* treeNode){
  int fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 777);

  printf("file desc: %d, error: %s\n", fd, strerror(errno));
}

void printCodesHelper(int fd, TreeNode* treeNode, char* prefix){

  if (treeNode->left == NULL && treeNode->right == NULL) {
    // prefix, tab, word, new line, null char
    int length = strlen(prefix) + 1 + strlen(treeNode->word) + 2;
    char* out_string = malloc(sizeof(char) * length);
    strcpy(out_string, prefix);
    strcat(out_string, "\t");

    printf("%s", out_string);
    write(fd, out_string, strlen(out_string));
    return;
  }

  if (treeNode->left != NULL) {
    char* new_string = malloc(strlen(prefix) + 1 + 1);
    // zeroes out array
    memset(new_string, '\0', strlen(prefix) +  1 + 1);
    strcpy(new_string, prefix);
    strcat(new_string, "1");

  }

  if (treeNode->right != NULL) {
    // makes new string
    char* new_string = malloc(strlen(prefix) +  1 + 1);
    // zeroes out array
    memset(new_string, '\0', strlen(prefix) +  1 + 1);
    strcpy(new_string, prefix);
    strcat(new_string, "1");

    // printf("going to right on %s\n", new_string);
    printCodesHelper(fd, treeNode->right, new_string);
  } 
  
}