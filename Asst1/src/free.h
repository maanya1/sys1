#include "tokens.h"
#include "heap.h"

#ifndef FREE_H
#define FREE_H

void Free_tokens_list(Token* head);
void Free_binary_tree(TreeNode* root);
void Free_heap(Heap* heap);

#endif