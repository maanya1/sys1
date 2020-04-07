#include <stdio.h>
#include <stdlib.h>

void Warning_print_warning(char* warning) {
  printf("[Warning 🙄]: %s\n", warning);
}

void Warning_print_fatal_error(char* fatal_error) {
  printf("[Fatal Error 😕]: %s\n", fatal_error);
  exit(1);
}

void Warning_print_error(char* error) { printf("[Error 😟]: %s\n", error); }