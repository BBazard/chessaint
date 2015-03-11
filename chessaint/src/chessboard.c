
/** 
 *  @file chessboard.c
 *  @brief chessboard handling functions
 *
 *  This files implements chessboard handling functions 
 *  or placing pieces in a given position
 *
 */

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
}; /*WHITE BLACK or EMPTY (see #define in .h)*/

int piece[NBCASES] = {
  3, 2, 1, 4, 5, 1, 2, 3,
  0, 0, 0, 0, 0, 0, 0, 0,
  9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9,
  9, 9, 9, 9, 9, 9, 9, 9,
  0, 0, 0, 0, 0, 0, 0, 0,
  3, 2, 1, 4, 5, 1, 2, 3
}; /*PAWN BISHOP KNIGHT ROOK QUEEN KING or EMPTY (see #define in .h)*/

char pieceChar[12] = {
  'P', 'B', 'N', 'R', 'Q', 'K', 'p', 'b', 'n', 'r', 'q', 'k'
}; /* Pawn Bishop kNight Rook Queen King ; lower for black ; */
    /*upper case for white */

/** 
 *  @fn void initBoardToStartPos(char *board, int *boardPiece, int *boardColor)
 *  @brief Place the 3 boards in starting position
 *  @param[in,out] char and int pointers : the boards
 *
 *  Starting from a8 to h1 
 */

void initBoardToStartPos(char *board, int *boardPiece, int *boardColor) {
  int i;
  for (i=0; i <= (NBCASES-1) ; i++) {
    boardPiece[i] = piece[i];
  }
  for (i=0; i <= (NBCASES-1) ; i++) {
    boardColor[i] = color[i];
  }
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
 *  @fn void printBoard(char *board, int *piece, int *color)
 *  @brief Print the arrays in a formated way
 *  @param[in] char and int pointers, the boards
 *
 */

void printBoard(char *board, int *piece, int *color) {
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
  printf("\n\n");

  printf("8  ");
  for (i=0 ; i <= (NBCASES-1) ; ++i) {
    printf("|%d", color[i]);
    if ((i+1)%8 == 0) {
      printf("|\n");
      if (i != 63)
        printf("%d  ",8-i/8-1);
    }
  }
  printf("\n");
  printf("    a b c d e f g h\n");

  printf("\n\n");
  printf("\n\n");

  printf("8  ");
  for (i=0 ; i <= (NBCASES-1) ; ++i) {
    printf("|%d", piece[i]);
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
 *
 * THIS function doesn't modify yet the 2 other important arrays 
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
 *  This function is getting more and more accurate 
 */

void humanVHuman() {
  int nbMoves = 0;

  char move[4]; /* move OR exit*/
  strcpy(move, "0000");

  char activeColor;
  activeColor = 'w';

  Llist movesList = NULL;
  Arc amove;

  printf("\n\n");
  printf("Human v Human game !\n");
  printf("To move a piece write starting position and ending position ex : e2e4 \n");
  /* beacause first only Algebraic notation is implemented */
  printf("At any moment you can go back to main menu by typing exit \n");
  initBoardToStartPos(boardChar, boardPiece, boardColor);
  printBoard(boardChar, boardPiece, boardColor);

  while (strcmp(move,"exit") != 0) {
    printf("Your move : ");
    scanf("%s",move);
    if ((activeColor == 'w' && isAWhiteLegalMove(move) )) { 
      amove = getArcFromMove(move,'w',nbMoves);
      llist_add(amove, &movesList);
      moveBoard(move, boardChar, boardPiece, boardColor);
      activeColor ='b';
      ++nbMoves;
    } else {
      if (isABlackLegalMove(move) && activeColor == 'b') {
        amove = getArcFromMove(move, 'b', nbMoves);
        llist_add(amove, &movesList);
        moveBoard(move, boardChar, boardPiece, boardColor);
        activeColor = 'w';
        ++nbMoves;
      } else {
        printf("ILLEGAL MOVE\n");
      }
    } 
    printBoard(boardChar, boardPiece, boardColor);
    llist_print(movesList);
  }
}

/** 
 *  @fn void moveBoard(char *move, char *board, int *piece, int *color)
 *  @brief moves a piece on the board
 *  @param[in,out] string : the move, the boards
 *   
 *  Its current mission is to tranlate a string into a move
 *  and to play it. On the 3 boards. This function will not check the accuracy of a move
 */

void moveBoard(char *move, char *board, int *piece, int *color) {
  /*We need to transform "d2" or "a3"... into the corresponding cases in the board*/
  char *fromC[3];
  char *toC[3];
  memcpy(fromC,&move[0],2);
  fromC[2]='\0';
  memcpy(toC,&move[2],2);
  toC[2]='\0';
  int from,to;
  from = lettersCoordToNumberCoord(fromC);
  to = lettersCoordToNumberCoord(toC);

  /*Actually moves boards to play*/
  board[to]=board[from];
  board[from]=' ';
  color[to]=color[from];
  color[from]=9;
  piece[to]=piece[from];
  piece[from]=9;
}
/** 
 *  @fn int lettersCoordToNumberCoord(char *square)
 *  @brief from "a8" gives 0, from "b8" gives 1 etc..
 *  @param[in] string : a square on the board (no verification yet)
 *  @param[out] int : the number matching with the square in our array representation 
 *
 */
int lettersCoordToNumberCoord(char *square) {
  int correspondingTableSlot;
  switch (square[1]) {
    case '1':
      correspondingTableSlot = 56;
      break;
    case '2':
      correspondingTableSlot = 48;
      break;
    case '3':
      correspondingTableSlot = 40;
      break;
    case '4':
      correspondingTableSlot = 32;
      break;
    case '5':
      correspondingTableSlot = 24;
      break;
    case '6':
      correspondingTableSlot = 16;
      break;
    case '7':
      correspondingTableSlot = 8;
      break;
    case '8':
      correspondingTableSlot = 0;
      break;
  }
  switch (square[0]) {
    case 'a':
      correspondingTableSlot += 0;
      break;
    case 'b':
      correspondingTableSlot += 1;
      break;
    case 'c':
      correspondingTableSlot += 2;
      break;
    case 'd':
      correspondingTableSlot += 3;
      break;
    case 'e':
      correspondingTableSlot += 4;
      break;
    case 'f':
      correspondingTableSlot += 5;
      break;
    case 'g':
      correspondingTableSlot += 6;
      break;
    case 'h':
      correspondingTableSlot += 7;
      break;    
  }
  return correspondingTableSlot;
}
/** 
 *  @fn bool isAWhiteLegalMove(char *move)
 *  @brief check for the validity of a move with the help of the 3 arrays
 *  @param[in] string : the move
 *  @param[out] bool : is this legal ?
 *
 *  THIS FUNCTION IS QUITE INCOMPLETE, it will change
 */
bool isAWhiteLegalMove(char *move) {
/*We need to transform "d2" or "a3"... into the corresponding cases in the boardS*/
  char *fromC[3];
  char *toC[3];
  memcpy(fromC,&move[0],2);
  fromC[2]='\0';
  memcpy(toC,&move[2],2);
  int from,to;
  from = lettersCoordToNumberCoord(fromC);
  to = lettersCoordToNumberCoord(toC);

  if (boardColor[from] == 1 && boardColor[to]==9) {
    return true;
  } else {
    return false;
  }
}
/** 
 *  @fn bool isABlackLegalMove(char *move)
 *  @brief check for the validity of a move with the help of the 3 arrays
 *  @param[in] string : the move
 *  @param[out] bool : is this legal ?
 *
 *  THIS FUNCTION IS QUITE INCOMPLETE, it will change
 */
bool isABlackLegalMove(char *move) {
/*We need to transform "d2" or "a3"... into the corresponding cases in the boardS*/
  char *fromC[3];
  char *toC[3];
  memcpy(fromC,&move[0],2);
  fromC[2]='\0';
  memcpy(toC,&move[2],2);
  int from,to;
  from = lettersCoordToNumberCoord(fromC);
  to = lettersCoordToNumberCoord(toC);

  if (boardColor[from] == 2 && boardColor[to]==9) {
    return true;
  } else {
    return false;
  }
}
/** 
 *  @fn Arc getArcFromMove(char *move, char whoPlayed, int nbMoves)
 *  @brief creates the arc corresponding to the human move
 *  @param[in,out] string : the move ; char who played ( 'b' or 'w') ; int number of moves so far
 * 
 * THIS FUNCTION IS INCOMPLETE (so basic)
 */
Arc getArcFromMove(char *move, char whoPlayed, int nbMoves) {
  Arc arc;
  arc.id = nbMoves; /*No originality*/
  memcpy(arc.from,&move[0],2);
  arc.from[2]='\0';
  memcpy(arc.to,&move[2],2);
  arc.to[2]='\0';
  arc.score = 0; /*Useless noAI yet */
  arc.whichSet=none; /*useless no AI*/
  arc.activeColor=whoPlayed;
  arc.castlingAvailability = "xx"; /*Not suppoorted yet */
  arc.enPassant = "xx"; /*Not supported yet*/
  arc.halfmoveClock = 0; /*Not supported yet*/
  arc.fullmoveNumber = nbMoves;

  return arc;
}
