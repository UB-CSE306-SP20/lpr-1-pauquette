#include <stdlib.h>
#include <string.h>
#include "RecipeBook.h"

struct Ingredient * newIngredient(char * name, int caloriesPerGram) {
  // Define later
  struct Ingredient * ingredient;
  ingredient = malloc(sizeof(*ingredient));
  ingredient->name = malloc(sizeof(*name)+1);
  strcpy(ingredient->name, *name);
  ingredient->calories = caloriesPerGram;
  ingredient->quantity = 0;
  ingredient->next = NULL;
  return ingredient;
}

struct Pantry * newPantry() {
  // Define later
  struct Pantry * pantry;
  pantry = malloc(sizeof(*pantry));
  pantry->head = NULL;
  return pantry;
}

struct Recipe * newRecipe(char * name, int servings) {
  // Define later
  struct Recipe * recipe;
  recipe = malloc(sizeof(*recipe));
  recipe->name = malloc(sizeof(*name)+1);
  strcpy(recipe->name, *name);
  recipe->servings = servings;
  recipe->head = NULL;
  recipe->next = NULL;
  return recipe;
}

struct Book * newBook() {
  // Define later
  struct Book * book;
  book = malloc(sizeof(*book));
  book->head = NULL;
  return book;
}

void addRecipe(struct Book * book, struct Recipe * recipe) {
  // Define later
  recipe->next = book->head;
  book->head = recipe;
}

void addIngredient(struct Recipe * recipe, struct Ingredient * ingredient, int quantity) {
  // Define later
  ingredient->quantity = quantity;
  ingredient->next = recipe->head;
  recipe->head = ingredient;
}

void storeIngredient(struct Pantry * pantry, struct Ingredient * ingredient, int quantity) {
  // Define later
  ingredient->quantity = quantity;
  ingredient->next = pantry->head;
  pantry->head = ingredient;
}

struct Book * canMakeAny(struct Pantry * pantry, struct Book * book) {
  // Define later
  struct Book * newBook = newBook();
  struct Recipe * currentRecipe = book->head;
  while(currentRecipe != NULL) {
    struct Ingredient * currentIngredient = currentRecipe->head;
    while(currentIngredient != NULL) {
      if(getQuantity(currentIngredient->name, pantry) <= currentIngredient->quantity) {
	addRecipe(newBook, currentRecipe);
      }
      currentIngredient = currentIngredient->next;
    }
    currentRecipe = currentRecipe->next;
  }
  return newBook;
}

struct Book * canMakeAll(struct Pantry * pantry, struct Book * book) {
  // Define later
  return NULL;
}

struct Book * withinCalorieLimit(struct Pantry * pantry, struct Book * book, int limit) {
  // Define later
  struct Book * newBook = newBook();
  struct Recipe * currentRecipe = book->head;
  while (currentRecipe != NULL) {
    if (caloriesPerServing(recipe) < limit) {
      addRecipe(newBook, currentRecipe);
    }
    currentRecipe = currentRecipe->next;
  }
  return newBook;
}

int caloriesPerServing(struct Recipe * recipe) {
  // Define later
  int totalCalories = 0;
  struct Ingredient * current = recipe->head;
  while (current != NULL) {
    totalCalories += (ingredient->calories * ingredient->quantity);
    current = current->next; 
  }
  return totalCalories/recipe->servings;
}

int getQuantity(char * name, struct Pantry * pantry) {
  struct Ingredient * current = pantry->head;
  while (current != NULL) {
    if(!strscmp(current->name, name)) {
      return current->quantity;
    }
    current = current->next;
  }
  return 0;
}
