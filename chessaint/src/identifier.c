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
 *  @fn Path* path_init(int init_depth)
 *  @brief Initialisation of a Path type element
 *  @return  If succeful
 *
 *  This function allocate memory for the array pointer, and make other
 *  elements of the structure equal to what they should.
 *
 */

Path path_init(int init_depth) {
  int i;
  Path new_path = { .depth = init_depth,
                    .array = malloc(init_depth*sizeof(unsigned long int))
  };
  new_path.current = new_path.array;
  for (i = 0; i < init_depth; i++)
    new_path.array[i] = -1;
  return new_path;
}

/** 
 *  @fn void path_reset(Path* path)
 *  @brief Reset the current pointer
 *
 *  This function make the current pointer equal to the array
 *  pointer.
 *
 */

void path_reset(Path *path) {
  path->current = path->array;
}

/** 
 *  @fn void identifier_print(Identifier id)
 *  @brief Print an identifier
 *
 *  This function prints an identifier on the standard
 *  output.
 *
 */

void identifier_print(Identifier id) {
  FILE* stdout;
  stdout = fopen("/dev/stdout", "a");
  fputc('\n', stdout);
  mpz_out_str(stdout, 10, id);
  fputc('\n', stdout);

  fclose(stdout);
}

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

void identifier_path(Identifier id, Path* path) {
   if (mpz_cmp_ui(id, SON_MAX_NB) >= 0) {
    Identifier idsub;
    Identifier iddiv;
    mpz_inits(idsub,iddiv,NULL);

    unsigned long int r;
    r=mpz_tdiv_ui(id,SON_MAX_NB);
    mpz_sub_ui(idsub,id,r);
    mpz_divexact_ui(iddiv, idsub, SON_MAX_NB);

    identifier_path(iddiv, path);

    ++(path->current);
    *(path->current) = r;
   }
  else {
    *(path->current)=mpz_tdiv_ui(id,SON_MAX_NB);
  }
}
