#include "tokens.h"
#include "heap.h"

TreeNode* Huffman_from_list(Token* list) {
  Heap* new_heap = CreateHeap(1);

  while(list != NULL){
      Token* next = list->next;
      list->next = NULL;

      insert(new_heap, list);

      list = next;
  }

s
  return NULL;
}