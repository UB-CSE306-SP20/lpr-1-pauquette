#include <stdlib.h>
#include "Recipe.h"
#include "Ingredient.h"
#include "NodeIngredientQuantity.h"


struct Recipe * newRecipe(char * n, int s) {
  struct Recipe * this;
  this = malloc(sizeof(*this));
  this -> name = n;
  this -> servings = s;
  this -> head = NULL;
  return this;
}

void addIngredient(struct Recipe * recipe, struct Ingredient * ingredient, int quantityInGrams) {
  struct NodeIngredientQuantity * this;
  this = newNodeIngredientQuantity(ingredient, quantityInGrams, recipe->head);
  recipe -> head = this;
}


