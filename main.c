/* Direct file I/O and manage dictionary operations.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"

int main(int argc, char **argv) {

  // dict and buffer variable declaration
  node_t *dict = NULL;
  data_t data;
  string_t input = malloc(sizeof(char) * (MAX_LINE_LEN));
  string_t input_file = argv[1], output_file = argv[2];

  // File I/O
  FILE *fin = fopen(input_file, "r");
  // Overwrite output.txt and reopen for appending
  fclose(fopen(output_file, "w"));
  FILE *fout = fopen(output_file, "a");

  // Read input data to dictionary
  int data_points = 0;
  while (fgets(input, MAX_LINE_LEN, fin) != NULL) {
    printf("###main.c $ read point %7d\n", data_points++);
    read_data(&data, input);
    dict = insert_dict(dict, data);
  }

  // Run lookups on names from stdin
  int found_match = FALSE, counter = 0;
  while (fgets(input, MAX_STR_LEN, stdin) != NULL) {
    // Prepare input string for search
    found_match = FALSE;
    strip_trailing_newline(input);

    // Reset counter for comparisons
    counter = 0;
    search_dict(dict, input, fout, &found_match, &counter);

    // Output number of comparisons to stdout
    fprintf(stdout, "%s --> %d\n", input, counter);

    // Case for no matches found
    if (found_match == FALSE) {
      fprintf(fout, "%s --> NOT FOUND\n\n", input);
    }
  }

  // Free memory and clean up
  free_dict(dict);
  free(input);
  fclose(fin), fclose(fout);

  return 0;
}
