#ifndef RECIPE_H
#define RECIPE_H

#include "Ingredient.h"

struct Recipe {
  char * name;
  int servings;
  struct NodeIngredientQuantity * head;
};

struct Recipe * newRecipe(char * n, int s);

void addIngredient(struct Recipe * recipe, struct Ingredient * ingredient, int quantityInGrams);

#endif
