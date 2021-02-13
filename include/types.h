/*
 * @file types.h
 * @author Javier Mateos Najari
 */

#ifndef TYPES_H
#define	TYPES_H

#include <stdio.h>

typedef enum {
    FALSE, TRUE
} Bool;

typedef enum {
    ERR, OK
} Status;

typedef enum {
    RIGHT, UP, LEFT, DOWN
} Move;

#endif	/* TYPES_H */
