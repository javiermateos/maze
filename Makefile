##
# Laberinto
#
# @file Makefile
# @version 1.0
##
TOPDIR := $(pwd)
SDIR := src
IDIR := include
TDIR := test
ODIR := obj
BDIR := build
LDIR := lib

NAME := libmaze
L_NAMES:= point.c map.c
T_NAMES:= map_test.c point_test.c

CC := gcc
CFLAGS := -g -I$(IDIR) -ansi -pedantic -Wall -Wextra

SFILES := c
OFILES := o
LFILES := a
L_SOURCES := $(foreach sname, $(L_NAMES), $(SDIR)/$(sname))
L_OBJECTS := $(patsubst $(SDIR)/%.$(SFILES), $(ODIR)/%.$(OFILES), $(L_SOURCES))

T_SOURCES := $(foreach sname, $(T_NAMES), $(TDIR)/$(sname))
TESTS := $(patsubst $(TDIR)/%.$(SFILES), $(BDIR)/%, $(T_SOURCES))

LIB := $(LDIR)/$(NAME).$(LFILES)

build: build_target build_tests clear

build_tests: $(TESTS)
	@echo "Tests compiled..."

build_target: $(LIB)
	@echo "Static library builded..."
	
# Rule to compile the tests
$(TESTS): $(BDIR)/%: $(ODIR)/%.$(OFILES) $(L_OBJECTS)
	@echo "Building tests..."
	@mkdir -pv $(BDIR)
	$(CC) $^ -o $@

# Rule to make the static library
$(LIB): $(L_OBJECTS)
	@echo "Building static library..."
	@mkdir -pv $(LDIR)
	ar rcs $@ $<

# Rule to make every object file
$(ODIR)/%$(OFILES): */%$(SFILES)
	@echo "Compiling $@..."
	@mkdir -pv $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

clear:
	@echo "Removing temporary files..."
	@rm -rfv $(ODIR)/*.o 

.PHONY: clean
clean:
	@rm -rfv $(ODIR) $(LDIR) $(BDIR)  

.PHONY: test
test: build_tests
	@echo ">>>>>>Running point_test"
	$(BDIR)/point_test
	@echo ">>>>>>Running map_test"
	$(BDIR)/map_test m1.txt

.PHONY: testv
testv: build_tests
	@echo ">>>>>>Running point_test with valgrind"
	valgrind --leak-check=full $(BDIR)/point_test
	@echo ">>>>>>Running map_test with valgrind"
	valgrind --leak-check=full $(BDIR)/map_test m1.txt

# Deteccion de dependencias automatica
CFLAGS += -MMD
DEPEND_FILES := $(wildcard $(ODIR)/*.d)
-include $(DEPEND_FILES)

# end
