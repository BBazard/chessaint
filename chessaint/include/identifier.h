/*This file is part of the ChessAInt project 2015*/
/** 
 *  @file identifier.h
 *  @brief identifier structure header
 *
 *  This file contains the prototypes of the functions developped
 *  in identifier.c file
 *
 */

#ifndef TRUNK_CHESSAINT_INCLUDE_HEURISTIC_H_
#define TRUNK_CHESSAINT_INCLUDE_HEURISTIC_H_

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

/** 
 *  @typedef Identifier
 *  @brief Definition of the Identifier type
 *
 *  Rename type mpz_t from GNU Multi-Precision library
 *
 */

typedef mpz_t Identifier;

/** 
 *  @typedef Stack
 *  @brief Definition of the Stack type
 *
 *  Rename type mpz_t from GNU Multi-Precision library
 *
 */

typedef mpz_t Stack;

void stack_init(Stack *s);
void stack_free(Stack *s);
void stack_push(Stack *s, int item);
int stack_pop(Stack *s);

void identifier_print(Identifier id);

int identifier_is_leaf(Identifier id);
int identifier_is_white(Identifier id);
int identifier_is_passant(Identifier id);
int identifier_get_cast(Identifier id);
int identifier_get_halfmove(Identifier id);
int identifier_get_fullmove(Identifier id);

int identifier_is_equal(Identifier left, Identifier right);

#endif /*TRUNK_CHESSAINT_INCLUDE_HEURISTIC_H_*/
