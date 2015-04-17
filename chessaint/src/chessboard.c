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


/**
 * @todo need to init in a function
 */

Color colorToInit[ROWCOL_NB][ROWCOL_NB] = {
  {black, black, black, black, black, black, black, black},
  {black, black, black, black, black, black, black, black},
  {neutral, neutral, neutral, neutral, neutral, neutral, neutral, neutral},
  {neutral, neutral, neutral, neutral, neutral, neutral, neutral, neutral},
  {neutral, neutral, neutral, neutral, neutral, neutral, neutral, neutral},
  {neutral, neutral, neutral, neutral, neutral, neutral, neutral, neutral},
  {white, white, white, white, white, white, white, white},
  {white, white, white, white, white, white, white, white},
};

Piece piecesToInit[ROWCOL_NB][ROWCOL_NB] = {
  {rook, knight, bishop, queen, king, bishop, knight, rook},
  {pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn},
  {empty, empty, empty, empty, empty, empty, empty, empty},
  {empty, empty, empty, empty, empty, empty, empty, empty},
  {empty, empty, empty, empty, empty, empty, empty, empty},
  {empty, empty, empty, empty, empty, empty, empty, empty},
  {pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn},
  {rook, knight, bishop, queen, king, bishop, knight, rook},
};

/**
 *  @fn void initAGame(Board *game)
 *  @brief Put a board to the initial position
 *  @param[in,out] Board pointer on the board to initialize
 */

void initAGame(Board *game) {
  int i, j;

  for (i = 0 ; i <= ROWCOL_NB - 1 ; ++i) {
    for (j = 0; j <= ROWCOL_NB - 1 ; ++j) {
      game->square[i][j].color = colorToInit[i][j];
      game->square[i][j].piece = piecesToInit[i][j];
    }
  }
  game->activeColor = white;
  game->availableCastlings[0] = 1;
  game->availableCastlings[1] = 1;
  game->availableCastlings[2] = 1;
  game->availableCastlings[3] = 1;
  game->enPassant.column = -1;
  game->enPassant.line = -1;
  game->halfMoveClock = 0;
  game->fullMoveNb = 1;
}


/**
 *  @fn void fenToBoard(char *fen, Board *game)
 *  @brief Put a board to the position described by the FEN string
 *  @param[in] char *fen : the fen string
 *  @param[in,out] Board *game: the board to put in a certain position
 *
 *  @bug : i think the bug is : if no sqaure en passant, the end of the
 *    string is badly parsed. I'll check that -hugo
 *
 *  Parsing function
 */


void fenToBoard(char *fen, Board *game) {
  int i = 0;
  int j = 0;
  int k = 0;
  int m = 0;
  char temp[3];
  for (i = 0; i< 4; i++)
    game->availableCastlings[i] = 0;

  while (fen[i] != ' ') {
    if (fen[i] == '/') {
      ++i;
      ++m;
      j = 0;
    } else {
      if (isalpha(fen[i])) {
        switch (fen[i]) {
          case 'P':
            game->square[m][j].color = white;
            game->square[m][j].piece = pawn;
            break;
          case 'p':
            game->square[m][j].color = black;
            game->square[m][j].piece = pawn;
            break;
          case 'B':
            game->square[m][j].color = white;
            game->square[m][j].piece = bishop;
            break;
          case 'b':
            game->square[m][j].color = black;
            game->square[m][j].piece = bishop;
            break;
          case 'N':
            game->square[m][j].color = white;
            game->square[m][j].piece = knight;
            break;
          case 'n':
            game->square[m][j].color = black;
            game->square[m][j].piece = knight;
            break;
          case 'R':
            game->square[m][j].color = white;
            game->square[m][j].piece = rook;
            break;
          case 'r':
            game->square[m][j].color = black;
            game->square[m][j].piece = rook;
            break;
          case 'Q':
            game->square[m][j].color = white;
            game->square[m][j].piece = queen;
            break;
          case 'q':
            game->square[m][j].color = black;
            game->square[m][j].piece = queen;
            break;
          case 'K':
            game->square[m][j].color = white;
            game->square[m][j].piece = king;
            break;
          case 'k':
            game->square[m][j].color = black;
            game->square[m][j].piece = king;
            break;
        }
      ++j;
      } else {
        for (k=1 ; k <= atoi(&fen[i]) ; ++k) {
          game->square[m][j].piece = empty;
          game->square[m][j].color = neutral;
          ++j;
        }
      }
      ++i;
    }
  }

  ++i; /* let's go to the next field */

  while (fen[i] != ' ') {
    if (fen[i] == 'w') {
      game->activeColor = white;
    } else {
      game->activeColor = black;
    }
    ++i;
  }

  ++i; /* To the next field of the fen string */

  while (fen[i] != ' ') {
    if (fen[i] == 'K') 
      game->availableCastlings[0] = 1;
    else if (fen[i] == 'k') 
      game->availableCastlings[2] = 1;
    else if (fen[i] == 'Q') 
      game->availableCastlings[1] = 1;
    else if (fen[i] == 'q') 
      game->availableCastlings[3] = 1;
    i++;
  }

  ++i; /* To the next field of the fen string */

  while (fen[i] != ' ') {
    if (fen[i] == '-') {
      game->enPassant.column = -1;
      game->enPassant.line = -1;
      break;
    } else {
        switch (fen[i]) {
          case 'a':
            game->enPassant.column = 0;
            break;
          case 'b':
            game->enPassant.column = 1;
            break;
          case 'c':
            game->enPassant.column = 2;
            break;
          case 'd':
            game->enPassant.column = 3;
            break;
          case 'e':
            game->enPassant.column = 4;
            break;
          case 'f':
            game->enPassant.column = 5;
            break;
          case 'g':
            game->enPassant.column = 6;
            break;
          case 'h':
            game->enPassant.column = 7;
            break;
        }
      ++i;
      game->enPassant.line = atoi(&fen[i]) - 1;
    }
    ++i;
  }
  ++i;
  k = 0;
  while (fen[i+k] != ' ') {
    ++k;
  }
  memcpy(temp, &fen[i], k);
  game->halfMoveClock = atoi(temp);

  i += k;
  ++i;
  k = 0;
  while (fen[i+k] != '\0') {
    ++k;
  }
  memcpy(temp, &fen[i], k);
  game->fullMoveNb = atoi(temp);
}


/**
 *  @fn void printBoardAndData(Board game)
 *  @brief Print the board and game data in a formatted way
 *  @param[in] baord game: the board (and its data of its structure) to display
 */



void printBoardAndData(Board game) {
  int i, j;
  printf("\n\n");

  printf("8  ");
  for (i = 0 ; i <= (ROWCOL_NB - 1) ; ++i) {
    printf("|");
    for (j = 0 ; j <= (ROWCOL_NB - 1) ; ++j) {
      switch (game.square[i][j].piece) {
        case empty:
          printf(" ");
          break;
        case pawn:
          if (game.square[i][j].color == white)
            printf("P");
          else
            printf("p");
          break;
        case bishop:
          if (game.square[i][j].color == white)
            printf("B");
          else
            printf("b");
          break;
        case knight:
          if (game.square[i][j].color == white)
            printf("N");
          else
            printf("n");
          break;
        case rook:
          if (game.square[i][j].color == white)
            printf("R");
          else
            printf("r");
          break;
        case queen:
          if (game.square[i][j].color == white)
            printf("Q");
          else
            printf("q");
          break;
        case king:
          if (game.square[i][j].color == white)
            printf("K");
          else
            printf("k");
          break;
      }
      printf("|");
    }
    if (i != 7)
      printf("\n%d  ", 7 - i);
  }
  printf("\n");
  printf("    a b c d e f g h\n\n");

  if (game.activeColor == white)
    printf("Next color to play : white\n");
  else
    printf("Next Color to play : black\n");

  for (i = 0 ; i <= 3 ; ++i) {
    if (game.availableCastlings[i] != 0) {
      if (game.availableCastlings[i] == 1)
        printf("White can castle on the king side\n");
      if (game.availableCastlings[i] == 1)
        printf("Black can castle on the king side\n");
      if (game.availableCastlings[i] == 1)
        printf("White can castle on the queen side\n");
      if (game.availableCastlings[i] == 1)
        printf("Black can castle on the queen side\n");
    }
  }

  if (game.enPassant.column != -1) {
    printf("Square we can reach \"en passant\" : %d%d\n",
      game.enPassant.column, game.enPassant.line);
  } else {
    printf("No square to reach \" en passant\" \n");
  }

  printf("Number of plies since last capture or pawn move : %d\n",
    game.halfMoveClock);
  printf("Number of total moves (starting from 1) : %d\n",
    game.fullMoveNb);
}
