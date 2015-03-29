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

Color colorToInit[NBSQUARES] = {
  black, black, black, black, black, black, black, black,
  black, black, black, black, black, black, black, black,
  neuter, neuter, neuter, neuter, neuter, neuter, neuter, neuter,
  neuter, neuter, neuter, neuter, neuter, neuter, neuter, neuter,
  neuter, neuter, neuter, neuter, neuter, neuter, neuter, neuter,
  neuter, neuter, neuter, neuter, neuter, neuter, neuter, neuter,
  white, white, white, white, white, white, white, white,
  white, white, white, white, white, white, white, white,
};

Piece piecesToInit[NBSQUARES] = {
  rook, knight, bishop, queen, king, bishop, knight, rook,
  pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn,
  empty, empty, empty, empty, empty, empty, empty, empty,
  empty, empty, empty, empty, empty, empty, empty, empty,
  empty, empty, empty, empty, empty, empty, empty, empty,
  empty, empty, empty, empty, empty, empty, empty, empty,
  pawn, pawn, pawn, pawn, pawn, pawn, pawn, pawn,
  rook, knight, bishop, queen, king, bishop, knight, rook,
};

void initAGame(Board *game) {
  int i;
  for (i = 0 ; i <= NBSQUARES - 1 ; ++i) {
    game->square[i].color = colorToInit[i];
    game->square[i].piece = piecesToInit[i];
  }
  game->activeColor = white;
  game->availableCastlings[0] = K;
  game->availableCastlings[1] = Q;
  game->availableCastlings[2] = k;
  game->availableCastlings[3] = q;
  game->enPassant.column = 'x';
  game->enPassant.line = 0;
  game->pliesSinceLastCaptureOrLastPawnMovement = 0;
  game->nbMovesTotal = 1;
}

/*With a game given, it will generate all next moves possible*/
char **moveGenerator(Board game) {
  int i = 0;
  char **listOfRawMoves, **listOfCheckedMoves;

  for (i = 0 ; i <= 63 ; ++i) {
    if (game.square[i].color == game.activeColor) {
      switch (game.square[i].piece) {
        case pawn:
          listOfRawMoves = pawnMoveGenerator(game);
          break;
        case bishop:
          listOfRawMoves = bishopMoveGenerator(game);
          break;
        case knight:
          listOfRawMoves = knightMoveGenerator(game);
          break;
        case rook:
          listOfRawMoves = rookMoveGenerator(game);
          break;
        case queen:
          listOfRawMoves = queenMoveGenerator(game);
          break;
        case king:
          listOfRawMoves = kingMoveGenerator(game);
          break;
        case empty:
          /*we'll never happen bc activeColor will never be neuter*/
          break;
      }
    }
  }

  listOfCheckedMoves = areTheseLegalMoves(listOfRawMoves, game);

  return listOfCheckedMoves;
}

char **pawnMoveGenerator(Board game) {
  char **listOfRawMoves;

  return listOfRawMoves;
}
char **bishopMoveGenerator(Board game) {
  char **listOfRawMoves;

  return listOfRawMoves;
}
char **knightMoveGenerator(Board game) {
  char **listOfRawMoves;
  
  return listOfRawMoves;

}
char **rookMoveGenerator(Board game) {
  char **listOfRawMoves;

  return listOfRawMoves;
}
char **queenMoveGenerator(Board game) {
  char **listOfRawMoves;

  return listOfRawMoves;
}
char **kingMoveGenerator(Board game) {
  char **listOfRawMoves;

  return listOfRawMoves;
}

/* Its job is to delete illegal moves of the list previously proposed */
char **areTheseLegalMoves(char **listOfRawMoves, Board game) {
  char **listOfCheckedMoves=listOfRawMoves;

  return listOfCheckedMoves;
}




void fenToBoard(char *fen, Board *game) {
  int i = 0;
  int j = 0;
  int k = 0;
  while (fen[i] != ' ') {
    if (fen[i] == '/') {
      ++i;
    } else {
      if (isalpha(fen[i])) {
        switch (fen[i]) {
          case 'P':
            game->square[j].color = white;
            game->square[j].piece = pawn;
            break;
          case 'p':
            game->square[j].color = black;
            game->square[j].piece = pawn;
            break;
          case 'B':
            game->square[j].color = white;
            game->square[j].piece = bishop;
            break;
          case 'b':
            game->square[j].color = black;
            game->square[j].piece = bishop;
            break;
          case 'N':
            game->square[j].color = white;
            game->square[j].piece = knight;
            break;
          case 'n':
            game->square[j].color = black;
            game->square[j].piece = knight;
            break;
          case 'R':
            game->square[j].color = white;
            game->square[j].piece = rook;
            break;
          case 'r':
            game->square[j].color = black;
            game->square[j].piece = rook;
            break;
          case 'Q':
            game->square[j].color = white;
            game->square[j].piece = queen;
            break;
          case 'q':
            game->square[j].color = black;
            game->square[j].piece = queen;
            break;
          case 'K':
            game->square[j].color = white;
            game->square[j].piece = king;
            break;
          case 'k':
            game->square[j].color = black;
            game->square[j].piece = king;
            break;
        }
      ++j;
      } else {
        for (k=1 ; k <= atoi(&fen[i]) ; ++k) {
          game->square[j].piece = empty;
          game->square[j].color = neuter;
          ++j;
        }
      }
      ++i;
      }
    }

  ++i; /*let's go to the next field*/

  while (fen[i] != ' ') {
    if (fen[i] == 'w') {
      game->activeColor = white;
    } else {
      game->activeColor = black;
    }
    ++i;
  }

  ++i; /*To the next field of the fen string*/

  k = 0;
  while (fen[i] != ' ') {
    if (fen[i] == 'K') {
      game->availableCastlings[k] = K;
    } else {
      if (fen[i] == 'k') {
        game->availableCastlings[k] = k;
      } else {
        if (fen[i] == 'Q') {
          game->availableCastlings[k] = Q;
        } else {
          if (fen[i] == 'q') {
            game->availableCastlings[k] = q;
          } else {
            game->availableCastlings[k] = no;
          }
        }
      }
    }
    ++i;
    ++k;
  }

  ++i; /*To the next field of the fen string*/

  while (fen[i] != ' ') {
    if (fen[i] == '-') {
      game->enPassant.column = 'x';
      game->enPassant.line = 0;
      break;
    } else {
      game->enPassant.column = fen[i];
      ++i;
      game->enPassant.line = atoi(&fen[i]);
      ++i;
    }
  }

  ++i;

  while (fen[i] != ' ') {
    game->pliesSinceLastCaptureOrLastPawnMovement = atoi(&fen[i]);
    ++i;
  }

  ++i;

  while (fen[i] != ' ') {
    game->nbMovesTotal = atoi(&fen[i]);
    ++i;
  }
}

void printBoardAndData(Board game) {
  int i;
  printf("\n\n");

  printf("8  ");
  for (i=0 ; i <= (NBSQUARES-1) ; ++i) {
    printf("|");
    switch (game.square[i].piece) {
      case empty:
        printf(" ");
        break;
      case pawn:
        if (game.square[i].color == white)
          printf("P");
        else
          printf("p");
        break;
      case bishop:
        if (game.square[i].color == white)
          printf("B");
        else
          printf("b");
        break;
      case knight:
        if (game.square[i].color == white)
          printf("N");
        else
          printf("n");
        break;
      case rook:
        if (game.square[i].color == white)
          printf("R");
        else
          printf("r");
        break;
      case queen:
        if (game.square[i].color == white)
          printf("Q");
        else
          printf("q");
        break;
      case king:
        if (game.square[i].color == white)
          printf("K");
        else
          printf("k");
        break;
    }
    if ((i+1)%8 == 0) {
      printf("|\n");
      if (i != 63)
        printf("%d  ", 8-i/8-1);
    }
  }
  printf("\n");
  printf("    a b c d e f g h\n\n");

  if (game.activeColor == white)
    printf("Next color to play : white\n");
  else
    printf("Next Color to play : black\n");

  for (i = 0 ; i <= 3 ; ++i) {
    if (game.availableCastlings[i] != no) {
      if (game.availableCastlings[i] == K)
        printf("White can castle on the king side\n");
      if (game.availableCastlings[i] == k)
        printf("Black can castle on the king side\n");
      if (game.availableCastlings[i] == Q)
        printf("White can castle on the queen side\n");
      if (game.availableCastlings[i] == q)
        printf("Black can castle on the queen side\n");
    }
  }

  if (game.enPassant.column != 'x') {
    printf("Square we can reach \"en passant\" : %c%d\n",
      game.enPassant.column, game.enPassant.line);
  } else {
    printf("No square to reach \" en passant\" \n");
  }

  printf("Number of plies since last capture or pawn move : %d\n",
    game.pliesSinceLastCaptureOrLastPawnMovement);
  printf("Number of total moves (starting from 1) : %d\n",
    game.nbMovesTotal);
}
