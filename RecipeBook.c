#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RecipeBook.h"

struct Ingredient * newIngredient(char * name, int caloriesPerGram) {
  struct Ingredient * ingredient;
  ingredient = malloc(sizeof(*ingredient));
  ingredient->name = malloc(sizeof(*name)+1);
  strcpy(ingredient->name, name);
  ingredient->calories = caloriesPerGram;
  ingredient->quantity = 0;
  ingredient->next = NULL;
  return ingredient;
}

struct Pantry * newPantry() {
  struct Pantry * pantry;
  pantry = malloc(sizeof(*pantry));
  pantry->head = NULL;
  return pantry;
}

struct Recipe * newRecipe(char * name, int servings) {
  struct Recipe * recipe;
  recipe = malloc(sizeof(*recipe));
  recipe->name = malloc(sizeof(*name)+1);
  strcpy(recipe->name, name);
  recipe->servings = servings;
  recipe->head = NULL;
  recipe->next = NULL;
  return recipe;
}

struct Book * newBook() {
  struct Book * book;
  book = malloc(sizeof(*book));
  book->head = NULL;
  return book;
}

void addRecipe(struct Book * book, struct Recipe * recipe) {
  recipe->next = book->head;
  book->head = recipe;
}

void addIngredient(struct Recipe * recipe, struct Ingredient * ingredient, int quantity) {
  ingredient->quantity = quantity;
  ingredient->next = recipe->head;
  recipe->head = ingredient;
}

void storeIngredient(struct Pantry * pantry, struct Ingredient * ingredient, int quantity) {
  ingredient->quantity = quantity;
  ingredient->next = pantry->head;
  pantry->head = ingredient;
}

struct Book * canMakeAny(struct Pantry * pantry, struct Book * book) {
  bool canAdd = true;
  struct Book * anyBook = newBook();
  struct Recipe * currentRecipe = book->head;
  while(currentRecipe != NULL) {
    struct Ingredient * currentIngredient = currentRecipe->head;
    while(currentIngredient != NULL) {
      struct Ingredient * pantryIngredient = getIngredient(currentIngredient->name, pantry);
      if(pantryIngredient == NULL || pantryIngredient->quantity < currentIngredient->quantity) {
	canAdd = false;
      }
      currentIngredient = currentIngredient->next;
    }
    if (canAdd) { addRecipe(anyBook, currentRecipe); }
    else { canAdd = true; }
    currentRecipe = currentRecipe->next;
  }
  return anyBook;
}

struct Book * canMakeAll(struct Pantry * pantry, struct Book * book) {
  // Define later
  bool canAdd = true;
  struct Book * allBook = newBook();
  struct Recipe * currentRecipe = book->head;
  while (currentRecipe != NULL) {
    struct Ingredient * currentIngredient = currentRecipe->head;
    while (currentIngredient != NULL) {
      struct Ingredient * pantryIngredient = getIngredient(currentIngredient->name, pantry);
      if (pantryIngredient != NULL && pantryIngredient->quantity >= currentIngredient->quantity) {
	pantryIngredient->quantity -= currentIngredient->quantity;
      } else { canAdd = false; }
      currentIngredient = currentIngredient->next;
    }
    if (canAdd) { addRecipe(allBook, currentRecipe); }
    else { canAdd = true; }
    currentRecipe = currentRecipe->next;
  }
  return allBook;
}

struct Book * withinCalorieLimit(struct Pantry * pantry, struct Book * book, int limit) {
  struct Book * dietBook = newBook();
  struct Recipe * currentRecipe = book->head;
  while (currentRecipe != NULL) {
    if (caloriesPerServing(currentRecipe) < limit) {
      addRecipe(dietBook, currentRecipe);
    }
    currentRecipe = currentRecipe->next;
  }
  return dietBook;
}

int caloriesPerServing(struct Recipe * recipe) {
  int totalCalories = 0;
  struct Ingredient * current = recipe->head;
  while (current != NULL) {
    totalCalories += (current->calories * current->quantity);
    current = current->next; 
  }
  return totalCalories/recipe->servings;
}

struct Ingredient * getIngredient(char * name, struct Pantry * pantry) {
  struct Ingredient * current = pantry->head;
  while (current != NULL) {
    if(!strcmp(current->name, name)) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}
