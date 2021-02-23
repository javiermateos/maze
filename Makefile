##
# Laberinto
#
# @file Makefile
# @version 1.0
##
PDIR := $(shell pwd)
SDIR := src
IDIR := include
TDIR := test
ODIR := obj
BDIR := build
LDIR := lib
DDIR := data

NAME := maze
L_NAMES := point.c map.c utils.c functions.c
S_NAMES := stack.c queue.c list.c tree.c map_solver.c main.c
T_NAMES := map_test.c point_test.c stack_test.c list_test.c queue_test.c tree_test.c

CC := gcc
CFLAGS := -g -I$(IDIR) -ansi -pedantic -Wall -Wextra

SFILES := c
OFILES := o
L_SOURCES := $(foreach sname, $(L_NAMES), $(SDIR)/$(sname))
L_OBJECTS := $(patsubst $(SDIR)/%.$(SFILES), $(ODIR)/%.$(OFILES), $(L_SOURCES))
S_SOURCES := $(foreach sname, $(S_NAMES), $(SDIR)/$(sname)) 
S_OBJECTS := $(patsubst $(SDIR)/%.$(SFILES), $(ODIR)/%.$(OFILES), $(S_SOURCES))
T_SOURCES := $(foreach sname, $(T_NAMES), $(TDIR)/$(sname))

NAME_TESTS := $(patsubst $(TDIR)/%.$(SFILES), $(BDIR)/%, $(T_SOURCES))

EXE := $(BDIR)/$(NAME)

.DEFAULT_GOAL := bin

all: build_project bin tests

# Build the folders needed by the project
build_project:
	@mkdir -pv $(BDIR)
	@mkdir -pv $(ODIR)

tests: build_project $(NAME_TESTS)
	@echo "*******************************************************************"
	@echo ">Tests compiled succesfully!"
	@echo "*******************************************************************"

bin: build_project $(EXE)
	@echo "*******************************************************************"
	@echo ">Binary compiled succesfully!"
	@echo "*******************************************************************"
	
# Rule to compile the tests
$(NAME_TESTS): $(BDIR)/%_test: $(L_OBJECTS) $(ODIR)/%_test.$(OFILES) $(ODIR)/%.$(OFILES) 
	@echo ">Building test $@..."
	$(CC) $^ -o $@

# Rule to make the binary
$(EXE): $(L_OBJECTS) $(S_OBJECTS)
	@echo ">Building binary $@..."
	$(CC) $^ -o $@

# Rule to make every object file
$(ODIR)/%$(OFILES): */%$(SFILES)
	@echo ">Compiling $@..."
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@rm -rfv $(ODIR) $(LDIR) $(BDIR)
	@rm -rfv $(NAME)

.PHONY: run_test
run_test: tests
	@echo ">Running point_test..."
	$(BDIR)/point_test
	@echo ">Running map_test with m1.txt..."
	$(BDIR)/map_test $(DDIR)/m1.txt
	@echo ">Running map_test with m2.txt..."
	$(BDIR)/map_test $(DDIR)/m2.txt
	@echo ">Running map_test with m3.txt..."
	$(BDIR)/map_test $(DDIR)/m3.txt
	@echo ">Running stack_test with m1.txt..."
	$(BDIR)/stack_test $(DDIR)/m1.txt
	@echo ">Running list_test with data.txt..."
	$(BDIR)/list_test $(DDIR)/data.txt
	@echo ">Running queue_test with points.txt..."
	$(BDIR)/queue_test $(DDIR)/points.txt
	@echo ">Running tree_test with data.txt..."
	$(BDIR)/tree_test $(DDIR)/data.txt

.PHONY: run_testv
run_testv: tests
	@echo ">Running point_test with valgrind..."
	valgrind --leak-check=full $(BDIR)/point_test
	@echo ">Running map_test with valgrind..."
	valgrind --leak-check=full $(BDIR)/map_test $(DDIR)/m1.txt
	@echo ">Running stack_test with valgrind..."
	valgrind --leak-check=full $(BDIR)/stack_test $(DDIR)/m1.txt
	@echo ">Running list_test with valgrind..."
	valgrind --leak-check=full $(BDIR)/list_test $(DDIR)/data.txt
	@echo ">Running queue_test with valgrind..."
	valgrind --leak-check=full $(BDIR)/queue_test $(DDIR)/points.txt
	@echo ">Running tree_test with valgrind..."
	valgrind --leak-check=full $(BDIR)/tree_test $(DDIR)/data.txt

run: bin
	@echo ">Running maze with m1.txt and stack..."
	$(BDIR)/maze $(DDIR)/m1.txt stack
	@echo ">Running maze with m1.txt and queue..."
	$(BDIR)/maze $(DDIR)/m1.txt queue
	@echo ">Running maze with m1.txt and recursive..."
	$(BDIR)/maze $(DDIR)/m1.txt recursive

runv: bin
	@echo ">Running maze with m1.txt and stack..."
	valgrind --leak-check=full $(BDIR)/maze $(DDIR)/m1.txt stack
	@echo ">Running maze with m1.txt and queue..."
	valgrind --leak-check=full $(BDIR)/maze $(DDIR)/m1.txt queue
	@echo ">Running maze with m1.txt and recursive..."
	valgrind --leak-check=full $(BDIR)/maze $(DDIR)/m1.txt recursive

# Deteccion de dependencias automatica
CFLAGS += -MMD
DEPEND_FILES := $(wildcard $(ODIR)/*.d)
-include $(DEPEND_FILES)

# end
