/*This file is part of the ChessAInt project 2015*/
/**
 *  @file
 *
 *  This files implements chessboard handling functions
 *  or placing pieces in a given position
 */

#include "include/chessboard.h"
#include <assert.h>

/**
 *  The variable to init color in initAGame function
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

/**
 *  The variable to init pieces in initAGame function
 */
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
 *  @brief Put a board to the initial position
 *  @param[in,out] game pointer on the board to initialize
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
 *  @brief Put a board to the position described by the FEN string
 *  @param[in] fen The fen string
 *  @param[in,out] game The board to put in a certain position
 *
 *  @bug : I think the bug is : if no square en passant, the end of the
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
 *  @brief Print the board and game data in a formatted way
 *  @param[in] game: the board (and its data of its structure) to display
 *  @note Never forget that a1 <-> (0,0) so this printing is kinda flipped
 *  @bug Previous note is FALSE actually it works only for a1, b2 etc since 
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

/**
 *  @brief Change a char in a piece
 *  @param[in] c The char to transform
 *  @return piece
 */
Piece charToPiece(char c) {
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

/**
 *  @brief Get the opponent color
 *  @param[in] color The color given
 *  @return The opponent color
 */
Color getOtherColor(Color color) {
  if (color == white)
    return black;
  if (color == black)
    return white;

  return neutral;
}

/**
 *  @brief Test if the given square given with its coordinates is in the board
 *  @param[in] squareX
 *  @param[in] squareY are the coordinates of the square to test
 *  @return bool true if the square is in false otherwise.
 */
bool isInBoardSquare(int squareX, int squareY) {
  return (squareX >= 0) && (squareX <= 7) && (squareY >= 0) && (squareY <= 7);
}

/**
 *  @brief find the piece which cannot move
 *         because of pinnings :
 *         the piece cannot move without the king being mate
 *
 *  fill pinned array
 *
 *  @param board
 *  @param activeColor
 *  @param pinned
 *
 */
void findAllPinnings(Board *board, Color activeColor, bool pinned[8][8]) {
  for (int i = 0; i < ROWCOL_NB; ++i)
    for (int j = 0; j < ROWCOL_NB; ++j)
      pinned[i][j] = false;

  Color enemyColor = getOtherColor(activeColor);

  for (int i = 0 ; i < ROWCOL_NB ; ++i)
    for (int j = 0 ; j < ROWCOL_NB ; ++j)
      if (board->square[i][j].color == enemyColor) {
        switch (board->square[i][j].piece) {
        case bishop:
          findBishopPinnings(board, enemyColor, pinned, i, j);
          break;
        case rook:
          findRookPinnings(board, enemyColor, pinned, i, j);
          break;
        case queen:
          findBishopPinnings(board, enemyColor, pinned, i, j);
          findRookPinnings(board, enemyColor, pinned, i, j);
          break;
        default:  /* pawn, knight, king, empty */
          break;
        }
      }
}

/**
 *  @brief search for a piece of your color between a enemy
 *         piece and your king for a piece
 *  
 *  @param board The board on which to compute
 *  @param enemyColor The color of threatening pieces
 *  @param pinned The bool matrix in which are given results
 *  @param X
 *  @param Y
 *  @param incX
 *  @param incY
 *
 */
void findLinePinnings(Board *board, Color enemyColor, bool pinned[8][8],
                      int X, int Y, int incX, int incY) {
  Color myColor = getOtherColor(enemyColor);
  Piece potentielPinned = empty;
  int potX = -1;
  int potY = -1;

  assert(board->square[X][Y].color == enemyColor);
  X += incX;
  Y += incY;

  while (isInBoardSquare(X, Y) && board->square[X][Y].color != enemyColor) {
    if (board->square[X][Y].color == myColor) {
      if (board->square[X][Y].piece != king) {
        /* when there is more than one piece    */
        /* between the king and the enemy piece */
        if (potentielPinned != empty)
          return;

        potentielPinned = board->square[X][Y].piece;
        potX = X;
        potY = Y;
      }
      if (board->square[X][Y].piece == king) {
        if (potentielPinned != empty)
          pinned[potX][potY] = true;
        return;
      }
    }
    X += incX;
    Y += incY;
  }
}
/**
 *  @brief Pinning for rooks
 *
 *  @param board
 *  @param enemyColor
 *  @param pinned
 *  @param X
 *  @param Y
 */
void findRookPinnings(Board *board, Color enemyColor,
                      bool pinned[8][8], int X, int Y) {
  findLinePinnings(board, enemyColor, pinned, X, Y, 1, 0);
  findLinePinnings(board, enemyColor, pinned, X, Y, 0, 1);
  findLinePinnings(board, enemyColor, pinned, X, Y, -1, 0);
  findLinePinnings(board, enemyColor, pinned, X, Y, 0, -1);
}
/**
 *  @brief Pinning for bishops
 *
 *  @param board
 *  @param enemyColor
 *  @param pinned
 *  @param X
 *  @param Y
 */
void findBishopPinnings(Board *board, Color enemyColor,
                        bool pinned[8][8], int X, int Y) {
  findLinePinnings(board, enemyColor, pinned, X, Y, -1, -1);
  findLinePinnings(board, enemyColor, pinned, X, Y, -1, +1);
  findLinePinnings(board, enemyColor, pinned, X, Y, +1, -1);
  findLinePinnings(board, enemyColor, pinned, X, Y, +1, +1);
}

