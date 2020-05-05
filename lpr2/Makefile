# Makefile generated automatically by makeMake, version 1.0, on Thu May  3 08:55:27 EDT 2018

# Variables used by makefile

CC=gcc
CFLAGS=-Wall -std=c11 -g
EXE=main
OBJECTS=Recipe.o Pantry.o NodeRecipe.o NodeIngredientQuantity.o Ingredient.o Book.o 

# Recipes for targets

Book.o: Book.c Book.h
	$(CC) $(CFLAGS) -c Book.c

Ingredient.o: Ingredient.c Ingredient.h
	$(CC) $(CFLAGS) -c Ingredient.c

NodeIngredientQuantity.o: NodeIngredientQuantity.c \
  NodeIngredientQuantity.h
	$(CC) $(CFLAGS) -c NodeIngredientQuantity.c

NodeRecipe.o: NodeRecipe.c NodeRecipe.h
	$(CC) $(CFLAGS) -c NodeRecipe.c

Pantry.o: Pantry.c Pantry.h
	$(CC) $(CFLAGS) -c Pantry.c

Recipe.o: Recipe.c Recipe.h
	$(CC) $(CFLAGS) -c Recipe.c

main: $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(EXE).c -lm

# PHONY targets

.PHONY: clean
clean:
	rm -rf *~ $(OBJECTS) $(EXE) *.zip

# End of makefile
