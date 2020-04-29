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
FLAGS = -g -O0 -Wall -fprofile-arcs -ftest-coverage -std=c11

RecipeBook.o: RecipeBook.c
	$(CC) -c $(FLAGS) RecipeBook.c

tests: RecipeBook.o tests.c
	$(CC) $(FLAGS) -L $(CUNIT_PATH_PREFIX)lib -I $(CUNIT_PATH_PREFIX)include/$(CUNIT_DIRECTORY) RecipeBook.o tests.c -o tests -lcunit -lgcov


clean:
	rm -rf *~ *.o a.out tests runner *.xml *.gc?? *.dSYM
