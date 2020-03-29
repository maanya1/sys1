#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "flags.h"
#include "tokens.h"

TokenNode* create_token_node(char* token) {
  TokenNode* new_token_node = malloc(sizeof(TokenNode));
  new_token_node->token = strdup(token);
  new_token_node->next = NULL;
  return new_token_node;
}

// append token node to token node list
TokenNode* append_node(TokenNode* head, TokenNode* node) {
  if (head == NULL) return node;
  if (node == NULL) return head;

  head->next = append_node(head->next, node);

  return head;
}

int list_length(TokenNode* list) {
  if (list == NULL) return 0;
  return 1 + list_length(list->next);
}

// converts a list of characters to a string
char* list_to_string(TokenNode* list) {
  // length of the list
  int str_length = list_length(list);
  // make a string as the length of the list (+ 1 for the null char at the end)
  char* string = malloc(sizeof(char) * str_length + 1);

 // pointer to front of string and curr string index
  TokenNode* curr = list;
  int str_index = 0;

 // iterate through and add to string
  while(curr != NULL) {
    string[str_index] = curr->token[0];

    curr = curr->next;
    str_index++;
  }

  string[str_index] = '\0';

  return string;
}

void print_tokens(TokenNode* head) {
  TokenNode* curr = head;

  while (curr != NULL) {
    printf("token: %s\n", curr->token);
    curr = curr->next;
  }
}

TokenNode* file_to_list(char* filename) {
  int file_descriptor = open(filename, O_RDONLY);

  if (file_descriptor < 0) {
    printf("could not open file\n");
    return NULL;
  }

  TokenNode* tokens = NULL;
  TokenNode* mini_tokens = NULL;

  int bytes_read = 0;

  do {
    char* buffer = malloc(sizeof(char) + 1);
    buffer[1] = '\0';

    bytes_read = read(file_descriptor, buffer, 1);

    if (bytes_read > 0) {
      if (isspace(*buffer)) {
        // printf("dis is a space: %s\n", buffer);

        TokenNode* word_node = create_token_node( list_to_string(mini_tokens));
        tokens = append_node(tokens, word_node);
        mini_tokens = NULL;

      } else {
        mini_tokens = append_node(mini_tokens, create_token_node(buffer));
        // printf("dis some text: %s\n", buffer);
      }
    }
  } while(bytes_read > 0);

  return tokens;
}