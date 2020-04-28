#include <stdio.h>
#include "CUnit.h"
#include "Basic.h"
#include "RecipeBook.h"

void testNewIngredient(char * name, int calories) {
  struct Ingredient * ingredient = newIngredient(name, calories);
  CU_ASSERT_PTR_NOT_NULL(ingredient);
  CU_ASSERT_STRING_EQUAL(name, ingredient->name);
  CU_ASSERT_EQUAL(calories, ingredient->calories);
  CU_ASSERT_EQUAL(0, ingredient->quantity);
  CU_ASSERT_PTR_NULL(ingredient->next);
} 

void testNewPantry() {
  struct Pantry * pantry = newPantry();
  CU_ASSERT_PTR_NOT_NULL(pantry);
  CU_ASSERT_PTR_NULL(pantry->head);
}

void testNewRecipe(char * name, int servings) {
  struct Recipe * recipe = newRecipe(name, servings);
  CU_ASSERT_PTR_NOT_NULL(recipe);
  CU_ASSERT_STRING_EQUAL(name, recipe->name);
  CU_ASSERT_EQUAL(servings, recipe->servings);
  CU_ASSERT_PTR_NULL(recipe->head);
  CU_ASSERT_PTR_NULL(recipe->next);
}

void testNewBook() {
  struct Book * book = newBook();
  CU_ASSERT_PTR_NOT_NULL(book);
  CU_ASSERT_PTR_NULL(book->head);
}

void testAddRecipe(struct Book * book, struct Recipe * recipe) {
  addRecipe(book, recipe);
  CU_ASSERT_PTR_NOT_NULL(book->head);
  CU_ASSERT_STRING_EQUAL(recipe->name, book->head->name);
  CU_ASSERT_EQUAL(recipe->servings, book->head->servings);
  CU_ASSERT_PTR_EQUAL(recipe->head, book->head->head);
  CU_ASSERT_PTR_EQUAL(recipe->next, book->head->next);
}

void testAddIngredient(struct Recipe * recipe, struct Ingredient * ingredient, int quantity) {
  addIngredient(recipe, ingredient, quantity);
  CU_ASSERT_PTR_NOT_NULL(recipe->head);
  CU_ASSERT_STRING_EQUAL(ingredient->name, recipe->head->name);
  CU_ASSERT_EQUAL(quantity, recipe->head->quantity);
  CU_ASSERT_PTR_EQUAL(ingredient, recipe->head);
  CU_ASSERT_PTR_EQUAL(ingredient->next, recipe->head->next);
}

void testStoreIngredient(struct Pantry * pantry, struct Ingredient * ingredient, int quantity) {
  storeIngredient(pantry, ingredient, quantity);
  CU_ASSERT_PTR_NOT_NULL(pantry->head);
  CU_ASSERT_STRING_EQUAL(ingredient->name, pantry->head->name);
  CU_ASSERT_EQUAL(quantity, pantry->head->quantity);
  CU_ASSERT_PTR_EQUAL(ingredient, pantry->head);
  CU_ASSERT_PTR_EQUAL(ingredient->next pantry->head->next);
}

void testCaloriesPerServing(struct Recipe * recipe, int expected) {
  int actual = caloriesPerServing(recipe);
  CU_ASSERT_EQUAL(expected, actual);
}

void testCanMakeAny(struct Pantry * pantry, struct Book * book) {
  struct Book * actual = canMakeAny(pantry, book);
  currentRecipe = actual->head;
  while(currentRecipe != NULL) {
    currentIngredient = currentRecipe->head;
    while(currentIngredient != NULL) {
      CU_ASSERT(currentIngredient->quantity <= getQuantity(char * name, struct Pantry * pantry)); 
      currentIngredient = currentIngredient->next;
    }
    currentRecipe = currentRecipe->next;
  }
}

void testCanMakeAll(struct Pantry * patry, struct Book * book) {
  struct Book * actual = canMakeAll(pantry, book);
  currentRecipe = actual->head;
  while(currentRecipe != NULL) {
    
  }
}

void testWithinCalorieLimit(struct Pantry * pantry, struct Book * book, int limit) {
  struct Book * actual = withinCalorieLimit(pantry, book, limit);
  struct Recipe * currentRecipe = actual->head;
  while (currentRecipe != NULL) {
    int calsPerServing = caloriesPerserving(currentRecipe);
    CU_ASSERT(calsPerServing < limit);
    currentRecipe = currentRecipe->next;
  }
}

 
