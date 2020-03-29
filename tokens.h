#ifndef TOKENS_H
#define TOKENS_H

typedef struct TokenNode {
  char* token;
  struct TokenNode* next;
} TokenNode;

TokenNode* create_token_node(char* token);
TokenNode* append_node(TokenNode* head, TokenNode* node);

int list_length(TokenNode* list);
char* list_to_string(TokenNode* list);
void print_tokens(TokenNode* head);

TokenNode* file_to_list(char* filename);

#endif