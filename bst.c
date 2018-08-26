/* Binary search tree and dictionary functionality*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

node_t *makedict(data_t data) {
  /* Return a pointer to a root node for a dictionary, given some starting data.
  */

  node_t *root = malloc(sizeof(node_t));
  root->left = NULL, root->right = NULL, root->data = data;
  return root;
}

node_t *insert(node_t *parent, data_t data) {
  /* Given a parent dictionary node, insert a data point in the correct place
  *  sorted by the <name> field.
  */

  // If at leaf, assign data to node
  if (parent == NULL) {
    parent = makedict(data);
    return parent;
  }

  // Direct data down tree
  if (strcmp(parent->data.name, data.name) <= 0) {
    parent->left = insert(parent->left, data);
  } else {
    parent->right = insert(parent->right, data);
  }
  return parent;
}

void search(node_t *parent, string_t name, FILE* out) {
  /* Search a dictionary for a name, and output associated data on matches to
     a specified file.
  */

  // Do nothing if parent is not a node
  if (parent == NULL) {
    return;
  }

  // If parent's data.name matches search name, print data
  if (strcmp(parent->data.name, name) == 0) {
    //printf("%s found at %p\n", parent->data.name, parent);
    output_data(&(parent->data), out);
  }

  // Search children, regardless of whether match was found
  if (strcmp(parent->data.name, name) <= 0) {
    search(parent->left, name, out);
  } else {
    search(parent->right, name, out);
  }
  return;
}

void free_dict(node_t *parent) {
  /* Free the memory used to store a dictionary.
  */

  if (parent == NULL) {
    return;
  }
  free(parent->left);
  free(parent->right);
  free(parent);
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
