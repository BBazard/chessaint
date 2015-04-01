/*This file is part of the ChessAInt project 2015*/
/** 
 *  @file identifier.c
 *  @brief identifier functions
 *
 *  This file contains the functions to manipulate
 *  Identifier type
 *
 */

#include "include/identifier.h"

/** 
 *  @fn void identifier_path(Identifier id, int* path)
 *  @brief Computes path based on an arc id (recursive)
 *  @param[in] id The id of the arc
 *  @param[out] path The int array containing the path
 *
 *  This function computes a path from root to an arc of
 *  identifier id, puting the path in an int array.
 *  First arc is put in the first address of the array
 *
 */

void identifier_path(Identifier id, int* path) {
  if (mpz_sgn(id)) {
    Identifier idsub;
    Identifier iddiv;
    mpz_inits(idsub,iddiv,NULL);

    int r;    
    r=mpz_tdiv_ui(id,SON_MAX_NB);
    mpz_sub_ui(idsub,id,r);
    mpz_divexact_ui(iddiv, idsub, SON_MAX_NB);

    identifier_path(iddiv, path);

    ++path;
    *path=r;
  }
  else {
    *path=mpz_tdiv_ui(id,SON_MAX_NB);
  }
}
