TOPDIR := ..

SDIR := .
ODIR := $(TOPDIR)/obj
IDIR := $(TOPDIR)/include

BDIR := $(TOPDIR)/lib

NAME := libmaze.a
C_SOURCES := point.c map.c

CC := gcc
CFLAGS := -g -Wall -Wextra -pedantic -ansi -I$(IDIR)

SFILES := c
OFILES := o
SOURCES := $(foreach sname, $(C_SOURCES), $(SDIR)/$(sname))
OBJECTS := $(patsubst $(SDIR)/%.$(SFILES), $(ODIR)/%.$(OFILES), $(SOURCES))

EXE := $(BDIR)/$(NAME)

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $^ -o $@

$(ODIR)/%$(OFILES): $(SDIR)/%$(SFILES)
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Deteccion de dependencias automatica
CFLAGS += -MMD
DEPEND_FILES := $(wildcard $(ODIR)/*.d)
-include $(DEPEND_FILES)
