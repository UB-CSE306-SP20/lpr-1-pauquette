#include <stdlib.h>
#include "Pantry.h"
#include "Ingredient.h"

struct Pantry * newPantry() {
  struct Pantry * this;
  this = malloc(sizeof(*this));
  this -> head = NULL;
  return this;
}

void storeIngredient(struct Pantry * pantry, struct Ingredient * ingredient, int quantityInGrams) {
  // TODO 
}
