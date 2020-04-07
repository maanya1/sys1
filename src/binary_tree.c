#include "free.h"
#include "heap.h"

// Finds a node by name in a binary search tree.
TreeNode* Tree_search(TreeNode* root, char* name) {
  if (root == NULL || strcmp(root->word, name) == 0) {
    return root;
  }

  if (strcmp(name, root->word) > 0) {
    return Tree_search(root->right, name);
  }

  return Tree_search(root->left, name);
}

// Inserts a node by name in a binary search tree.
// Frees if it already exists.
TreeNode* Tree_insert(TreeNode* root, TreeNode* node) {
  if (node == NULL) return root;
  if (root == NULL) return node;

  if (strcmp(node->word, root->word) < 0) {
    root->left = Tree_insert(root->left, node);
  } else if (strcmp(node->word, root->word) > 0) {
    root->right = Tree_insert(root->right, node);
  } else {
    root->frequency++;
    Free_binary_tree(root);
  }

  return root;
}