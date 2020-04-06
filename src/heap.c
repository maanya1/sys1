#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "heap.h"
#include "tokens.h"

TreeNode* create_tree_node(int frequency, char* word) {
    TreeNode* node = malloc(sizeof(TreeNode));

    node->frequency = frequency;
    node->word = word == NULL ? "" : strdup(word);
    node->code = "";

    node->left = NULL;
    node->right = NULL;

    return node;
} 

TreeNode* compress_create_node(char* code, char* word) {
    TreeNode* node = malloc(sizeof(TreeNode));

    node->code = strdup(code);
    node->word = word == NULL ? "" : strdup(word);
    node->frequency = 1;

    node->left = NULL;
    node->right = NULL;

    return node;
} 

Heap *CreateHeap(int capacity){
    Heap *h = (Heap * ) malloc(sizeof(Heap)); 

    //check if memory allocation is fails
    if(h == NULL){
        printf("Memory Error!");
        return NULL;
    }

    h->count = 0;
    h->capacity = capacity;
    h->arr = malloc(capacity * sizeof(TreeNode*)); //allocating size in bytes

    //check if allocation succeeds
    if ( h->arr == NULL){
        printf("Memory Error!");
        return NULL;
    }
    return h;
}

void swap(TreeNode **a, TreeNode **b) {
    TreeNode* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap *h, int i){
    int smallest = i;
    int l = 2*i + 1; //the array index of the left child
    int r = 2*i + 2; //the array index of the right child

    if(l < h->count && h->arr[l]->frequency < h->arr[smallest]->frequency){
        smallest = l;
    }

    if(r < h->count && h->arr[r]->frequency < h->arr[smallest]->frequency){
        smallest = r;
    }

    if(smallest != i){
        swap(&h->arr[i], &h->arr[smallest]);
        heapify(h, smallest);
    }
}

Heap* insert(Heap *h, Token* token){
    TreeNode* node = create_tree_node(token->frequency, token->token);
    return insert_tree_node(h, node);
}

Heap* insert_tree_node(Heap *h, TreeNode* node){
    if (h->count >= h->capacity) {
        int new_size = h->capacity * 2;
        TreeNode** new_heap = malloc(sizeof(TreeNode*) * new_size);

        int i = 0;
        for(; i < h->count; i++){
            new_heap[i] = h->arr[i];
        }

        // free(h->arr);
        h->capacity = new_size;
        h->arr = new_heap;
    }

    h->arr[h->count] = node;
    siftUp(h, h->count);
    h->count++;

    return h;
}

void siftUp(Heap *h, int i){
    //if the heapNode to sift up is at the root, return
    if(i == 0){
        return;
    }

    int p = (i-1)/2; //index that parent is at
    //if the specified value is smaller than it's parent, then swap with it's parent
    if(p >= 0 && h->arr[i]->frequency < h->arr[p]->frequency ){
        swap(&h->arr[p],& h->arr[i]);
        siftUp(h, p);
    }
}

TreeNode* removeMin(Heap *h){
    if(h->count == 0){
        return NULL;
    }
    TreeNode* ret = h->arr[0]; 
    swap(&h->arr[h->count-1], &h->arr[0]);

    h->count--;
    heapify(h, 0);

    return ret;
}

void printHeap(Heap *h){
    int i = 0;
    for(; i < h->count; i++) {
        TreeNode* node = h->arr[i];
        printf("frequencyt: %d, token: %s\n", node->frequency, node->word);
    }
}

int isSizeOne(Heap* h){
    if(h->count == 1){
        return 1;
    }
    return 0;
}

// int main(int argc, char** argv){
//     Heap *h = CreateHeap(5);
//     //int array[] = {3, 70, 4, 80,90,5,6,82,84,91,92,7,8};
//     //CreateHeap(array);

//     insert(h, Token_create_frequency("dis", 1));
//     insert(h, Token_create_frequency(" ", 4));
//     insert(h, Token_create_frequency("some", 1));
//     insert(h, Token_create_frequency("text", 3));


//     // insert(h, Token_create_frequency("blah", 5));
//     // insert(h, Token_create_frequency("yeet", 7));
//     // insert(h, Token_create_frequency("swag", 2));
//     // insert(h, Token_create_frequency("blah2", 1));
//     // insert(h, Token_create_frequency("poopy", 3));

//     printHeap(h);
// }

