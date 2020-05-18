#include <stdlib.h>
#include "Book.h"
#include "Recipe.h"

struct Book * newBook() {
  struct Book * this;
  this = malloc(sizeof(*this));
  this -> head = NULL;
  return this;
}

void addRecipe(struct Book * book, struct Recipe * recipe) {
  // TODO
}
