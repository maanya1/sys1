#include "heap.h"
#include "boolean.h"

TreeNode* Tree_search(TreeNode* root, char* name) {
  if(root == NULL || strcmp(root->word, name) == 0) {
      return root;
  }
  
  if (strcmp(name, root->word) > 0){
    return Tree_search(root->right, name);
  }

  return Tree_search(root->left, name);
}

TreeNode* Tree_insert(TreeNode* root, TreeNode* node) {
    if (node == NULL) return root;
    if (root == NULL) return node;

    if(strcmp(node->word, root->word) < 0){
        root->left = Tree_insert(root->left, node);
    } else if (strcmp(node->word, root->word) > 0){
        root->right = Tree_insert(root->right, node);
    } else {
        root->frequency++;
    }

    return root;
}