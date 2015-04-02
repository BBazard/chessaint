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

/** 
 *  @typedef Path
 *  @brief Definition of the Path type
 *
 *  Defines Path type as pointer on Path structure
 *
 */
 
typedef struct Path Path;

/** 
 *  @struct Path_element
 *  @brief Definition of the Path structure
 *
 *  Represents a path in a graph
 *
 */

struct Path {
  int depth; /**< The depth the path ends, also the size of the array */
  unsigned long int * const array; /**< The array storing the data */
  unsigned long int *current; /**< Pointer on a block of the array */
};

Path path_init(int init_depth);
void path_reset(Path* path);

void identifier_print(Identifier id);

void identifier_path(Identifier id, Path* path);

#endif /*TRUNK_CHESSAINT_INCLUDE_HEURISTIC_H_*/
