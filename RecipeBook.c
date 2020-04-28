#include <stdlib.h>
#include "RecipeBook.h"

struct Ingredient * newIngredient(char * name, int caloriesPerGram) {
  // Define later
  return NULL;
}

struct Pantry * newPantry() {
  // Define later
  return NULL;
}

struct Recipe * newRecipe(char * name, int servings) {
  // Define later
  return NULL;
}

struct Book * newBook() {
  // Define later
  return NULL;
}

void addRecipe(struct Book * book, struct Recipe * recipe) {
  // Define later
}

void addIngredient(struct Recipe * recipe, struct Ingredient * ingredient, int quantity) {
  // Define later
}

void storeIngredient(struct Pantry * pantry, struct Ingredient * ingredient, int quantity) {
  // eEfine later
}

struct Book * canMakeAny(struct Pantry * pantry, struct Book * book) {
  // Define later
  return NULL;
}

struct Book * canMakeAll(struct Pantry * pantry, struct Book * book) {
  // Define later
  return NULL;
}

struct Book * withinCalorieLimit(struct Pantry * pantry, struct Book * book, int limit) {
  // Define later
  return NULL;
}

int caloriesPerServing(struct Recipe * recipe) {
  // Define later
  return 0;
}

int getQuantity(char * name, struct Pantry * pantry) { return 0; }
