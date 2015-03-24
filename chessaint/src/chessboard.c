/*This file is part of the ChessAInt project 2015*/
/** 
 *  @file chessboard.c
 *  @brief chessboard handling functions
 *
 *  This files implements chessboard handling functions 
 *  or placing pieces in a given position
 *
 */

#include "include/chessboard.h"


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
        printf("%d  ", 8-i/8-1);
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
        printf("%d  ", 8-i/8-1);
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
        printf("%d  ", 8-i/8-1);
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
  snprintf(move, sizeof(move), "0000");

  char activeColor;
  activeColor = 'w';

  Llist movesList = NULL;
  Arc amove;

  printf("\n\n");
  printf("Human v Human game !\n");
  printf("To move a piece write starting position");
  printf("and ending position ex : e2e4 \n");
  /* beacause first only Algebraic notation is implemented */
  printf("At any moment you can go back to main menu by typing exit \n");
  initBoardToStartPos(boardChar, boardPiece, boardColor);
  printBoard(boardChar, boardPiece, boardColor);

  while (strcmp(move, "exit") != 0) {
    printf("Your move : ");
    scanf("%s", move);
    if ((activeColor == 'w') && isAWhiteLegalMove(move)) {
      amove = getArcFromMove(move, 'w', nbMoves);
      llist_add(amove, &movesList);
      moveBoard(move, boardChar, boardPiece, boardColor);
      activeColor = 'b';
      ++nbMoves;

      printBoard(boardChar, boardPiece, boardColor);
      llist_print(movesList);
    } else {
        if (isABlackLegalMove(move) && activeColor == 'b') {
          amove = getArcFromMove(move, 'b', nbMoves);
          llist_add(amove, &movesList);
          moveBoard(move, boardChar, boardPiece, boardColor);
          activeColor = 'w';
          ++nbMoves;

          printBoard(boardChar, boardPiece, boardColor);
          llist_print(movesList);
        } else {
          printf("ILLEGAL MOVE\n");
        }
    }
  }
  if (strcmp(move, "exit") == 0) {
    while (movesList != NULL) {
      llist_suppr(&movesList);
    }
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
  /*We need to transform "d2" or "a3"... */
  /*into the corresponding cases in the board*/
  char fromC[3];
  char toC[3];
  memcpy(fromC, &move[0], 2);
  fromC[2] = '\0';
  memcpy(toC, &move[2], 2);
  toC[2]='\0';
  int from, to;
  from = lettersCoordToNumberCoord(fromC);
  to = lettersCoordToNumberCoord(toC);

  /*Actually moves boards to play*/
  board[to] = board[from];
  board[from] = ' ';
  color[to] = color[from];
  color[from] = 9;
  piece[to] = piece[from];
  piece[from] = 9;
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

void numberCoordToLettersCoord(int number, char result[2]) {
  printf("mod 8 %d\n", number % 8);
  printf("/ 8 %d\n", number / 8);
  snprintf(result, sizeof(result), "00");
  switch (number % 8) {
    case 0:
      result[0] = 'a';
      break;
    case 1:
      result[0] = 'b';
      break;
    case 2:
      result[0] = 'c';
      break;
    case 3:
      result[0] = 'd';
      break;
    case 4:
      result[0] = 'e';
      break;
    case 5:
      result[0] = 'f';
      break;
    case 6:
      result[0] = 'g';
      break;
    case 7:
      result[0] = 'h';
      break;
  }
  switch (number / 8) {
    case 0:
      result[0] = '8';
      break;
    case 1:
      result[0] = '7';
      break;
    case 2:
      result[0] = '6';
      break;
    case 3:
      result[0] = '5';
      break;
    case 4:
      result[0] = '4';
      break;
    case 5:
      result[0] = '3';
      break;
    case 6:
      result[0] = '2';
      break;
    case 7:
      result[0] = '1';
      break;
  }
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
  bool answer;
  /*We need to transform "d2" or "a3"...*/
  /* into the corresponding cases in the boardS*/
  char fromC[3];
  char toC[3];
  memcpy(fromC, &move[0], 2);
  fromC[2] = '\0';
  memcpy(toC, &move[2], 2);
  int from, to;
  from = lettersCoordToNumberCoord(fromC);
  to = lettersCoordToNumberCoord(toC);

  char activeColor = 'w';
  if (boardColor[to] == 1) { /*You can't move on one of your pieces*/
    return false;
  }

  if (boardColor[from] == 1) { /* First you need to grab one of your pieces...*/
    switch (boardPiece[from]) {
      case 0: /* If you grab a pawn */
        if (isAPawnLegalMove(move, activeColor)) {
          answer = true;
        } else {
          answer = false;
        }
        break;
      case 1:
        if (isABishopLegalMove(move, activeColor)) {
          answer = true;
        } else {
          answer = false;
        }
        break;
      case 2:
          answer = true;
        break;
      case 3:
        if (isARookLegalMove(move, activeColor)) {
          answer = true;
        } else {
          answer = false;
        }
        break;
      case 4:
        if (isARookLegalMove(move, activeColor) ||
          isABishopLegalMove(move, activeColor)) {
          answer = true;
        } else {
          answer = false;
        }
        break;
      case 5:
          answer = true;
        break;
    }
  } else {
    answer = false;
  }

  return answer;
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
  bool answer;
  /*We need to transform "d2" or "a3"...*/
  /*into the corresponding cases in the boardS*/
  char fromC[3];
  char toC[3];
  memcpy(fromC, &move[0], 2);
  fromC[2] = '\0';
  memcpy(toC, &move[2], 2);
  int from, to;
  from = lettersCoordToNumberCoord(fromC);
  to = lettersCoordToNumberCoord(toC);

  char activeColor = 'b';
  if (boardColor[to] == 2) { /*You can't move on one of your pieces*/
    return false;
  }

  if (boardColor[from] == 2) { /* First you need to grab one of your pieces...*/
    switch (boardPiece[from]) {
      case 0: /* If you grab a pawn */
        if (isAPawnLegalMove(move, activeColor)) {
          answer = true;
        } else {
          answer = false;
        }
        break;
      case 1:
        if (isABishopLegalMove(move, activeColor)) {
          answer = true;
        } else {
          answer = false;
        }
        break;
      case 2:
          answer = true;
        break;
      case 3:
        if (isARookLegalMove(move, activeColor)) {
          answer = true;
        } else {
          answer = false;
        }
        break;
      case 4:
        if (isARookLegalMove(move, activeColor) ||
          isABishopLegalMove(move, activeColor)) {
          answer = true;
        } else {
          answer = false;
        }
        break;
      case 5:
          answer = true;
        break;
    }
  } else {
    answer = false;
  }

  return answer;
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
  memcpy(arc.from, &move[0], 2);
  arc.from[2] = '\0';
  memcpy(arc.to, &move[2], 2);
  arc.to[2] = '\0';
  arc.score = 0; /*Useless noAI yet */
  arc.whichSet = none; /*useless no AI*/
  arc.activeColor = whoPlayed;
  arc.castlingAvailability = "xx"; /*Not suppoorted yet */
  arc.enPassant = "xx"; /*Not supported yet*/
  arc.halfmoveClock = 0; /*Not supported yet*/
  arc.fullmoveNumber = nbMoves;

  return arc;
}

bool isAPawnLegalMove(char *move, char activeColor) {
  bool answer = false;  /*if none of foolowing cases matches return false*/
  char fromC[3];
  char toC[3];
  memcpy(fromC, &move[0], 2);
  fromC[2] = '\0';
  memcpy(toC, &move[2], 2);
  int from, to;
  from = lettersCoordToNumberCoord(fromC);
  to = lettersCoordToNumberCoord(toC);


  if (activeColor == 'w') { /*if it's a white pawn*/
    if (move[0] == move[2]) { /*if we stay on the same column*/
      if ((move[1] == '2') && (move[3] == '4')) {
      /*if we do this double first move*/
        if ((boardPiece[to] == 9) && (boardPiece[to+8] == 9)) {
        /*if the 2 squares ahead are empty*/
          answer = true;
        }
      } else {
        if (from == to+8) { /*If we're really going only one square forward*/
          if (boardPiece[to] == 9) { /*If the square desired is empty*/
            answer = true;
          }
        }
      }
    } else { /*if we change column with our pawn*/
      if ((from == to+7) || (from == to+9)) {
      /*if we correctly going forward in case we change colmun*/
        if (((move[0] == 'a') && (move[2] == 'b'))
          || ((move[0] == 'h') && (move[2] == 'g'))
          || ((move[0] == move[2]+1) || (move[0] == move[2]-1))) {
        /*if we are correctly changing column (extreme cases and other)*/
        /* we're doing some casts here*/
          if (boardColor[to] == 2) {
          /* yeah only if we're killing an opposite piece OR EN PASSANT*/
          /* (to be implemented HERE) */
            answer = true;
          }
        }
      } else { /*all other cases are false*/
        answer = false;
      }
    }
  } else { /*if a black pawn wanna move */
      if (move[0] == move[2]) { /*if we stay on the same column*/
        if ((move[1] == '7') && (move[3] == '5')) {
        /*if we do this double first move*/
          if ((boardPiece[to] == 9) && (boardPiece[to-8] == 9)) {
          /*if the 2 squares ahead are empty*/
            answer = true;
          }
        } else {
          if (from == to-8) { /*If we're really going only one square forward*/
            if (boardPiece[to] == 9) { /*If the square desired is empty*/
              answer = true;
            }
          }
        }
      } else { /*if we change column with our pawn*/
        if ((from == to-7) || (from == to-9)) {
        /*if we correctly going forward*/
          if (((move[0] == 'a') && (move[2] == 'b'))
            || ((move[0] == 'h') && (move[2] == 'g'))
            || ((move[0] == move[2]+1) || (move[0] == move[2]-1))) {
          /*if we are correctly changing column (extreme cases and other)*/
          /* we're doing some casts here*/
            if (boardColor[to] == 1) { /* yeah only if we're killing an */
            /*opposite piece OR EN PASSANT (to be implemented HERE) */
              answer = true;
            }
          }
        } else { /*all other cases are false*/
          answer = false;
        }
      }
  }

  return answer;
}

bool isABishopLegalMove(char *move, char activeColor) {
  bool answer = false; /*if none of foolowing cases matches return false*/

  char fromC[3];
  memcpy(fromC, &move[0], 2);
  fromC[2] = '\0';
  int from;
  from = lettersCoordToNumberCoord(fromC);

  int i;
  int diffColumns = move[0]-move[2];
  int diffLines = atoi(&move[1])-atoi(&move[3]);

  int ennemyNb, allyNb;
  if (activeColor == 'w') {
    ennemyNb = 2;
    allyNb = 1;
  } else {
    ennemyNb = 1;
    allyNb = 2;
  }

  if ((diffColumns > 0) && (diffLines < 0)) { /*if we wanna go to North-West */
    if ((boardColor[from-8*diffColumns-diffColumns] == 9) /*=boardColor[to]*/
      || (boardColor[from-8*diffColumns-diffColumns] == ennemyNb)) {
      answer = true;
    } /*Normalement on peut y aller sauf si ça contredit sur le chemin du for*/
    for (i = 1 ; i <= diffColumns ; ++i) {
      if ((boardColor[from-8*i-i] == allyNb)
        || (boardColor[from-8*i-i] == ennemyNb)) {
        answer = false;
        break;
      }
    }
  }
  if ((diffColumns < 0) && (diffLines < 0)) { /*if we wanna go to North-East */
    diffColumns = -diffColumns; /*get something positive */
    if ((boardColor[from-8*diffColumns+diffColumns] == 9)
      || (boardColor[from-8*diffColumns+diffColumns] == ennemyNb)) {
      answer = true;
    }
    for (i = 1 ; i <= diffColumns ; ++i) {
      if ((boardColor[from-8*i+i] == allyNb)
        || (boardColor[from-8*i+i] == ennemyNb)) {
        answer = false;
        break;
      }
    }
  }
  if ((diffColumns < 0) && (diffLines > 0)) { /*if we wanna go to South-East */
    diffColumns = -diffColumns; /*get something positive */
    if ((boardColor[from+8*diffColumns+diffColumns] == 9)
      || (boardColor[from+8*diffColumns+diffColumns] == ennemyNb)) {
      answer = true;
    }
    for (i = 1 ; i <= diffColumns ; ++i) {
      if ((boardColor[from+8*i+i] == allyNb)
        || (boardColor[from+8*i+i] == ennemyNb)) {
        answer = false;
        break;
      }
    }
  }
  if ((diffColumns > 0) && (diffLines > 0)) { /*if we wanna go to South-West */
    if ((boardColor[from+8*diffColumns-diffColumns] == 9)
      || (boardColor[from+8*diffColumns-diffColumns] == ennemyNb)) {
      answer = true;
    }
    for (i = 1 ; i <= diffColumns ; ++i) {
      if ((boardColor[from+8*i-i] == allyNb)
        || (boardColor[from+8*i-i] == ennemyNb)) {
        answer = false;
        break;
      }
    }
  }

  return answer;
}

bool isARookLegalMove(char *move, char activeColor) {
  bool answer = false;  /*if none of foolowing cases matches return false*/
  char fromC[3];
  char toC[3];
  memcpy(fromC, &move[0], 2);
  fromC[2] = '\0';
  memcpy(toC, &move[2], 2);
  int from, to;
  from = lettersCoordToNumberCoord(fromC);
  to = lettersCoordToNumberCoord(toC);

  int i;

  int diffColumns = move[0]-move[2];
  int diffLines = atoi(&move[1])-atoi(&move[3]);

  int ennemyNb, allyNb;
  if (activeColor == 'w') {
    ennemyNb = 2;
    allyNb = 1;
  } else {
    ennemyNb = 1;
    allyNb = 2;
  }

  if (move[1] == move[3]) { /*if were moving on a line...*/
    if (diffColumns > 0) { /*... and to the left*/
      if ((boardColor[to] == 9) || boardColor[to] == ennemyNb) {
        answer = true;
      }
      /* So it should be true except if we find womething anormal on our road*/
      for (i = 1 ; i <= diffColumns ; ++i) {
        if ((boardColor[from-i] == ennemyNb)
          || (boardColor[from-i] == allyNb)) {
          answer = false;
          break;
        }
      }
    } else { /*if were going to the right*/
      diffColumns = -diffColumns;
      if ((boardColor[to] == 9) || boardColor[to] == ennemyNb) {
        answer = true;
      }
      /* So it should be true except if we find womething anormal on our road*/
      for (i = 1 ; i <= diffColumns ; ++i) {
        if ((boardColor[from+i] == ennemyNb) ||
          (boardColor[from+i] == allyNb)) {
          answer = false;
          break;
        }
      }
    }
  }
  if (move[0] == move[2]) { /*if were moving on a column...*/
    if (diffLines > 0) { /*... and down*/
      if ((boardColor[to] == 9) ||
        boardColor[to] == ennemyNb) {
        answer = true;
      }
      /* So it should be true except if we find womething anormal on our road*/
      for (i = 1 ; i <= diffLines ; ++i) {
        if ((boardColor[from+8*i] == ennemyNb) ||
          (boardColor[from+8*i] == allyNb)) {
          answer = false;
          break;
        }
      }
    } else { /*if were going up*/
      diffLines = -diffLines;
      if ((boardColor[to] == 9) || boardColor[to] == ennemyNb) {
        answer = true;
      }
      /* So it should be true except if we find womething anormal on our road*/
      for (i = 1 ; i <= diffLines ; ++i) {
        if ((boardColor[from-8*i] == ennemyNb) ||
          (boardColor[from-8*i] == allyNb)) {
          answer = false;
          break;
        }
      }
    }
  }

  return answer;
}
