/* Copyright 2015 Hugo GANGLOFF */
/** 
 *  @file chessboard.c
 *  @brief chessboard handling functions
 *  @author HGangloff
 *  @version 1.0
 *  @date 6 March 2015
 *
 *  This files implements chessboard handling functions 
 *  or placing pieces in a given position
 *
 */

#include <ctype.h>
#include <unistd.h>
#include "../include/chessboard.h"

int color[NBCASES] = {
  2, 2, 2, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2, 2, 2,
  9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1
}; /*WHITE BLACK or EMPTY*/

int piece[NBCASES] = {
  3, 2, 1, 4, 5, 1, 2, 3,
  0, 0, 0, 0, 0, 0, 0, 0,
  9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9,
  0, 0, 0, 0, 0, 0, 0, 0,
  3, 2, 1, 4, 5, 1, 2, 3
}; /*PAWN BISHOP KNIGHT ROOK QUEEN KING or EMPTY */

char pieceChar[12] = {
  'P', 'B', 'N', 'R', 'Q', 'K', 'p', 'b', 'n', 'r', 'q', 'k'
}; /* Pawn Bishop kNight Rook Queen King ; lower for black ; */
    /*upper case for white */

/** 
 *  @fn void initBoardToStartPos(char *board)
 *  @brief Place pieces in the starting position
 *  @param[in,out] char pointer, the board
 *
 *  Starting from a8 to h1 
 */

void initBoardToStartPos(char *board) {
  int i;
  for (i=0 ; i <= (NBCASES-1) ; ++i) { 
    switch (color[i]) {
      case WHITE:
        board[i] = pieceChar[piece[i]];
        break;
      case BLACK:
        board[i] = pieceChar[piece[i]+6];
        break;
      case EMPTY:
        board[i] = ' ';
        break;
    }
  }
}

/** 
 *  @fn void printBoard(char *board)
 *  @brief Print the array in a formated way
 *  @param[in] char pointer, the board
 *
 * This way for the starting position :
 *
 *
 *
 *|r|n|b|q|k|b|n|r|
 *|p|p|p|p|p|p|p|p|
 *| | | | | | | | |
 *| | | | | | | | |
 *| | | | | | | | |
 *| | | | | | | | |
 *|P|P|P|P|P|P|P|P|
 *|R|N|B|Q|K|B|N|R|
 */

void printBoard(char *board) {
  int i;
  for (i=0 ; i <= (NBCASES-1) ; ++i) {
    printf("|%c", board[i]);
    if ((i+1)%8 == 0) {
      printf("|\n");
    }
  }
}
/** 
 *  @fn void fenToBoard(char *board, char *fenString)
 *  @brief Place pieces in a given position
 *  @param[in] A FEN string (char *)
 *  @param[in,out] char pointer, the board
 *
 *  FEN strings are describing position from a8...
 *  (b8... h8... a7...) ... h1 ans SO IS OUR BOARD 
 *  More details in the code
 */
void fenToBoard(char *board, char *fenString) {
  int i = 0;
  int j = 0; 
  int k;
  while (fenString[i] != ' ') {
  /* While we're readind the field that interests us */
    if (fenString[i] == '/') {
    /* Means we're changing rank (8->7 or 5->4 etc.) */
      ++i;
    } else {
      if (isalpha(fenString[i])) {
      /* Is it a character from ctype.h library ? */
        board[j] = fenString[i];
        ++j;
      } else {
      /* If we're considering a number in the */
      /*fen string it means the number of */
      /*empty case(s) in the rank so we need to put this in our board */
        for (k=1 ; k <= atoi(&fenString[i]) ; ++k) {
          board[j] = ' ';
          ++j;
        }
      }
      ++i;
      }
  }
}
