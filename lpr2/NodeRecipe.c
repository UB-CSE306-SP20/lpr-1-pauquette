#include <stdlib.h>
#include "NodeRecipe.h"

struct NodeRecipe * newNodeRecipe(struct Recipe *v, struct NodeRecipe * n) {
  struct NodeRecipe * this;
  this = malloc(sizeof(*this));
  this -> value = v;
  this -> next = n;
  return this;
}

