#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"

#ifndef HEAP_H
#define HEAP_H

typedef struct TreeNode {
  int frequency;
  char* word;
  char* code;

  struct TreeNode* left;
  struct TreeNode* right;
} TreeNode;

TreeNode* TreeNode_create(int frequency, char* word);
TreeNode* TreeNode_create_encoding(char* code, char* word);

typedef struct Heap {
  TreeNode** arr;
  int count;
  int capacity;
} Heap;

Heap* Heap_create(int capacity);
Heap* Heap_insert(Heap* h, Token* key);
Heap* Heap_insert_node(Heap* h, TreeNode* key);

void siftUp(Heap* h, int i);
TreeNode* removeMin(Heap* h);
void swap(TreeNode** a, TreeNode** b);
void printHeap(Heap* h);
int isSizeOne(Heap* h);

#endif