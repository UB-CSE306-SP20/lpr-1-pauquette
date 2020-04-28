# OS identification from: https://stackoverflow.com/questions/714100/os-detecting-makefile
OS := $(shell uname -s)

ifeq ($(OS), Darwin) 
  CUNIT_PATH_PREFIX = /usr/local/Cellar/cunit/2.1-3/
  CUNIT_DIRECTORY = cunit
endif
ifeq ($(OS), Linux) 
  CUNIT_PATH_PREFIX = /util/CUnit/
  CUNIT_DIRECTORY = CUnit/
endif

CC = gcc
FLAGS = -g -Wall -std=c11

RecipeBook.o: RecipeBook.c
	$(CC) -c $(FLAGS) RecipeBook.c

tests.o: tests.c
	$(CC) -c $(FLAGS) -I $(CUNIT_PATH_PREFIX)include/$(CUNIT_DIRECTORY) tests.c

tests: RecipeBook.o tests.o
	gcc -Wall -L $(CUNIT_PATH_PREFIX)lib -I $(CUNIT_PATH_PREFIX)include/$(CUNIT_DIRECTORY) -o tests RecipeBook.o tests.o -lcunit


clean:
	rm -rf *~ *.o program tests runner *.dSYM
