#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RecipeBook.h"

/* Function to create a new Ingredient struct. Returns new struct with name and caloriesPerGram set
   @params - name: a string contaning the desired ingredient name
           - caloriesPerGram: an int that holds the calories/gram of the ingredient
   @returns - A new Ingredient struct with name and caloriesPerGram member variables set */

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

/* Function to create a new Pantry struct. Pantry holds a pointer to the head of a list of Ingredients
   @params - none
   @returns - A pointer to a new Pantry struct that is empty */

struct Pantry * newPantry() {
  struct Pantry * pantry;
  pantry = malloc(sizeof(*pantry));
  pantry->head = NULL;
  return pantry;
}

/* Function to create a new Recipe struct. Function takes in the and number of servings of the recipe
   @params - name: A string holding the desired name of the new recipe
           - servings: An int holding the number of servings for the recipe
   @returns - A pointer to a new Recipe struct with name and servings set */

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

/* Function to create a new recipe Book struct. Book holds a pointer to the head of a list of Recipes 
   @params - none
   @returns - A pointer to a new Book struct */ 

struct Book * newBook() {
  struct Book * book;
  book = malloc(sizeof(*book));
  book->head = NULL;
  return book;
}

/* Function to add a Recipe struct to a Book struct. Fucntion sets recipe's next pointer to head of book
   and sets recipe to be the new head of book. 
   @params - book: A pointer to the Book struct the recipe is being added to
           - recipe: A pointer to the Recipe struct being added to book
   @returns - none*/

void addRecipe(struct Book * book, struct Recipe * recipe) {
  recipe->next = book->head;
  book->head = recipe;
}

/* Function to add an Ingredient struct to a Recipe struct. Function sets Ingredient quantity, sets
   ingredient's next pointer to head of recipe and sets ingredient to be the new head of recipe.
   @params - recipe: A pointer to a Recipe struct that is having the Ingredient added to it
           - ingredient: A pointer to the Ingredient struct that is being added to recipe
           - quantity: The amount of Ingredient to be added to the recipe in grams */ 

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
