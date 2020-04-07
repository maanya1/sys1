#include "free.h"

#include <string.h>

#include "heap.h"
#include "tokens.h"

// Frees a linked list of tokens.
void Free_tokens_list(Token* head) {
  if (head == NULL) {
    return;
  }

  if (strlen(head->token) != 0) {
    free(head->token);
  }

  Token* next = head->next;
  free(head);

  Free_tokens_list(next);
}

// Frees a binary tree and it's nodes.
void Free_binary_tree(TreeNode* root) {
  if (root == NULL) {
    return;
  }

  if (strlen(root->word) > 0) {
    free(root->word);
  }

  if (strlen(root->code) > 0) {
    free(root->code);
  }

  TreeNode* left_node = root->left;
  TreeNode* right_node = root->right;
  free(root);

  Free_binary_tree(left_node);
  Free_binary_tree(right_node);
}

// Frees a heap, but not it's contents.
void Free_heap(Heap* heap) {
  free(heap->arr);
  free(heap);
}
