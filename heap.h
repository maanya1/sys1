#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct HeapNode {
    int frequency;
    char* word;

    struct HeapNode* left;
    struct HeapNode* right;;
} HeapNode;

typedef struct Heap{
    HeapNode *arr;
    int count;
    int capacity;
} Heap;

Heap *CreateHeap(int capacity,int heap_type);
HeapNode* create_heap_node(int frequency, char* word);
void insert(Heap *h, int key);