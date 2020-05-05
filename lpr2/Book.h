#ifndef BOOK_H
#define BOOK_H

#include "Recipe.h"

struct Book {
  struct NodeRecipe * head;
};

struct Book * newBook();

void addRecipe(struct Book * book, struct Recipe * recipe);

#endif
