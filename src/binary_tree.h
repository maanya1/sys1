#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tokens.h"
#include "heap.h"
#include "huffman.h"

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

TreeNode* Tree_search(TreeNode* root, char* name);
TreeNode* Tree_insert(TreeNode* root, TreeNode* node);

#endif