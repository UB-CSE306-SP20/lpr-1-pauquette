#ifndef NODE_RECIPE_H
#define NODE_RECIPE_H

struct NodeRecipe {
  struct Recipe * value;
  struct NodeRecipe * next;
};

struct NodeRecipe * newNodeRecipe(struct Recipe *v, struct NodeRecipe * n);

#endif
