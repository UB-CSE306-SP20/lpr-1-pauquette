#ifndef PANTRY_H
#define PANTRY_H

#include "Ingredient.h"

struct Pantry {
  struct NodeIngredientQuantity * head;
};

struct Pantry * newPantry();

void storeIngredient(struct Pantry * pantry, struct Ingredient * ingredient, int quantityInGrams);

#endif
