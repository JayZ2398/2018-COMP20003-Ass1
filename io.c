/* I/O and comparison counter functions.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"

void read_data(data_t *data, string_t input) {
  /* Read a csv line from stdin into a data structure's members.
  */

  string_t* member = (string_t*)data;
  char c, *temp_str = malloc(sizeof(char) * MAX_STR_LEN);
  int letter_idx = 0, input_idx = 0;

  // Iterate input string characters, store chars up to , in temp_str
  for (input_idx = 0; input_idx < strlen(input); input_idx++) {
  c = input[input_idx];

    // If comma or end of line reached, copy temp string into struct
    if (c == ',' || c == '\n') {
      temp_str[letter_idx] = '\0';
      //  Only chars up to and including '\0' in temp_str are copied.
      *member = malloc(sizeof(char) * (strlen(temp_str) + 1));
      strcpy(*member, temp_str);
      letter_idx = 0, member++;
    }
    // Otherwise, add character to current string
    else {
      temp_str[letter_idx++] = c;
    }
  }
  free(temp_str);
  return;
}

void output_data(data_t *data, FILE *out) {
  /* Output string of data to designated output stream.
  */

  const static char tags[OUTPUT_FIELDS][FIELD_STR_LEN] = {
    "Sex", "Age", "Height", "Weight", "Team", "NOC", "Games", "Year",
    "Season", "City", "Sport", "Event", "Medal"
  };

  int members_counted = 0;
  string_t *member = (string_t *)&(data->sex);

  // Output name and ID fields first with special formatting
  fprintf(out, "%s --> ID: %s || ", data->name, data->id);

  // Output remaining fields in order
  while (members_counted < OUTPUT_FIELDS) {
    fprintf(out, "%s: %s || ", tags[members_counted], *member);
    members_counted++, member++;
  }

  // Add newline, output data to file
  fprintf(out, "\n");
  return;
}

void strip_trailing_newline(string_t string) {
  /* Removes the newline character at the end of a string. Also Removes
     carriage returns.
  */

  int end = strlen(string);
  if (strlen(string) > 2 && string[end - 2] == '\r') {
    string[end - 2] = '\0';
  } else if (string[end - 1] == '\n') {
    string[end - 1] = '\0';
  }
  return;
}
