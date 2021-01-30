##
# Laberinto
#
# @file Makefile
# @version 1.0
##
DIR := $(PWD)
SDIR := src
IDIR := include
TDIR := test
ODIR := obj
BDIR := build
LDIR := lib

NAME := libmaze.a
C_SOURCES:= point.c map.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p1_e1"
	./p1_e1
	@echo ">>>>>>Running p1_e2"
	./p1_e2 m1.txt

runv:
	@echo ">>>>>>Running p1_e1 with valgrind"
	valgrind --leak-check=full ./p1_e1
	@echo ">>>>>>Running p1_e2 with valgrind"
	valgrind --leak-check=full ./p1_e2 m1.txt
