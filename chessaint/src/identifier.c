/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 */

#include "include/identifier.h"

/**
 *  @brief 4096 represents 8*8 * 8*8 ie the number of pairs
 *  of coords possible
 *
 */

#define MAX_PAIRS 8889

/**
 *  @fn int stack_contract(int p1, int p2, int p3, int p4)
 *  @brief Transform four int in one
 *  @param[in] p1 Most Signifiant Bit
 *  @param[in] p2,p3,p4 Others bits
 *  @return int "p1p2p3p4"
 *
 *  Return the int which is the "concatenation" of p1...p4, MSB first
 *
 */

int stack_contract(int p1, int p2, int p3, int p4) {
  return p1*1000 + p2*100 + p3*10 + p4;
}

/**
 *  @fn void stack_expand(int *p1, int *p2, int *p3, int *p4, int todivide)
 *  @brief Transform an int in four
 *  @param[out] p1,p2,p3,p4 Where p1 is todivide MSB and p4 todivide LSB
 *  @param[in] todivide The integer (must be in [|0; 10000|]) to divide in four
 *  @bug last "tmp =" is useless
 *
 *  Divide todivide in p1, p2, p3 and p4
 *
 */

void stack_expand(int *p1, int *p2, int *p3, int *p4, int todivide) {
  int tmp = todivide;

  *p4 = tmp%10;
  tmp = (tmp-*p4)/10;
  *p3 = tmp%10;
  tmp = (tmp-*p3)/10;
  *p2 = tmp%10;
  tmp = (tmp-*p2)/10;
  *p1 = tmp%10;
  tmp = (tmp-*p1)/10;
}

/**
 *  @fn void stack_init(Stack *s)
 *  @brief Create a stack
 *
 *  Initialisation of a stack
 *  @note need stack_free afterwards
 *
 */

void stack_init(Stack *s) {
  mpz_init(*s);
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

  mpz_mul_si(*s, tmp, MAX_PAIRS);

  mpz_set(tmp, *s);
  mpz_add_ui(*s, tmp, (unsigned long int) item);
  mpz_clear(tmp);
}

/**
 *  @fn int stack_pop(Stack *s);
 *  @brief Extract an item from the stack
 *  @return -1 If the stack is empty
 *  @return int the first element of the stack
 *
 *  This function extract an item from the stack
 *  and returns it
 *  @note If the stack contains 0 it means it is empty since
 *  the moveGenerator will never add the a1a1 move.
 *
 */

int stack_pop(Stack *s) {
  mpz_t tmp;
  int ret;
  if (!mpz_cmp_ui(*s, 0)) {
    ret = -1;
  } else {
    mpz_init_set(tmp, *s);

    ret = (mpz_tdiv_q_ui(*s, tmp, MAX_PAIRS));
    mpz_clear(tmp);
  }
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
 *  or not, given its Identifier
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
 *  or not, given its Identifier
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
 *  or not, given its Identifier
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
 *  @return [|0;15|] Meaning a state of castling
 *
 *  This function check the castling state of an arc, given its
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

/**
 *  @fn void identifier_to_stack(Identifier id, Stack *stack)
 *  @brief Puts the "history" part of id in a stack
 *  @param[in] id The identifier holding the data
 *  @param[out] stack The stack in which to store extracted data
 *
 *  Extract the "history" part of the identifier (the moves since root board)
 *  and store it in a stack
 *
 */

void identifier_to_stack(Identifier id, Stack *stack) {
  stack_init(stack);
  mpz_tdiv_q_ui(*stack, id, 1000000);
}

/**
 *  @fn void stack_to_identifier(Identifier *id, Stack stack)
 *  @brief Puts the content of a stack in the identifier id
 *  @param[in] stack The stack in which to store extracted data
 *  @param[out] id The identifier holding the data
 *
 *  Puts the data of the stack in the identifier, as the "history"
 *  part of the identifier
 *
 */

void stack_to_identifier(Identifier *id, Stack stack) {
  mpz_init(*id);
  mpz_mul_ui(*id, stack, 1000000);
}

/**
 *  @fn int identifier_is_equal(Identifier left, Identifier right)
 *  @brief Compares identifiers
 *  @return 1 If identifier are equal
 *  @return 0 Otherwise
 *
 */

int identifier_is_equal(Identifier left, Identifier right) {
  return !(mpz_cmp(left, right));
}

