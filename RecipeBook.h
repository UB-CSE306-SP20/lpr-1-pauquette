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

/* Singly-linked list structure that holds a pointer to the first
   ingedient in the pantry (or NULL if pantry is empty) */

struct Pantry {
  struct Ingredient * head;
};

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

/* Singly-linked list structure that holds a pointer to the first
   recipe in the book (or NULL if book is empty) */

struct Book {
  struct Recipe * head;
};
