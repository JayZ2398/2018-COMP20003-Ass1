#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"

#define MAX_LINE_LEN 512
#define MAX_STR_LEN 128

void read_to_data(data_t *data, string_t input);

int main(int argc, char **argv) {

  FILE *fp;
  string_t input = malloc(sizeof(char) * (MAX_LINE_LEN + 1));
  string_t input_file = argv[1];
  node_t *dict1 = NULL;
  data_t data;

  fp = fopen(input_file, "r");
  while (fgets(input, MAX_LINE_LEN + 1, fp) != NULL) {
    read_to_data(&data, input);
    dict1 = insert(dict1, data);
  }

  return 0;
}

void read_to_data(data_t *data, string_t input) {
  /* read a csv line from stdin into a data structure's members */

  // use i as index for building words, j as index for input string character
  string_t* member = (string_t*)data;
  char c, word[MAX_STR_LEN];
  int i = 0, j = 0;

  for (j = 0; j < strlen(input); j++) {
    c = input[j];
    // Commas within double quotations case - to do later

    // If comma reached, store value in next data member
    if (c == ',') {
      word[i] = '\0';
      // Copy current word to data
      // strlen only counts the size of the word up to the null terminator
      *member = malloc(sizeof(char) * strlen(word));
      strcpy(*member, word);
      i = 0, member++;
    }
    // Otherwise, add character to current word
    else {
      word[i] = c;
      i++;
    }
  }
  return;
}
