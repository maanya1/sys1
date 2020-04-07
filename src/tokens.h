#ifndef TOKENS_H
#define TOKENS_H

typedef struct Token {
  char* token;
  int frequency;
  struct Token* next;
} Token;

Token* Token_create(char* token);
Token* Token_create_frequency(char* token, int frequency);

Token* Token_append(Token* head, Token* node);
Token* Token_append_distinct(Token* head, Token* node);
Token* Token_merge(Token* list_a, Token* list_b);
int Token_length(Token* list);
char* Token_to_string(Token* list);
void Token_print(Token* head);
Token* Token_read_file(char* filename);
Token* Token_read_file_distinct(char* filename);

#endif