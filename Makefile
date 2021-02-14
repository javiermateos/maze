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
T_NAMES := map_test.c point_test.c stack_test.c queue_test.c tree_test.c

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

build: build_project tests bin clear

# Build the folders needed by the project
build_project:
	@mkdir -pv $(BDIR)
	@mkdir -pv $(ODIR)

.PHONY: tests
tests: build_project $(NAME_TESTS)
	@echo "*******************************************************************"
	@echo ">Tests compiled succesfully!"
	@echo "*******************************************************************"

bin: $(NAME)
	@echo "*******************************************************************"
	@echo ">Binary compiled..."
	@echo "*******************************************************************"
	
# Rule to compile the tests
$(NAME_TESTS): $(BDIR)/%_test: $(L_OBJECTS) $(ODIR)/%_test.$(OFILES) $(ODIR)/%.$(OFILES) 
	@echo ">Building test $@..."
	$(CC) $^ -o $@

# Rule to make the binary
$(NAME): $(L_OBJECTS) $(S_OBJECTS)
	@echo ">Building binary $@..."
	$(CC) $^ -o $@

# Rule to make every object file
$(ODIR)/%$(OFILES): */%$(SFILES)
	@echo ">Compiling $@..."
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	@echo ">Removing temporary files..."
	@rm -rfv $(ODIR)/*.o 

.PHONY: clean
clean:
	@rm -rfv $(ODIR) $(LDIR) $(BDIR)  

.PHONY: test
test: build_tests
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

.PHONY: testv
testv: build_tests
	@echo ">Running point_test with valgrind..."
	valgrind --leak-check=full $(BDIR)/point_test
	@echo ">Running map_test with valgrind..."
	valgrind --leak-check=full $(BDIR)/map_test $(DDIR)/m1.txt
	@echo ">Running stack_test with m1.txt and valgrind..."
	valgrind --leak-check=full $(BDIR)/stack_test $(DDIR)/m1.txt

# Deteccion de dependencias automatica
CFLAGS += -MMD
DEPEND_FILES := $(wildcard $(ODIR)/*.d)
-include $(DEPEND_FILES)

# end
