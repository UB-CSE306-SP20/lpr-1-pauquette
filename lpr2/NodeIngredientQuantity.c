#include <stdlib.h>
#include "NodeIngredientQuantity.h"

struct NodeIngredientQuantity * newNodeIngredientQuantity(struct Ingredient * i, int g, struct NodeIngredientQuantity * n) {
  struct NodeIngredientQuantity * this;
  this = malloc(sizeof(*this));
  this -> ingredient = i;
  this -> grams = g;
  this -> next = n;
  return this;
}


