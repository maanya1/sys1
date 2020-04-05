#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

typedef struct Heap{
    TreeNode **arr;
    int count;
    int capacity;
} Heap;

Heap *CreateHeap(int capacity);
TreeNode* create_tree_node(int frequency, char* word);
TreeNode* compress_create_node(char* code, char* word);
void insert(Heap *h, Token* key);
void insert_tree_node(Heap *h, TreeNode* key);
void siftUp(Heap *h, int i);
TreeNode* removeMin(Heap *h);
void swap(TreeNode **a, TreeNode **b);
void printHeap(Heap *h);
int isSizeOne(Heap* h);

#endif