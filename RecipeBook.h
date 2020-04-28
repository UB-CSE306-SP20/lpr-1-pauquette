#ifndef RECIPE_BOOK_H
#define RECIPE_BOOK_H

#include <stdbool.h>

/* Node in a singly-linked list of ingedients
   - name is name of ingedient
   - calories is number of calories per gram
   - quantity is the number of grams of the ingedient
   - next is a pointer to the next ingedient or NULL if last node in list */
struct Ingredient {
  char * name;
  int calories;
  int quantity;
  struct Ingredient * next;
};

/* creates a new ingredient struct with indicated name and calorie count */
struct Ingredient * newIngredient(char * name, int caloriesPerGram); 

/* Singly-linked list structure that holds a pointer to the first
   ingedient in the pantry (or NULL if pantry is empty) */
struct Pantry {
  struct Ingredient * head;
};

/* creates a new pantry struct */
struct Pantry * newPantry();

/* Node in a singly-linked list of Recipes
   - name is the name of the recipe
   - servings is the number of servings the recipe makes
   - head is the beginning of the ingedient list (can be NULL)
   - next is the next recipe in the recipe book or NULL if end of book */
struct Recipe {
  char * name;
  int servings;
  struct Ingredient * head;
  struct Recipe * next;
};

/* creates a new recipe, with indicated name and number of servings */
struct Recipe * newRecipe(char * name, int servings);

/* Singly-linked list structure that holds a pointer to the first
   recipe in the book (or NULL if book is empty) */
struct Book {
  struct Recipe * head;
};

/* Creates a new recipe book */
struct Book * newBook();

/* adds recipe to book */
void addRecipe(struct Book * book, struct Recipe * recipe); 

/* adds indicated quantity of ingredient (in grams) to recipe */
void addIngredient(struct Recipe * recipe, struct Ingredient * ingredient, int quantity);

/* adds indicated quantity of ingredient (in grams) to pantry */
void storeIngredient(struct Pantry * pantry, struct Ingredient * ingredient, int quantity);

/* returns new book containing recipes from input book that can be made
   with the ingredients in pantry */
struct Book * canMakeAny(struct Pantry * pantry, struct Book * book);

/* returns new book containing recipes from input book that can be made
   with the ingredients in pantry. There must be enough ingredients to 
   make ALL recipes in the new book */
struct Book * canMakeAll(struct Pantry * pantry, struct Book * book);

/* returns new book containing recipes from input book that have fewer
   calories than the calorie limit, per serving */
struct Book * withinCalorieLimit(struct Pantry * pantry, struct Book * book, int limit);

/* returns the number of calories per serving of an input recipe */
int caloriesPerServing(struct Recipe * recipe); 
