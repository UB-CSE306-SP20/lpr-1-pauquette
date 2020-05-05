#ifndef NODE_INGREDIENT_QUANTITY_H
#define NODE_INGREDIENT_QUANTITY_H

struct NodeIngredientQuantity {
  struct Ingredient * ingredient;
  int grams;
  struct NodeIngredientQuantity * next;
};

struct NodeIngredientQuantity * newNodeIngredientQuantity(struct Ingredient * i, int g, struct NodeIngredientQuantity * n);

#endif
