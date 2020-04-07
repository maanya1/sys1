#include "tokens.h"
#include "heap.h"

#include "free.h"
#include <string.h>

// remember to free "strdup". also cmd + f for all malloc and make sure that
// they're covered.

// don't forget to free strings malloced in structs

void Free_tokens_list(Token* head) {
  if (head == NULL) return;
  Token* next = head->next;

  if (strlen(head->token) != 0) {
    free(head->token);
  }
  free(head);

  printf("next: %p\n", next);
  Free_tokens_list(next);
}

void Free_binary_tree(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* left_node = root->left;
    TreeNode* right_node = root->right;

    if (strlen(root->word) > 0) {
      free(root->word);
    }

    if (strlen(root->code) > 0) {
        free(root->code);
    }
  
    free(root);

    Free_binary_tree(left_node);
    Free_binary_tree(right_node);
}

void Free_heap(Heap* heap) {
    int i = 0;
    for (; i < heap->count; i++) {
      Free_binary_tree(heap->arr[i]);
    }

    free(heap->arr);
    free(heap);
}
