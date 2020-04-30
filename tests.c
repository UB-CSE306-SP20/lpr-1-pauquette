#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
  CU_ASSERT_PTR_EQUAL(ingredient->next, pantry->head->next);
}

void testCaloriesPerServing(struct Recipe * recipe, int expected) {
  int actual = caloriesPerServing(recipe);
  CU_ASSERT_EQUAL(expected, actual);
}

void testCanMakeAny(struct Pantry * pantry, struct Book * book) {
  struct Book * actual = canMakeAny(pantry, book);
  struct Recipe * currentRecipe = actual->head;
  while(currentRecipe != NULL) {
    struct Ingredient * currentIngredient = currentRecipe->head;
    while(currentIngredient != NULL) {
      bool condition = currentIngredient->quantity <= getIngredient(currentIngredient->name, pantry)->quantity;
      CU_ASSERT_TRUE(condition); 
      currentIngredient = currentIngredient->next;
    }
    currentRecipe = currentRecipe->next;
  }
}

void testCanMakeAnyFails(struct Pantry * pantry, struct Book * book) {
  struct Book * actual = canMakeAny(pantry, book);
  struct Recipe * currentRecipe = actual->head;
  while(currentRecipe != NULL) {
    struct Ingredient * currentIngredient = currentRecipe->head;
    while(currentIngredient != NULL) {
      bool condition = currentIngredient->quantity <= getIngredient(currentIngredient->name, pantry)->quantity;
      CU_ASSERT_FALSE(condition); 
      currentIngredient = currentIngredient->next;
    }
    currentRecipe = currentRecipe->next;
  }
}

void testCanMakeAll(struct Pantry * pantry, struct Book * book) {
  canMakeAll(pantry, book);
  struct Ingredient * currentIngredient = pantry->head;
  while(currentIngredient != NULL) {
    CU_ASSERT(currentIngredient->quantity >= 0);
    currentIngredient = currentIngredient->next;
  }
}

void testCanMakeAllFails(struct Pantry * pantry, struct Book * book) {
  canMakeAll(pantry, book);
  struct Ingredient * currentIngredient = pantry->head;
  while(currentIngredient != NULL) {
    CU_ASSERT(currentIngredient->quantity >= 0);
    currentIngredient = currentIngredient->next;
  }
} 

void testWithinCalorieLimit(struct Pantry * pantry, struct Book * book, int limit) {
  struct Book * actual = withinCalorieLimit(pantry, book, limit);
  struct Recipe * currentRecipe = actual->head;
  while (currentRecipe != NULL) {
    int calsPerServing = caloriesPerServing(currentRecipe);
    CU_ASSERT(calsPerServing < limit);
    currentRecipe = currentRecipe->next;
  }
}

void test00(void) { testNewIngredient("Apple", 1); }
void test01(void) { testNewPantry(); }
void test02(void) { testNewRecipe("Apple Pie", 8); }
void test03(void) { testNewBook(); }
void test04(void) {
  struct Recipe * recipe = newRecipe("Apple Pie", 8);
  struct Ingredient * apple = newIngredient("Apple", 1);
  testAddIngredient(recipe, apple, 10);
}
void test05(void) {
  struct Pantry * pantry = newPantry();
  struct Ingredient * apple = newIngredient("Apple", 1);
  testStoreIngredient(pantry, apple, 10);
}
void test06(void) {
  struct Book * book = newBook();
  struct Recipe * recipe = newRecipe("Apple Pie", 8);
  testAddRecipe(book, recipe);
}
void test07(void) {
  struct Recipe * recipe = newRecipe("Apple Pie", 8);
  struct Ingredient * apples = newIngredient("apples", 1);
  struct Ingredient * crust = newIngredient("crust", 4);
  struct Ingredient * sugar = newIngredient("sugar", 4);
  struct Ingredient * cinnamon = newIngredient("cinnamon", 2);
  addIngredient(recipe, apples, 500);
  addIngredient(recipe, crust, 200);
  addIngredient(recipe, sugar, 100);
  addIngredient(recipe, cinnamon, 50);
  testCaloriesPerServing(recipe, 225);
}
void test08(void) {
  struct Book * book = newBook();
  struct Pantry * pantry = newPantry();
  struct Recipe * recipe = newRecipe("Apple Pie", 8);
  struct Ingredient * apples = newIngredient("apples", 1);
  struct Ingredient * crust = newIngredient("crust", 4);
  struct Ingredient * sugar = newIngredient("sugar", 4);
  struct Ingredient * cinnamon = newIngredient("cinnamon", 2);
  addIngredient(recipe, apples, 500);
  addIngredient(recipe, crust, 200);
  addIngredient(recipe, sugar, 100);
  addIngredient(recipe, cinnamon, 50);
  addRecipe(book, recipe);
  struct Ingredient * pantryApples = newIngredient("apples", 1);
  struct Ingredient * pantryCrust = newIngredient("crust", 4);
  struct Ingredient * pantrySugar = newIngredient("sugar", 4);
  struct Ingredient * pantryCinnamon = newIngredient("cinnamon", 2);
  storeIngredient(pantry, pantryApples, 500);
  storeIngredient(pantry, pantryCrust, 500);
  storeIngredient(pantry, pantrySugar, 500);
  storeIngredient(pantry, pantryCinnamon, 500);
  testCanMakeAll(pantry, book);
}
void test09(void) {
  struct Book * book = newBook();
  struct Pantry * pantry = newPantry();
  struct Recipe * recipe = newRecipe("Apple Pie", 8);
  struct Ingredient * apples = newIngredient("apples", 1);
  struct Ingredient * crust = newIngredient("crust", 4);
  struct Ingredient * sugar = newIngredient("sugar", 4);
  struct Ingredient * cinnamon = newIngredient("cinnamon", 2);
  addIngredient(recipe, apples, 500);
  addIngredient(recipe, crust, 200);
  addIngredient(recipe, sugar, 100);
  addIngredient(recipe, cinnamon, 50);
  addRecipe(book, recipe);
  struct Ingredient * pantryApples = newIngredient("apples", 1);
  struct Ingredient * pantryCrust = newIngredient("crust", 4);
  struct Ingredient * pantrySugar = newIngredient("sugar", 4);
  struct Ingredient * pantryCinnamon = newIngredient("cinnamon", 2);
  storeIngredient(pantry, pantryApples, 500);
  storeIngredient(pantry, pantryCrust, 500);
  storeIngredient(pantry, pantrySugar, 500);
  storeIngredient(pantry, pantryCinnamon, 500);
  testCanMakeAny(pantry, book);
}

void test10(void) {
  struct Book * book = newBook();
  struct Pantry * pantry = newPantry();
  struct Recipe * recipe = newRecipe("Apple Pie", 8);
  struct Ingredient * apples = newIngredient("apples", 1);
  struct Ingredient * crust = newIngredient("crust", 4);
  struct Ingredient * sugar = newIngredient("sugar", 4);
  struct Ingredient * cinnamon = newIngredient("cinnamon", 2);
  addIngredient(recipe, apples, 500);
  addIngredient(recipe, crust, 200);
  addIngredient(recipe, sugar, 100);
  addIngredient(recipe, cinnamon, 50);
  addRecipe(book, recipe);
  struct Ingredient * pantryApples = newIngredient("apples", 1);
  struct Ingredient * pantryCrust = newIngredient("crust", 4);
  struct Ingredient * pantrySugar = newIngredient("sugar", 4);
  struct Ingredient * pantryCinnamon = newIngredient("cinnamon", 2);
  storeIngredient(pantry, pantryApples, 400);
  storeIngredient(pantry, pantryCrust, 500);
  storeIngredient(pantry, pantrySugar, 500);
  storeIngredient(pantry, pantryCinnamon, 500);
  testCanMakeAllFails(pantry, book);
}

void test11(void) {
  struct Book * book = newBook();
  struct Pantry * pantry = newPantry();
  struct Recipe * recipe = newRecipe("Apple Pie", 8);
  struct Ingredient * apples = newIngredient("apples", 1);
  struct Ingredient * crust = newIngredient("crust", 4);
  struct Ingredient * sugar = newIngredient("sugar", 4);
  struct Ingredient * cinnamon = newIngredient("cinnamon", 2);
  addIngredient(recipe, apples, 500);
  addIngredient(recipe, crust, 200);
  addIngredient(recipe, sugar, 100);
  addIngredient(recipe, cinnamon, 50);
  addRecipe(book, recipe);
  struct Ingredient * pantryApples = newIngredient("apples", 1);
  struct Ingredient * pantryCrust = newIngredient("crust", 4);
  struct Ingredient * pantrySugar = newIngredient("sugar", 4);
  struct Ingredient * pantryCinnamon = newIngredient("cinnamon", 2);
  storeIngredient(pantry, pantryApples, 400);
  storeIngredient(pantry, pantryCrust, 500);
  storeIngredient(pantry, pantrySugar, 500);
  storeIngredient(pantry, pantryCinnamon, 500);
  testCanMakeAnyFails(pantry, book);
}

void test12(void) {
  struct Book * book = newBook();
  struct Pantry * pantry = newPantry();
  struct Recipe * recipe = newRecipe("Apple Pie", 8);
  struct Ingredient * apples = newIngredient("apples", 1);
  struct Ingredient * crust = newIngredient("crust", 4);
  struct Ingredient * sugar = newIngredient("sugar", 4);
  struct Ingredient * cinnamon = newIngredient("cinnamon", 2);
  addIngredient(recipe, apples, 500);
  addIngredient(recipe, crust, 200);
  addIngredient(recipe, sugar, 100);
  addIngredient(recipe, cinnamon, 50);
  addRecipe(book, recipe);
  struct Ingredient * pantryApples = newIngredient("apples", 1);
  struct Ingredient * pantryCrust = newIngredient("crust", 4);
  struct Ingredient * pantrySugar = newIngredient("sugar", 4);
  struct Ingredient * pantryCinnamon = newIngredient("cinnamon", 2);
  storeIngredient(pantry, pantryApples, 500);
  storeIngredient(pantry, pantryCrust, 500);
  storeIngredient(pantry, pantrySugar, 500);
  storeIngredient(pantry, pantryCinnamon, 500);
  struct Book * dietBook;
  dietBook = canMakeAny(pantry, book);
  testWithinCalorieLimit(pantry, dietBook, 250);
}
void test13(void) { 
  struct Pantry * pantry = newPantry();
  struct Ingredient * apples = getIngredient("apples", pantry);
  CU_ASSERT_PTR_NULL(apples);
}

int main() {
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry()) { return CU_get_error(); }

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_1", NULL, NULL);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (
      (NULL == CU_add_test(pSuite, "testNewIngredient: Apple", test00)) ||
      (NULL == CU_add_test(pSuite, "testNewRecipe: Apple Pie", test01)) ||
      (NULL == CU_add_test(pSuite, "testNewPantry", test02)) ||
      (NULL == CU_add_test(pSuite, "testNewBook", test03)) ||
      (NULL == CU_add_test(pSuite, "testAddIngredient: Apple -> Apple Pie", test04)) ||
      (NULL == CU_add_test(pSuite, "testStoreIngredient: Apple", test05)) ||
      (NULL == CU_add_test(pSuite, "testAddRecipe: Apple Pie", test06)) ||
      (NULL == CU_add_test(pSuite, "testCaloriesPerServing: Apple Pie", test07)) ||
      (NULL == CU_add_test(pSuite, "testCanMakeAll: Apple Pie w/ enough ingredients", test08)) ||
      (NULL == CU_add_test(pSuite, "testCanMakeAny: Apple Pie w/ enough ingredients", test09)) ||
      (NULL == CU_add_test(pSuite, "testCanMakeAll: Apple Pie w/o enough ingredients", test10)) ||
      (NULL == CU_add_test(pSuite, "testCanMakeAny: Apple Pie w/o enough ingredients", test11)) ||
      (NULL == CU_add_test(pSuite, "testWithinCalorieLimit: Apple Pie w/in calorie limit", test12)) ||
      (NULL == CU_add_test(pSuite, "testGetIngredient: No ingredient exists in pantry", test13))
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
