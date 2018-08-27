/* Stage 2 dictionary function definitions
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

node_t *make_dict(data_t data) {
  /* Return a pointer to a root node for a dictionary, given some starting data.
  */

  node_t *root = malloc(sizeof(node_t));
  root->left = NULL, root->right = NULL, root->next = NULL, root->data = data;
  return root;
}

node_t *insert_dict(node_t *parent, data_t data) {
  /* Given a parent dictionary node, insert a data point in the correct place
  *  sorted by the <name> field.
  */

  // If at leaf, assign data to node
  if (parent == NULL) {
    parent = make_dict(data);
    return parent;
  }

  int comparison = strcmp(parent->data.name, data.name);
  // Direct data down tree
  if (comparison == 0) {
    parent->next = insert_dict(parent->next, data);
  } else if (comparison < 0) {
    parent->left = insert_dict(parent->left, data);
  } else {
    parent->right = insert_dict(parent->right, data);
  }
  return parent;
}

void search_dict(node_t *parent, string_t name, FILE *out, int *found_match) {
  /* Search a dictionary for a name, and output associated data on matches to
     a specified file.
  */

  // Do nothing if parent is not an initialised node
  if (parent == NULL) {
    return;
  }

  int comparison = strcmp(parent->data.name, name);
  // If parent's data.name matches search name, print data
  if (comparison == 0) {
    output_data(&(parent->data), out);
    search_dict(parent->next, name, out, found_match);
    *found_match = TRUE;
    return;
  }

  // Search children, regardless of whether match was found
  if (comparison < 0) {
    search_dict(parent->left, name, out, found_match);
  } else {
    search_dict(parent->right, name, out, found_match);
  }

  // Increment comparison count for the single strcmp call
  counter(1, INCREMENT);
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
