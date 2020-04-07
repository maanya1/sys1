#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tokens.h"
#include "heap.h"

#ifndef HUFF_H
#define HUFF_H

TreeNode* Huffman_from_list(Token* list);
TreeNode* Huffman_from_codebook(char* codebook);
TreeNode* Huffman_insert(TreeNode* huff, char* prefix, char* word);
void printCodes(char* path, TreeNode* treeNode);
void printCodesHelper(int fd, TreeNode* treeNode, char* prefix);

#endif
