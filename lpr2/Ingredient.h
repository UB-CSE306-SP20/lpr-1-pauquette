#ifndef INGREDIENT_H
#define INGREDIENT_H

struct Ingredient {
  char * name;
  int caloriesPerGram;
};

struct Ingredient * newIngredient(char * n, int cpg);

struct Ingredient * mergeIngredients(struct Ingredient * a, struct Ingredient * b);

char * toString(struct Ingredient * a);

#endif
