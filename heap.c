#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "heap.h"

HeapNode* create_heap_node(int frequency, char* word) {
    HeapNode* node = malloc(sizeof(HeapNode));

    node->frequency = frequency;
    node->word = strdup(word);

    node->left = NULL;
    node->right = NULL;

    return node;
}

Heap *CreateHeap(int capacity,int heap_type){
    Heap *h = (Heap * ) malloc(sizeof(Heap)); 

    //check if memory allocation is fails
    if(h == NULL){
        printf("Memory Error!");
        return;
    }
    //h->count = 0;
    h->capacity = capacity;
    h->arr = (int *) malloc(capacity*sizeof(int)); //allocating size in bytes

    //check if allocation succeeds
    if ( h->arr == NULL){
        printf("Memory Error!");
        return;
    }
    return h;
}

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap *h, int i){
    int smallest = i;
    int l = 2*i + 1; //the array index of the left child
    int r = 2*i + 2; //the array index of the right child

    if(l < h->capacity && *h->arr[l]->frequency < *h->arr[smallest]->frequency){
        smallest = l;
    }

    if(r < h->capacity && *h->arr[r]->frequency < *h->arr[smallest]->frequency){
        smallest = r;
    }

    if(smallest != i){
        swap(h->arr[i], h->arr[smallest]);
        heapify(h, smallest);
    }

}

//void heapSort(Heap *h, int n){
    // n is the size of the heap
//    for (int i = n / 2 - 1; i >= 0; i--) 
//      heapify(h->arr, n, i);
//}

void insert(Heap *h, int key){
    if( h->count < h->capacity){
        h->arr[h->count] = key;
        heapify(h, h->count);
        h->count++;
    }
}

