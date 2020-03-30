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

  new_token_node->frequency = 1;
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

// append token node to token without duplicates
TokenNode* append_node_distinct(TokenNode* head, TokenNode* node) {
  if (head == NULL) return node;
  if (node == NULL) return head;

  if (strcmp(head->token, node->token) == 0) {
    head->frequency++;
    return head;
  }

  head->next = append_node_distinct(head->next, node);

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
    printf("token: '%s', frequency: %d\n", curr->token, curr->frequency);
    curr = curr->next;
  }
}

TokenNode* file_to_list(char* filename) {
  int fd = open(filename, O_RDONLY);

  if (fd < 0) {
    printf("could not open file\n");
    return NULL;
  }

  TokenNode* all_tokens = NULL;
  TokenNode* non_space_tokens = NULL;

  int bytes_read;
  char* token = malloc(sizeof(char));

  while((bytes_read = read(fd, token, 1)) > 0)  {
    char token_char = *token;

    if (isspace(token_char)) {
        // If there are non-space characters, add them.
        if (non_space_tokens != NULL) {
          char* non_space_str = list_to_string(non_space_tokens);

          all_tokens = append_node_distinct(
              all_tokens, create_token_node(non_space_str)
          );
          non_space_tokens = NULL; // Reset non-space list.
        } 

        // Add the space.
        all_tokens = append_node_distinct(all_tokens, create_token_node(buffer));
    } else {
      // Add non-space characters.
      non_space_tokens = append_node(non_space_tokens, create_token_node(token));
    }
  }

  // Add leftover non-whitespace characters 
  if (non_space_tokens != NULL) {
    char* non_space_str = list_to_string(non_space_tokens);

    all_tokens = append_node_distinct(
        all_tokens, create_token_node(non_space_str)
    );
  }

  return all_tokens;
}