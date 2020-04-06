#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "flags.h"
#include "tokens.h"
#include "warning.h"



// `create` - creates a new token node
Token* Token_create(char* token) {
  Token* node = malloc(sizeof(Token));

  node->frequency = 1;
  node->token = token == NULL ? "" : strdup(token);
  node->next = NULL;
  
  return node;
}

Token* Token_create_frequency(char* token, int frequency) {
  Token* node = Token_create(token);
  node->frequency = frequency;
  
  return node;
}

// `append` - appends a node to a token linked list
Token* Token_append(Token* head, Token* node) {
  if (head == NULL) return node;
  if (node == NULL) return head;

  head->next = Token_append(head->next, node);

  return head;
}

// `merge` - merges two token linked lists distinctly
Token* Token_merge(Token* list_a, Token* list_b) {
  while (list_b != NULL) {
    Token* next = list_b->next;
    list_b->next = NULL;

    list_a = Token_append_distinct(list_a, list_b);
    list_b = next;
  }

  return list_a;
}

// `append_distinct` - appends a node to a token linked list distinctly
Token* Token_append_distinct(Token* head, Token* node) {
  if (head == NULL) return node;
  if (node == NULL) return head;

  if (strcmp(head->token, node->token) == 0) {
    head->frequency++;
    return head;
  }

  head->next = Token_append_distinct(head->next, node);
  return head;
}

// `length` - gets the length of a token linked list
int Token_length(Token* list) {
  if (list == NULL) return 0;
  return 1 + Token_length(list->next);
}

// `to_string` - converts a token linked list to a string
char* Token_to_string(Token* head) {
  char* str = malloc(sizeof(char) * Token_length(head) + 1);

  // Iterate through and add to string.
  int index = 0;
  while(head != NULL) {  
    str[index] = head->token[0];

    head = head->next;
    index++;
  }

  str[index] = '\0';
  return str;
}

// `print` - prints a token linked list
void Token_print(Token* node) {
  if (node == NULL) return;

  printf("token: '%s', frequency: %d\n", node->token, node->frequency);

  Token_print(node->next);
}

// `read_file` - reads a file into a list
Token* Token_read_file(char* filename) {
  int fd = open(filename, O_RDONLY, 0777);

  if (fd < 0) {
    Warning_print_warning("File could not be opened.");
    return NULL;
  }

  Token* all_tokens = NULL;
  Token* non_space_tokens = NULL;

  char* token = malloc(sizeof(char) + 1);
  token[1] = '\0';

  int bytes_read;
  while((bytes_read = read(fd, token, 1)) > 0)  {
    char token_char = *token;

    if (isspace(token_char)) {
        // If there are non-space characters, add them.
        if (non_space_tokens != NULL) {
          char* non_space_str = Token_to_string(non_space_tokens);
          all_tokens = Token_append(all_tokens, Token_create(non_space_str));
          non_space_tokens = NULL; // Reset non-space list.
          free(non_space_str);
        } 

        // Add the space.
        all_tokens = Token_append(all_tokens, Token_create(token));
    } else {
      // Add non-space characters.
      non_space_tokens = Token_append(non_space_tokens, Token_create(token));
    }
  }


  free(token);
  close(fd);

  // Add leftover non-space characters.
  if (non_space_tokens != NULL) {
    char* non_space_str = Token_to_string(non_space_tokens);
    all_tokens = Token_append(all_tokens, Token_create(non_space_str));
    free(non_space_str);
  }

  if (all_tokens == NULL) {
    Warning_print_warning("Empty file!");
  }
 
  return all_tokens;
}

// `read_file` - reads a file into a list distinctly
Token* Token_read_file_distinct(char* filename) {
  Token* tokens = Token_read_file(filename);
  return Token_merge(NULL, tokens);
}