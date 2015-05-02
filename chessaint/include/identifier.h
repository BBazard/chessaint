/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */

#ifndef CHESSAINT_INCLUDE_IDENTIFIER_H_
#define CHESSAINT_INCLUDE_IDENTIFIER_H_

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

int stack_contract(int p1, int p2, int p3, int p4);
void stack_expand(int *p1, int *p2, int *p3, int *p4, int todivide);
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

void identifier_to_stack(Identifier id, Stack *stack);
void stack_to_identifier(Identifier *id, Stack stack);

int identifier_is_equal(Identifier left, Identifier right);

#endif /* CHESSAINT_INCLUDE_IDENTIFIER_H_ */

