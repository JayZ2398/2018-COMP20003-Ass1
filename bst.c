/* Binary search tree and dictionary functionality*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef char* string_t;

typedef struct {
  string_t id, name, sex, age, height, weight, team, noc, games,
  year, season, city, sport, event, medal;
} data_t;

typedef struct node_t {
  data_t data;
  struct node_t *left, *right;
} node_t;

node_t *makedict(data_t data) {
  /* Return a pointer to a root node for a dictionary, given some staring data.
  */
  node_t *root = malloc(sizeof(node_t));
  root->left = NULL, root->right = NULL, root->data = data;
  return root;
}

node_t *insert(node_t *parent, data_t data) {
  /* Given a parent dictionary node, insert a data point in the correct place
  *  sorted by the <name> field.
  */
  // if at leaf, assign data to node
  if (parent == NULL) {
    parent = makedict(data);
    printf("Planted %s\n", parent->data.name);
    return parent;
  }

  // direct data down tree
  if (strcmp(parent->data.name, data.name) <= 0) {
    parent->left = insert(parent->left, data);
  } else {
    parent->right = insert(parent->right, data);
  }
  return parent;
}
