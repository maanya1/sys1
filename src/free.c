#include "tokens.h"
#include "heap.h"

#include "free.h"

// remember to free "strdup". also cmd + f for all malloc and make sure that
// they're covered.

// don't forget to free strings malloced in structs

void Free_tokens_list(Token* head) {
  if (head == NULL) return;

  Token* next = head->next;

  free(head->token);
  free(head);

  Free_tokens_list(next);
}

void Free_binary_tree(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* left_node = root->left;
    TreeNode* right_node = root->right;

    free(root->word);
    free(root->code);
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
