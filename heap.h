#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tokens.h"

typedef struct TreeNode {
    int frequency;
    char* word;

    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Heap{
    TreeNode **arr;
    int count;
    int capacity;
} Heap;

Heap *CreateHeap(int capacity);
TreeNode* create_heap_node(int frequency, char* word);
void insert(Heap *h, Token* key);
void siftUp(Heap *h, int i);
TreeNode* removeMin(Heap *h);
void swap(TreeNode **a, TreeNode **b);
void printHeap(Heap *h);