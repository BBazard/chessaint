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
 *  @fn void stack_init(Stack *s)
 *  @brief Create a stack
 *
 *  Initialisation of a stack
 *
 */

void stack_init(Stack *s) {
  mpz_init_set_ui(*s, 0);
}

/** 
 *  @fn void stack_free(Stack *s)
 *  @brief Free a stack
 *
 *  Free the memory space allocated for stack pointed
 *  by s
 *
 */

void stack_free(Stack *s) {
  mpz_clear(*s);
  s = NULL;
}

/** 
 *  @fn void stack_push(Stack *s, int item)
 *  @brief add an item to the stack
 *
 *  This function adds an int to the stack
 *
 */

void stack_push(Stack *s, int item) {
  mpz_t tmp;
  mpz_init_set(tmp, *s);

  mpz_mul_si(*s, tmp, 1000000000);

  mpz_set(tmp, *s);
  mpz_add_ui(*s, tmp, (unsigned long int) item);
  mpz_clear(tmp);
}

/** 
 *  @int stack_pop(Stack *s);
 *  @brief Extract an item from the stack
 *  @return int the first element of the stack
 *
 *  This function extract an item from the stack
 *  and returns it
 *
 */

int stack_pop(Stack *s) {
  mpz_t tmp;
  int ret;
  mpz_init_set(tmp, *s);

  ret = (mpz_tdiv_q_ui(*s, tmp, 1000000000));
  mpz_clear(tmp);
  return ret;
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
 *  @fn int identifier_is_leaf(Identifier id)
 *  @brief Check if an arc is a leaf of the graph
 *  @param[in] id The identifier used
 *  @return 1 If the arc is a leaf
 *  @return 0 Otherwise
 *
 *  This function check if a given arc is a leaf
 *  or not, given it's Identifier
 *
 */

int identifier_is_leaf(Identifier id) {
  Identifier tmp;
  int ret;
  mpz_init(tmp);

  mpz_tdiv_q_ui(tmp, id, 100000);
  ret = (mpz_tdiv_ui(tmp, 10) > 1);
  mpz_clear(tmp);
  return ret;
}

/** 
 *  @fn int identifier_is_white(Identifier id)
 *  @brief Check if an arc is a white move
 *  @param[in] id The identifier used
 *  @return 1 If the arc is a white move
 *  @return 0 Otherwise
 *
 *  This function check if a given arc is a white move
 *  or not, given it's Identifier
 *
 */

int identifier_is_white(Identifier id) {
  Identifier tmp;
  int ret;
  mpz_init(tmp);

  mpz_tdiv_q_ui(tmp, id, 100000);
  ret = (mpz_tdiv_ui(tmp, 10) % 2);
  mpz_clear(tmp);
  return ret;
}

/** 
 *  @fn int identifier_is_passant(Identifier id)
 *  @brief Check if an arc contains a enpassant move
 *  @param[in] id The identifier used
 *  @return 1 If the arc contains enpassant
 *  @return 0 Otherwise
 *
 *  This function check if a given arc contains a enpassant move
 *  or not, given it's Identifier
 *
 */

int identifier_is_passant(Identifier id) {
  Identifier tmp;
  int ret;
  mpz_init(tmp);

  mpz_tdiv_q_ui(tmp, id, 10000);
  ret = mpz_tdiv_ui(tmp, 10);
  mpz_clear(tmp);
  return ret;
}

/** 
 *  @fn int identifier_get_cast(Identifier id)
 *  @brief Get the castling state
 *  @param[in] id The identifier used
 *  @return [|0;63|] Meaning a state of castling
 *
 *  This function check the castling state of an arc, given it's
 *  Identifier
 *
 */

int identifier_get_cast(Identifier id) {
  Identifier tmp;
  int ret;
  mpz_init(tmp);

  mpz_tdiv_q_ui(tmp, id, 100);
  ret = mpz_tdiv_ui(tmp, 100);
  mpz_clear(tmp);
  return ret;
}

/** 
 *  @fn int identifier_get_halfmove(Identifier id)
 *  @brief Get the number of "half move clock"
 *  @param[in] id The identifier used
 *  @return [|0;51|] the number of half moves
 *
 *  This function returns the number of half moves done
 *  since the last pawn move or capture, it is used for
 *  the fifty-move rule.
 *
 */

int identifier_get_halfmove(Identifier id) {
  int ret;

  ret = mpz_tdiv_ui(id, 100);
  return ret;
}

/** 
 *  @fn int identifier_get_fullmove(Identifier id)
 *  @brief Get the number of moves
 *  @param[in] id The identifier used
 *  @return (int) the number of moves
 *
 *  This function returns the number of moves done
 *  since the game has started
 *
 */

int identifier_get_fullmove(Identifier id) {
  int ret;

  if ( (ret = (mpz_sizeinbase(id, 10) -6))%4 != 0)
    return -1;
  else
    return ret/4;
}

int identifier_is_equal(Identifier left, Identifier right) {
  return !(mpz_cmp(left, right));
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
  if (mpz_cmp_ui(id, 100) >= 0) {
    Identifier idsub;
    Identifier iddiv;
    mpz_inits(idsub, iddiv, NULL);

    unsigned long int r;
    r = mpz_tdiv_ui(id, 100);
    mpz_sub_ui(idsub, id, r);
    mpz_divexact_ui(iddiv, idsub, 100);

    identifier_path(iddiv, path);

    ++(path->current);
    *(path->current) = r;
  } else {
    *(path->current) = mpz_tdiv_ui(id, 100);
  }
}
