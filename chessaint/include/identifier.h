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

#define SON_MAX_NB 100

/** 
 *  @typedef Identifier
 *  @brief Definition of the Identifier type
 *  
 *  Rename type mpz_t from GNU Multi-Precision library
 *
 */

typedef mpz_t Identifier;

int identifier_get_depth(Identifier id);
void identifier_path(Identifier id, int* Path);
void identifier_next(Identifier father_id, Identifier* son_id, int son_number); 
int identifier_is_father(Identifier father_id, Identifier son_id);

#endif /*TRUNK_CHESSAINT_INCLUDE_HEURISTIC_H_*/
