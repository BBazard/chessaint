/*This file is part of the ChessAInt project 2015*/
/**
 *  @file
 *
 *  This files implements chessboard handling functions
 *  or placing pieces in a given position
 */

#include "include/chessboard.h"

/**
 * @todo need to init in a function
 */

Color colorToInit[ROWCOL_NB][ROWCOL_NB] = {
  {white, white, white, white, white, white, white, white},
  {white, white, white, white, white, white, white, white},
  {neutral, neutral, neutral, neutral, neutral, neutral, neutral, neutral},
  {neutral, neutral, neutral, neutral, neutral, neutral, neutral, neutral},
  {neutral, neutral, neutral, neutral, neutral, neutral, neutral, neutral},
  {neutral, neutral, neutral, neutral, neutral, neutral, neutral, neutral},
  {black, black, black, black, black, black, black, black},
  {black, black, black, black, black, black, black, black},
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
  for (int i = 0; i < ROWCOL_NB; i++) {
    for (int j = 0; j < ROWCOL_NB; j++) {
      game->square[i][j].color = colorToInit[j][i];
      game->square[i][j].piece = piecesToInit[j][i];
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
 *  @bug : i think the bug is : if no square en passant, the end of the
 *    string is badly parsed. I'll check that -hugo
 *
 *  Parsing function
 */
void fenToBoard(char *fen, Board *game) {
  for (int i = 0; i < 4; ++i) {
    game->availableCastlings[i] = 0;
  }

  int idx = 0;
  int x = 0;
  int y = 7;
  int k = 0;

  while (fen[idx] != ' ') {
    if (fen[idx] == '/') {
      ++idx;
      --y;
      x = 0;
    } else {
      if (isalpha(fen[idx])) {
        if (islower(fen[idx]))
          game->square[x][y].color = black;
        else
          game->square[x][y].color = white;

        game->square[x][y].piece = charToPiece(fen[idx]);

      ++x;
      } else {
        for (int i = 0; i < atoi(&fen[idx]); ++i) {
          game->square[x][y].piece = empty;
          game->square[x][y].color = neutral;
          ++x;
        }
      }
      ++idx;
    }
  }

  ++idx; /* let's go to the next field */

  while (fen[idx] != ' ') {
    if (fen[idx] == 'w') {
      game->activeColor = white;
    } else {
      game->activeColor = black;
    }
    ++idx;
  }

  ++idx; /* To the next field of the fen string */

  while (fen[idx] != ' ') {
    if (fen[idx] == 'K') {
      game->availableCastlings[0] = 1;
    }
    if (fen[idx] == 'k') {
      game->availableCastlings[2] = 1;
    }
    if (fen[idx] == 'Q') {
      game->availableCastlings[1] = 1;
    }
    if (fen[idx] == 'q') {
      game->availableCastlings[3] = 1;
    }
    ++idx;
  }

  ++idx; /* To the next field of the fen string */

  while (fen[idx] != ' ') {
    if (fen[idx] == '-') {
      game->enPassant.column = -1;
      game->enPassant.line = -1;
      break;
    } else {
      game->enPassant.column = fen[idx] - 'a';
      ++idx;
      game->enPassant.line = atoi(&fen[idx]) - 1;
    }
    ++idx;
  }
  ++idx;
  k = 0;
  while (fen[idx+k] != ' ') {
    ++k;
  }
  char temp[256] = "";
  memcpy(temp, &fen[idx], k*sizeof(char));
  game->halfMoveClock = atoi(temp);

  idx += k;
  ++idx;
  k = 0;
  while (fen[idx+k] != '\0') {
    ++k;
  }
  memcpy(temp, &fen[idx], k*sizeof(char));
  game->fullMoveNb = atoi(temp);
}

/**
 *  @fn void printBoardAndData(Board game)
 *  @brief Print the board and game data in a formatted way
 *  @param[in] board game: the board (and its data of its structure) to display
 *  @note : Never forget that a1 <-> (0,0) so this printing is kinda flipped
 *  @bug : Previous note is FALSE actually it works only for a1, b2 etc since 
 *  board is symmetrized ( ie e2 is not (4,1), but (1,4) with current code)
 */
void printBoardAndData(Board game) {
  printf("\n\n");

  printf("8  ");
  for (int j = 7 ; j >= 0 ; --j) {
    printf("|");
    for (int i = 0 ; i < ROWCOL_NB ; ++i) {
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
    if (j != 0)
      printf("\n%d  ", j);
  }
  printf("\n");
  printf("    a b c d e f g h\n\n");

  /* Print the color array
  printf("8  ");
  for (j = 7 ; j >= 0 ; --j) {
    printf("|");
    for (i = 0 ; i <= (ROWCOL_NB - 1) ; ++i) {
      switch (game.square[i][j].color) {
        case white:
          printf("0");
          break;
        case black:
          printf("1");
          break;
        case neutral:
          printf("2");
          break;
      }
      printf("|");
    }
    if (j != 0)
      printf("\n%d  ", i);
  }
  printf("\n");
  printf("    a b c d e f g h\n\n"); 
  */ 
  /* Print the coords array 
  printf("8  ");
  for (i = 0 ; i <= (ROWCOL_NB - 1) ; ++i) {
    printf("|");
    for (j = 0 ; j <= (ROWCOL_NB - 1) ; ++j) {
      printf("(%d,%d)",7 - i,j );
      printf("|");
    }
    if (i != 7)
      printf("\n%d  ", 7 - i);
  }
  printf("\n");
  printf("    a b c d e f g h\n\n"); */

  /* Text data */

  if (game.activeColor == white)
    printf("Next color to play : white\n");
  else
    printf("Next Color to play : black\n");

  if (game.availableCastlings[0] == 1)
    printf("White can castle on the king side\n");
  if (game.availableCastlings[1] == 1)
    printf("White can castle on the queen side\n");
  if (game.availableCastlings[2] == 1)
    printf("Black can castle on the king side\n");
  if (game.availableCastlings[3] == 1)
    printf("Black can castle on the queen side\n");

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

enum Piece charToPiece(char c) {
  c = toupper(c);
  if (c == 'P')
    return pawn;
  if (c == 'B')
    return bishop;
  if (c == 'N')
    return knight;
  if (c == 'R')
    return rook;
  if (c == 'Q')
    return queen;
  if (c ==  'K')
    return king;
  return empty;
}

