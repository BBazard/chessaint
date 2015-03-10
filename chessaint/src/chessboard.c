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
#include <string.h>
#include <regex.h>
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
 *8  |r|n|b|q|k|b|n|r|
 *7  |p|p|p|p|p|p|p|p|
 *6  | | | | | | | | |
 *5  | | | | | | | | |
 *4  | | | | | | | | |
 *3  | | | | | | | | |
 *2  |P|P|P|P|P|P|P|P|
 *1  |R|N|B|Q|K|B|N|R|
 *
 *  a b c d e f g h
 *
 */

void printBoard(char *board) {
  int i;
  printf("\n\n");

  printf("8  ");
  for (i=0 ; i <= (NBCASES-1) ; ++i) {
    printf("|%c", board[i]);
    if ((i+1)%8 == 0) {
      printf("|\n");
      if (i != 63)
        printf("%d  ",8-i/8-1);
    }
  }
  printf("\n");
  printf("    a b c d e f g h\n");

  printf("\n\n");
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
/** 
 *  @fn void humanVHuman()
 *  @brief it's a human v human game
 *
 *  Currently it only moves pieces without restrictions until "exit"
 *  (you can totally do invalid moves)
 *  LATER THIS FUNCTION WILL CALL ANY FUNCTIONS IT NEEDS TO PLAY A TRUE GAME
 *  (ex : check valid moves, check check position etc.)
 *  IT AIMS ALSO TO USE GRAPH DATA STRUCTURES (without AI for sure)  
 */

void humanVHuman() {
  char move[4]; /* move OR exit*/
  strcpy(move, "0000");
  printf("\n\n");
  printf("Human v Human game !\n");
  printf("To move a piece write starting position and ending position ex : e2e4 \n");
  /* beacause first only Algebraic notation is implemented */
  printf("At any moment you can go back to main menu by typing exit \n");
  initBoardToStartPos(board);
  printBoard(board);

  while (strcmp(move,"exit") != 0) {
    scanf("%s",&move);
    moveBoard(move, board);
    printBoard(board);
  }
}

/** 
 *  @fn void moveBoard(char *move, char *board)
 *  @brief moves a piece on the board
 *  @param[in,out] string : the move, the board
 *   
 *  Its current mission is to tranlate a string into a move
 *  and to play it. This function will not check the accuracy of a move
 */

void moveBoard(char *move, char *board) {
  int from,to;
  /*We need to transform "d2" or "a3"... into the corresponding cases in the board*/
  switch (move[1]) {
    case '1':
      from = 56;
      break;
    case '2':
      from = 48;
      break;
    case '3':
      from = 40;
      break;
    case '4':
      from = 32;
      break;
    case '5':
      from = 24;
      break;
    case '6':
      from = 16;
      break;
    case '7':
      from = 8;
      break;
    case '8':
      from = 0;
      break;
  }
  switch (move[0]) {
    case 'a':
      from += 0;
      break;
    case 'b':
      from += 1;
      break;
    case 'c':
      from += 2;
      break;
    case 'd':
      from += 3;
      break;
    case 'e':
      from += 4;
      break;
    case 'f':
      from += 5;
      break;
    case 'g':
      from += 6;
      break;
    case 'h':
      from += 7;
      break;    
  }
  switch (move[3]) {
    case '1':
      to = 56;
      break;
    case '2':
      to = 48;
      break;
    case '3':
      to = 40;
      break;
    case '4':
      to = 32;
      break;
    case '5':
      to = 24;
      break;
    case '6':
      to = 16;
      break;
    case '7':
      to = 8;
      break;
    case '8':
      to = 0;
      break;
  }
  switch (move[2]) {
    case 'a':
      to += 0;
      break;
    case 'b':
      to += 1;
      break;
    case 'c':
      to += 2;
      break;
    case 'd':
      to += 3;
      break;
    case 'e':
      to += 4;
      break;
    case 'f':
      to += 5;
      break;
    case 'g':
      to += 6;
      break;
    case 'h':
      to += 7;
      break;    
  }
  board[to]=board[from];
  board[from]=' ';

}