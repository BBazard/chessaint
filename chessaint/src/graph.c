/* This file is part of the ChessAInt project 2015 */
/**
 *  @file
 *
 *  This file implements functions to manage graph and generate moves
 *
 */

#include "include/graph.h"
#include <stdbool.h>
#include "include/chessboard.h"

/**
 *  @brief Initialisation of a graph item
 *  @param[in,out] graph The graph to alloc
 *
 *  Calls any necessary init function.
 *  @note need graph_free afterwards
 *
 */
void graph_alloc(Graph *graph) {
  graph->links = NULL;
  stack_alloc(&(graph->current_moves));
  initAGame(&graph->root);
  initAGame(&graph->current_node);
}

/**
 *  @brief Free the memory of a graph item
 *  @param[in,out] graph The graph to free
 *
 *  Calls any necessary free function.
 */
void graph_free(Graph *graph) {
  llist_free(&(graph->links));
  stack_free(&(graph->current_moves));
}

/**
 *  @brief gives all moves from a graph
 *  @param[in, out] graph Pointer on the graph used to compute moves
 *
 *  @note  Need to add the en passant kill
 *
 */
void movesGenerator(Graph *graph) {
  Board board = graph->current_node;
  Stack *stack = &(graph->current_moves);
  int kingX, kingY;
  Color opponentColor = getOtherColor(board.activeColor);


  bool pinned[ROWCOL_NB][ROWCOL_NB];
  findAllPinnings(&board, board.activeColor, pinned);

  bool threats[ROWCOL_NB][ROWCOL_NB];
  findThreats(&board, opponentColor, board.activeColor, threats);

  bool thereIsNoKing = true;

  /* finding the king of the given color */
  for (int i = 0 ; i < ROWCOL_NB ; ++i) {
    for (int j = 0 ; j < ROWCOL_NB ; ++j) {
      if ((board.square[i][j].color == board.activeColor) &&
          (board.square[i][j].piece == king)) {
        kingX = i;
        kingY = j;
        thereIsNoKing = false;
      }
    }
  }

  if (!thereIsNoKing && (isThreatened(kingX, kingY, threats))) {
    stopThreat(stack, board, pinned, threats, kingX, kingY);

    kingMoveGenerator(stack, kingX,  kingY, board.activeColor, board, threats);
  } else {
    for (int j = 0 ; j < ROWCOL_NB ; ++j) {
      for (int i = 0 ; i < ROWCOL_NB ; ++i) {
        if (board.square[i][j].color == board.activeColor && !pinned[i][j]) {
          switch (board.square[i][j].piece) {
          case pawn:
            pawnMoveGeneratorCapture(stack, i, j, board.activeColor, board);
            pawnMoveGeneratorNoCapture(stack, i, j, board.activeColor, board);
            break;
          case bishop:
            bishopMoveGenerator(stack, i, j, board.activeColor, board);
            break;
          case knight:
            knightMoveGenerator(stack, i, j, board.activeColor, board);
            break;
          case rook:
            rookMoveGenerator(stack, i,  j, board.activeColor, board);
            break;
          case queen:
            queenMoveGenerator(stack, i, j, board.activeColor, board);
            break;
          case king:
            kingMoveGenerator(stack, i,  j, board.activeColor, board, threats);
            break;
          case empty:
            break;
          }
        }
      }
    }
  }
}

/**
 *  @brief this function is called when the king is threatened and find all
 *          moves (through a stack) that can stop the threat. Then we go back
 *          to movesGenerator
 *  @param[in, out] stack of moves
 *  @param[in] board
 *  @param[in] pinned the map of pinned pieces that cant move
 *  @param[in] threats the map of threats
 *  @param[in] threatenedX
 *  @param[in] threatenedY the coords of the threatened piece (king)
 */
void stopThreat(Stack *stack, Board board, bool pinned[8][8],
               bool threats[8][8], int threatenedX, int threatenedY) {
  Board originalBoard, currentBoard;
  originalBoard = board;
  currentBoard = originalBoard;
  Stack tmpMoves;
  stack_alloc(&tmpMoves);

  Color opponentColor = getOtherColor(board.activeColor);

  int poped;

  stopThreatMoveGenerator(currentBoard, &tmpMoves, pinned);
  while (((poped = stack_pop(&tmpMoves)) != - 1)) {
    playMoveToCheckThreat(poped, &currentBoard);
    findThreats(&currentBoard, opponentColor, currentBoard.activeColor,
                threats);
    /*  printThreatBoard(threats); */
    if (!isThreatened(threatenedX, threatenedY, threats)) {
      stack_push(stack, poped);
      /* printf("\n%d\n",poped); */
    }
    currentBoard = originalBoard;
  }
  stack_free(&tmpMoves);
}

/**
 *  @brief generates all moves except king's one. These moves will then be
 *        checked in stopThreat to see if they stop the threat
 *  @param[in] board
 *  @param[in,out] moves the moves generated
 *  @param[in] pinned because pinned pieces can't move
 */
void stopThreatMoveGenerator(Board board, Stack *moves, bool pinned[8][8]) {
  for (int j = 0 ; j < ROWCOL_NB ; ++j) {
    for (int i = 0 ; i < ROWCOL_NB ; ++i) {
      if (board.square[i][j].color == board.activeColor && !pinned[i][j]) {
        switch (board.square[i][j].piece) {
        case pawn:
          pawnMoveGeneratorCapture(moves, i, j, board.activeColor, board);
          pawnMoveGeneratorNoCapture(moves, i, j, board.activeColor, board);
          break;
        case bishop:
         bishopMoveGenerator(moves, i, j, board.activeColor, board);
          break;
        case knight:
          knightMoveGenerator(moves, i, j, board.activeColor, board);
          break;
        case rook:
          rookMoveGenerator(moves, i,  j, board.activeColor, board);
          break;
        case queen:
          queenMoveGenerator(moves, i, j, board.activeColor, board);
          break;
        case king:
          break;
        case empty:
          break;
        }
      }
    }
  }
}

/**
 *  @brief gives all moves for a pawn sitting on a given square
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX X coord of the pawn (7,7) system
 *  @param[in] squareY Y coord of the pawn (7,7) system
 *  @param[in] activeColor is the color of the pawn
 *  @param[in] board is the current board
 *
 *  This function gives all move for a colored pawn except the chess
 *  position handling.
 */
void pawnMoveGeneratorCapture(Stack *moves,
                              int squareX, int squareY,
                              Color activeColor, Board board) {
  int X, Y;
  Color adverseColor = getOtherColor(activeColor);

  if (activeColor == white)
    Y = squareY + 1;
  else
    Y = squareY - 1;

  /* The classic capture of pieces towards left of the board */
  X = squareX + 1;
  if (isInBoardSquare(X, Y)) {
    if (board.square[X][Y].color == adverseColor)
      stack_push(moves, stack_contract(squareX, squareY, X, Y));
  }

  /* The classic capture of pieces towards right of the board */
  X = squareX - 1;
  if (isInBoardSquare(X, Y)) {
    if (board.square[X][Y].color == adverseColor)
      stack_push(moves, stack_contract(squareX, squareY, X, Y));
  }

  /** @todo en passant
   * The capture en passant
   */
   /*
   if (isInBoardSquare(board.enPassant.line,
   board.enPassant.column)) {
   X = squareX + 1;
   if ((Y == board.enPassant.line) &&
   (X == board.enPassant.column)) {
   stack_push(moves, stack_contract(squareX, squareY, X, Y));
   }
   X = squareX - 1;
   if ((Y == board.enPassant.line) &&
   (X == board.enPassant.column)) {
   stack_push(moves, stack_contract(squareX, squareY, X, Y));
   }
   }
  */
}

/**
 *  @brief gives all moves for a pawn sitting on a given square
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX X coord of the pawn (7,7) system
 *  @param[in] squareY Y coord of the pawn (7,7) system
 *  @param[in] activeColor is the color of the pawn
 *  @param[in] board is the current board
 *
 *  This function gives all move for a colored pawn except the chess
 *  position handling.
 *  @note  Need promotion handling
 */
void pawnMoveGeneratorNoCapture(Stack *moves, int squareX, int squareY,
                                Color activeColor, Board board) {
  /* The simple move forward */
  int whiteMove, blackMove;
  int X = squareX;
  int Y = squareY;
  whiteMove = 1;
  blackMove = -1;
  if (activeColor == white)
    Y = squareY + 1;
  else
    Y = squareY - 1;

  if (isInBoardSquare(X, Y)) {
    if (board.square[X][Y].color == neutral) {
      stack_push(moves, stack_contract(squareX, squareY, X, Y));
      // printf("\n(%d,%d)->(%d,%d)\n", squareX, squareY,X, Y);
    }
  }

  /* Pawn moving 2 squares UP only from 2th row for white and 7th for black */
  if (
      ((activeColor == white) && (squareY == 1) &&
       (board.square[squareX][squareY + 1 * whiteMove].color == neutral) &&
       (board.square[squareX][squareY + 2 * whiteMove].color == neutral))
      ||
      ((activeColor == black) && (squareY == 6) &&
       (board.square[squareX][squareY + 1 * blackMove].color == neutral) &&
       (board.square[squareX][squareY + 2 * blackMove].color == neutral)
       )
      ) {
    if (activeColor == white) {
      stack_push(moves, stack_contract(squareX, 1, squareX,
                                       squareY + 2 * whiteMove));
// printf("\n(%d,%d)->(%d,%d)\n",
// squareX, squareY,squareX,squareY + 2 * whiteMove);
    } else {
      stack_push(moves, stack_contract(squareX, 6, squareX,
                                       squareY + 2 * blackMove));
// printf("\n(%d,%d)->(%d,%d)\n",
// squareX, squareY,squareX,squareY + 2 * blackMove);
    }
  }
}

/**
 *  @brief gives all moves for a bishop sitting on a given square by calling
 *         dedicated subfonctions
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX X coord of the bishop (7,7) system
 *  @param[in] squareY Y coord of the bishop (7,7) system
 *  @param[in] activeColor is the color of the bishop
 *  @param[in] board is the current board
 *
 */
void bishopMoveGenerator(Stack *moves, int squareX, int squareY,
                         Color activeColor, Board board) {
  /* Bishop going North-East */
  bishopAndRook4DirectionsGen(1, 1, moves, squareX, squareY, activeColor,
                              board);

  /* Bishop going South-East */
  bishopAndRook4DirectionsGen(1, -1, moves, squareX, squareY, activeColor,
                              board);

  /* Bishop going South-West */
  bishopAndRook4DirectionsGen(-1, -1, moves, squareX, squareY, activeColor,
                              board);

  /* Bishop going North-West */
  bishopAndRook4DirectionsGen(-1, 1, moves, squareX, squareY, activeColor,
                              board);
}

/**
 *  @brief gives all moves for a rook sitting on a given square by calling
 *  dedicated subfonctions
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX X coord of the rook (7,7) system
 *  @param[in] squareY Y coord of the rook (7,7) system
 *  @param[in] activeColor is the color of the rook
 *  @param[in] board is the current board
 *
 */
void rookMoveGenerator(Stack *moves, int squareX, int squareY,
                       Color activeColor, Board board) {
  /* Rook going North */
  bishopAndRook4DirectionsGen(0, 1, moves, squareX, squareY, activeColor,
                              board);

  /* Rook going South */
  bishopAndRook4DirectionsGen(0, -1, moves, squareX, squareY, activeColor,
                              board);

  /* Rook going East */
  bishopAndRook4DirectionsGen(1, 0, moves, squareX, squareY, activeColor,
                              board);

  /* Rook going West */
  bishopAndRook4DirectionsGen(-1, 0, moves, squareX, squareY, activeColor,
                              board);
}

/**
 *  @brief the subfonctions dealing with the 4 directions of movement
 *  @param[in] incX the X increment of the precise move
 *  @param[in] incY the Y increment of the precise move
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX X coord of the piece (7,7) system
 *  @param[in] squareY Y coord of the pawn (7,7) system
 *  @param[in] activeColor is the color of the piece
 *  @param[in] board is the current board
 *
 *  This function gives all legal move for a colored bishop or rook except
 *  those linked with chess position
 */
void bishopAndRook4DirectionsGen(int incX, int incY, Stack *moves, int squareX,
                                 int squareY, Color activeColor, Board board) {
  int X = squareX;
  int Y = squareY;

  X += incX;
  Y += incY;
  while ((isInBoardSquare(X, Y) && (board.square[X][Y].color == neutral))) {
    stack_push(moves, stack_contract(squareX, squareY, X, Y));
    X += incX;
    Y += incY;
  }

  if (isInBoardSquare(X, Y) && (board.square[X][Y].color != activeColor))
    stack_push(moves, stack_contract(squareX, squareY, X, Y));
}

/**
 *  @brief gives all moves for a queen sitting on a given square
 *
 *  @param[in,out] moves the stack  of moves
 *  @param[in] squareX X coord of the queen (7,7) system
 *  @param[in] squareY Y coord of the queen (7,7) system
 *  @param[in] activeColor is the color of the queen
 *  @param[in] board is the current board
 *  This function gives all legal move for a colored queen except those linked
 *  with chess position
 *  (just waiting for the stack structure)
 */
void queenMoveGenerator(Stack *moves, int squareX, int squareY,
                        Color activeColor, Board board) {
  bishopMoveGenerator(moves, squareX, squareY,
                      activeColor, board);
  rookMoveGenerator(moves, squareX, squareY,
                    activeColor, board);
}

/**
 *  @brief gives all moves for a knight sitting on a given square by calling
 *          subfunctions
 *  @param[in,out] moves the stack  of moves
 *  @param[in] squareX X coord of the knight (7,7) system
 *  @param[in] squareY Y coord of the knight (7,7) system
 *  @param[in] activeColor is the color of the knight
 *  @param[in] board is the current board
 */
void knightMoveGenerator(Stack *moves, int squareX,
                         int squareY, Color activeColor, Board board) {
  /* move : North then East
     | |F|  Finish
     | |
     |S|    Start */
  knightAndKing4DirectionsGen(1, 2, moves, squareX, squareY,
                              activeColor, board);
  /* move : North then West
     |F| |  Finish
     | |
     |S|    Start */
  knightAndKing4DirectionsGen(-1, 2, moves, squareX, squareY,
                              activeColor, board);
  /* move : East then North
     |F|  Finish
     |S| | |  Start */
  knightAndKing4DirectionsGen(2, 1, moves, squareX, squareY,
                              activeColor, board);
  /* move : East then South
     |S| | |  Start
     |F|  Finish */
  knightAndKing4DirectionsGen(2, -1, moves, squareX, squareY,
                              activeColor, board);
  /* move : South then West
     |S|  Start
     | |
     |F| |  Finish */
  knightAndKing4DirectionsGen(-1, -2, moves, squareX, squareY,
                              activeColor, board);
  /* move : South then East
     |S|    Start
     | |
     | |F|  Finish */
  knightAndKing4DirectionsGen(1, -2, moves, squareX, squareY,
                              activeColor, board);
  /* move : West then North
     |F|      Finish
     | | |S|  Start */
  knightAndKing4DirectionsGen(-2, 1, moves, squareX, squareY,
                              activeColor, board);
  /* move : West then South
     | | |S|  Start
     |F|      Finish */
  knightAndKing4DirectionsGen(-2, -1, moves, squareX, squareY,
                              activeColor, board);
}

/**
 *  @brief gives all moves for a king sitting on a given square by calling
 *          a subfunction
 *  @param[in,out] moves is the stack of moves
 *  @param[in] squareX X coord of the king (7,7) system
 *  @param[in] squareY Y coord of the king (7,7) system
 *  @param[in] activeColor is the color of the king
 *  @param[in] board is the current board
 *  @param threats The matrix of threats
 *
 */
void kingMoveGenerator(Stack *moves, int squareX,
                       int squareY, Color activeColor, Board board,
                       bool threats[8][8]) {
  if (isInBoardSquare(squareX, squareY + 1)) {
    if (!threats[squareX][squareY + 1]) {
      /* To the North */
      // printf("\n(%d,%d)->(%d,%d)\n", squareX, squareY, squareX, squareY + 1);
      knightAndKing4DirectionsGen(0, 1, moves, squareX, squareY,
                                  activeColor, board);
    }
  }
  if (isInBoardSquare(squareX + 1, squareY)) {
    if (!threats[squareX + 1][squareY]) {
      // printf("\n(%d,%d)->(%d,%d)\n", squareX, squareY, squareX + 1, squareY);
      /* To the East */
      knightAndKing4DirectionsGen(1, 0, moves, squareX, squareY,
                                  activeColor, board);
    }
  }
  if (isInBoardSquare(squareX, squareY - 1)) {
    if (!threats[squareX][squareY - 1]) {
      /*  printf("\n(%d,%d)->(%d,%d)\n", squareX, squareY, squareX,
          squareY - 1); */
      /* To the South */
      knightAndKing4DirectionsGen(0, -1, moves, squareX, squareY,
                                  activeColor, board);
    }
  }
  if (isInBoardSquare(squareX - 1, squareY)) {
    if (!threats[squareX - 1 ][squareY]) {
//  printf("\n(%d,%d)->(%d,%d)\n", squareX, squareY, squareX - 1, squareY);
      /* To the West */
      knightAndKing4DirectionsGen(-1, 0, moves, squareX, squareY,
                                  activeColor, board);
    }
  }
  if (isInBoardSquare(squareX + 1, squareY + 1)) {
    if (!threats[squareX + 1 ][squareY + 1]) {
// printf("\n(%d,%d)->(%d,%d)\n", squareX, squareY, squareX + 1 , squareY + 1);
      /* To the North-East */
      knightAndKing4DirectionsGen(1, 1, moves, squareX, squareY,
                                  activeColor, board);
    }
  }
  if (isInBoardSquare(squareX + 1, squareY - 1)) {
    if (!threats[squareX +1 ][squareY - 1]) {
// printf("\n(%d,%d)->(%d,%d)\n", squareX, squareY, squareX + 1, squareY - 1);
      /* To the South-East */
      knightAndKing4DirectionsGen(1, -1, moves, squareX, squareY,
                                  activeColor, board);
    }
  }
  if (isInBoardSquare(squareX - 1, squareY - 1)) {
    if (!threats[squareX - 1][squareY - 1]) {
// printf("\n(%d,%d)->(%d,%d)\n", squareX, squareY, squareX - 1, squareY - 1);
      /* To the South-West */
      knightAndKing4DirectionsGen(-1, -1, moves, squareX, squareY,
                                  activeColor, board);
    }
  }
  if (isInBoardSquare(squareX - 1, squareY + 1)) {
    if (!threats[squareX - 1][squareY + 1]) {
// printf("\n(%d,%d)->(%d,%d)\n", squareX, squareY, squareX - 1, squareY + 1);
      /* To the North-West */
      knightAndKing4DirectionsGen(-1, 1, moves, squareX, squareY,
                                  activeColor, board);
    }
  }
  /*First condition on castling : not be in checked position */
  if (!threats[squareX][squareY]) {
    for (int i = 0 ; i < 4 ; ++i) {
      if (board.availableCastlings[i] == 1) {
        switch (i) {
          case 0:
            if ((activeColor == white) && (!threats[squareX + 1][squareY]) &&
                (!threats[squareX + 2][squareY]))
              /* castlesMoveGenerator(1, squareX, squareY, moves, board); */
            break;
          case 1:
            if ((activeColor == white) && (!threats[squareX - 1][squareY]) &&
                (!threats[squareX - 2][squareY]))
             /* castlesMoveGenerator(-1, squareX, squareY, moves, board); */
            break;
          case 2:
            if ((activeColor == black) && (!threats[squareX + 1][squareY]) &&
                (!threats[squareX + 2][squareY]))
             /*  castlesMoveGenerator(1, squareX, squareY, moves, board); */
            break;
          case 3:
            if ((activeColor == black) && (!threats[squareX - 1][squareX]) &&
                (!threats[squareX - 2][squareY]))
            /*  castlesMoveGenerator(-1, squareX, squareY, moves, board); */
            break;
        }
      }
    }
  }
}

/**
 *  @brief Checks if castle is possible and add the move to stack if it is
 *  @param[in] incX used to determine what castle we are checking
 *  @param[in] squareX original position of the king who want to castle
 *  @param[in] squareY original position of the king who want to castle
 *  @param[in, out] moves is a stack that keep track of the results
 *  @param[in] board is the board of the game
 */
void castlesMoveGenerator(int incX, int squareX, int squareY, Stack *moves,
                          Board board) {
  int testSquare = squareX;
  int nextSquareX = 2 * incX + squareX;
  bool canCastle = true;

  if (incX < 0) {
    if (board.square[1][squareY].color != neutral)
      canCastle = false;
  }

  do {
    testSquare += incX;
    if (board.square[testSquare][squareY].color != neutral) {
      canCastle = false;
    }
  } while (testSquare != nextSquareX);

  if (canCastle) {
    stack_push(moves, stack_contract(squareX, squareY, nextSquareX, squareY));
  }
}

/**
 *  @brief the subfonctions dealing with the 4 directions of movement
 *  @param[in] incX the increment on X of the particular move being considered
 *  @param[in] incY the increment on Y of the particular move being considered
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX X coord of the piece (7,7) system
 *  @param[in] squareY Y coord of the piece (7,7) system
 *  @param[in] activeColor is the color of the piece
 *  @param[in] board is the current board
 *
 *  This function gives all legal move for a colored knight or king except
 *  those linked with chess position
 */
void knightAndKing4DirectionsGen(int incX, int incY, Stack *moves,
                                 int squareX, int squareY,
                                 Color activeColor, Board board) {
  int X = squareX + incX;
  int Y = squareY + incY;

  if (isInBoardSquare(X, Y) && (board.square[X][Y].color != activeColor))
    stack_push(moves, stack_contract(squareX, squareY, X, Y));
}

/**
 *  @brief play a move on a board
 *  @param[in] move the move to play, Ex : 4143 pour e2e4
 *  @param[in,out] board the board on which to play the move
 *
 *  @todo Need to update castling in board
 *
 */
void play_move(int move, Board *board) {
  int a, b, c, d;
  stack_expand(&a, &b, &c, &d, move);

  if (board->square[a][b].piece == pawn || board->square[c][d].piece != empty)
    board->halfMoveClock += 1;
  board->activeColor = (board->activeColor + 1) % 2;
  if (board->square[a][b].piece == pawn && d == b + 2)
    board->enPassant.column = 1; /* means there is enpassant */
  else
    board->enPassant.column = 0; /* means there is no enpassant */
  board->fullMoveNb += 1;

  /* Updating castlings list */
  if (board->activeColor == white) {
    if (a == 7 && b == 0)
      board->availableCastlings[0] = 0;
    if (a == 0 && b == 0)
      board->availableCastlings[1] = 0;
    if (a == 4 && b == 0) {
      board->availableCastlings[0] = 0;
      board->availableCastlings[1] = 0;
    }
  } else if (board->activeColor == black) {
    if (a == 7 && b == 7)
      board->availableCastlings[2] = 0;
    if (a == 0 && b == 7)
      board->availableCastlings[3] = 0;
    if (a == 4 && b == 7) {
      board->availableCastlings[2] = 0;
      board->availableCastlings[3] = 0;
    }
  }

  board->square[c][d] = board->square[a][b];
  board->square[a][b].color = neutral;
  board->square[a][b].piece = empty;
}

/**
 *  @param[in,out] s The stack in which are stored the moves
 *  @param[in,out] current The board to update
 *  Called by update_board, should never be used in another way
 *
 */
void update_moves(Stack *s, Board *current) {
  int current_move = stack_pop(s);

  if (current_move != -1) {
    update_moves(s, current);
    play_move(current_move, current);
  }
}

/**
 *  @brief Update graph->current node
 *  @param[in] father The node in which the board will be updated
 *  @param[in, out] board The board to update
 *
 *  This function updates the current_node board of the graph according
 *  to the data contained in the node identifier and the root board
 *
 */
void update_board(Node father, Board *board) {
  Stack stack;
  stack_alloc(&stack);
  identifier_to_stack(*(father.data), &stack);

  update_moves(&stack, board);

  int tmp = identifier_get_cast(*(father.data));
  for (int i = 0; i < 3; ++i) {
    board->availableCastlings[i] = tmp%2;
    tmp /= 2;
  }
  board->halfMoveClock = identifier_get_halfmove(*(father.data));
  board->fullMoveNb = identifier_get_fullmove(*(father.data));
  stack_free(&stack);
}

/**
 *  @brief This function gives in the threats array all the threats or
 *          protections (depending of the point of view) of color1 over color2
 *
 *  @param[in, out] board
 *  @param[in] color1 the color that attacks or defends
 *  @param[in] color2 the color to attack or defend
 *  @param[in, out] threats the map of threats (or protection)
 */
void findThreats(Board *board, Color color1, Color color2,
                      bool threats[8][8]) {
  /* No use in this version */
  if (color2 != neutral)
    color2 = neutral;

  /* Needed */
  for (int i = 0 ; i < 8 ; ++i) {
    for (int j = 0 ; j < 8 ; ++j) {
      threats[i][j] = false;
    }
  }

  /*we draw the array of threats <-> squares that opponent can capture */
  for (int i = 0 ; i < ROWCOL_NB ; ++i) {
    for (int j = 0 ; j < ROWCOL_NB ; ++j) {
      if (board->square[i][j].color == color1) {
        switch (board->square[i][j].piece) {
        case bishop:
          bishopThreatGenerator(i, j, *board, threats);
          break;
        case knight:
          knightThreatGenerator(i, j, threats);
          break;
        case rook:
          rookThreatGenerator(i, j, *board, threats);
          break;
        case queen:
          queenThreatGenerator(i, j, *board, threats);
          break;
        case king:
          kingThreatGenerator(i, j, threats);
          break;
        case pawn:
          pawnThreatGenerator(i, j, color1, threats);
          break;
        case empty:
          break;
        }
      }
    }
  }
}

/**
 *  @brief give all theatened square by a bishop through the call of a subfct
 *  @param[in] squareX X coord of the bishop (7,7) system
 *  @param[in] squareY Y coord of the bishop (7,7) system
 *  @param[in] board is the current board
 *  @param[in] threats is the matrix of booleans representing the threatened
 *  square
 *
 */
void bishopThreatGenerator(int squareX, int squareY, Board board,
                          bool threats[8][8]) {
  /* Bishop going North-East */
  lineThreatGenerator(1, 1, squareX, squareY, board, threats);

  /* Bishop going South-East */
  lineThreatGenerator(1, -1, squareX, squareY, board, threats);

  /* Bishop going South-West */
  lineThreatGenerator(-1, -1, squareX, squareY, board, threats);

  /* Bishop going North-West */
  lineThreatGenerator(-1, 1, squareX, squareY, board, threats);
}

/**
 *  @brief gives all threats for a rook sitting on a given square by calling
 *  dedicated subfonctions
 *  @param[in] squareX X coord of the rook (7,7) system
 *  @param[in] squareY Y coord of the rook (7,7) system
 *  @param[in] board is the current board
 *  @param[in] threats is the matrix of booleans representing the threatened
 *  square
 *
 */
void rookThreatGenerator(int squareX, int squareY, Board board,
                         bool threats[8][8]) {
  /* Rook going North */
  lineThreatGenerator(0, 1, squareX, squareY, board, threats);

  /* Rook going South */
  lineThreatGenerator(0, -1, squareX, squareY, board, threats);

  /* Rook going East */
  lineThreatGenerator(1, 0, squareX, squareY, board, threats);

  /* Rook going West */
  lineThreatGenerator(-1, 0,  squareX, squareY, board, threats);
}

/**
 *  @brief gives all threats for a queen sitting on a given square
 *  @param[in] squareX X coord of the queen (7,7) system
 *  @param[in] squareY Y coord of the queen (7,7) system
 *  @param[in] board is the current board
 *  @param[in] threats is the board of booleans representing the threatened
 *             square
 */
void queenThreatGenerator(int squareX, int squareY, Board board,
                          bool threats[8][8]) {
  bishopThreatGenerator(squareX, squareY, board, threats);
  rookThreatGenerator(squareX, squareY, board, threats);
}

/**
 *  @brief this subfunction must mark a square as a threat for the opponent of
 *         pieceColor
 *  @param[in] incX the X increment of the precise move
 *  @param[in] incY the Y increment of the precise move
 *  @param[in] squareX X coord of the piece (7,7) system
 *  @param[in] squareY Y coord of the piece (7,7) system
 *  @param[in] board is the current board
 *  @param[in] threats is the board of booleans representing the threatened
 *             square
 *
 *  This function gives all threatened square for a colored bishop or rook
 *  in a boolean array
 */
void lineThreatGenerator(int incX, int incY, int squareX,
                         int squareY, Board board, bool threats[8][8]) {
  int X = squareX;
  int Y = squareY;

  X += incX;
  Y += incY;
  while (((isInBoardSquare(X, Y) && (board.square[X][Y].color == neutral)))
      || (isInBoardSquare(X, Y) &&
        (board.square[X][Y].color == board.activeColor) &&
        board.square[X][Y].piece == king)) {
    threats[X][Y] = true;
    X += incX;
    Y += incY;
  }

  if (isInBoardSquare(X, Y))
    threats[X][Y] = true;
}
/**
 *  @brief Print a threat matrix
 *  @param[in] threats The matrix to print
 *
 */
void printThreatBoard(bool threats[8][8]) {
  for (int j = 7 ; j >= 0 ; --j) {
    printf("|");
    for (int i = 0 ; i < 8 ; ++i) {
      printf("%s|", threats[i][j] ? "x" : " ");
    }
    printf("\n");
  }
}

/**
 *  @brief gives all moves for a knight sitting on a given square by calling
 *         subfunctions
 *
 *  @param[in] squareX X coord of the knight (7,7) system
 *  @param[in] squareY Y coord of the knight (7,7) system
 *  @param[in] threats is the board of booleans representing the threatened
 *             square
 */
void knightThreatGenerator(int squareX, int squareY, bool threats[8][8]) {
  /* move : North then East
     | |F|  Finish
     | |
     |S|    Start */
  squareThreatGenerator(1, 2, squareX, squareY, threats);
  /* move : North then West
     |F| |  Finish
     | |
     |S|    Start */
  squareThreatGenerator(-1, 2, squareX, squareY, threats);
  /* move : East then North
     |F|  Finish
     |S| | |  Start */
  squareThreatGenerator(2, 1, squareX, squareY, threats);
  /* move : East then South
     |S| | |  Start
     |F|  Finish */
  squareThreatGenerator(2, -1, squareX, squareY, threats);
  /* move : South then West
     |S|  Start
     | |
     |F| |  Finish */
  squareThreatGenerator(-1, -2, squareX, squareY, threats);
  /* move : South then East
     |S|    Start
     | |
     | |F|  Finish */
  squareThreatGenerator(1, -2, squareX, squareY, threats);
  /* move : West then North
     |F|      Finish
     | | |S|  Start */
  squareThreatGenerator(-2, 1, squareX, squareY, threats);
  /* move : West then South
     | | |S|  Start
     |F|      Finish */
  squareThreatGenerator(-2, -1, squareX, squareY, threats);
}

/**
 *  @brief gives all threats for a king sitting on a given square by calling
 *          a subfunction
 *  @param[in] squareX X coord of the king (7,7) system
 *  @param[in] squareY Y coord of the king (7,7) system
 *  @param[in] threats is the board of booleans representing the threatened
 *             square
 */
void kingThreatGenerator(int squareX, int squareY, bool threats[8][8]) {
  /* To the North */
  squareThreatGenerator(0, 1, squareX, squareY, threats);
  /* To the East */
  squareThreatGenerator(1, 0, squareX, squareY, threats);
  /* To the South */
  squareThreatGenerator(0, -1, squareX, squareY, threats);
  /* To the West */
  squareThreatGenerator(-1, 0, squareX, squareY, threats);
  /* To the North-East */
  squareThreatGenerator(1, 1, squareX, squareY, threats);
  /* To the South-East */
  squareThreatGenerator(1, -1, squareX, squareY, threats);
  /* To the South-West */
  squareThreatGenerator(-1, -1, squareX, squareY, threats);
  /* To the North-West */
  squareThreatGenerator(-1, 1, squareX, squareY, threats);
}

/**
 *  @brief gives all threats for a pawn sitting on a given square
 *  @param[in] squareX X coord of the pawn (7,7) system
 *  @param[in] squareY Y coord of the pawn (7,7) system
 *  @param[in] pieceColor is the color of the pawn
 *  @param[in] threats is the board of booleans representing the threatened
 *             square
 *
 *  @note : no enPassant handling yet
 *
 */
void pawnThreatGenerator(int squareX, int squareY,
                         Color pieceColor, bool threats[8][8]) {
  int X, Y;
  if (pieceColor == white)
    Y = squareY + 1;
  else
    Y = squareY - 1;

  /* The classic capture of pieces towards left of the board */
  X = squareX + 1;
  if (isInBoardSquare(X, Y)) {
    threats[X][Y] = true;
  }

  /* The classic capture of pieces towards right of the board */
  X = squareX - 1;
  if (isInBoardSquare(X, Y)) {
    threats[X][Y] = true;
  }
}

/**
 *  @brief this subfunction must mark a square as a threat for the opponent of
 *         pieceColor
 *  @param[in] incX the increment on X of the particular move being considered
 *  @param[in] incY the increment on Y of the particular move being considered
 *  @param[in] squareX X coord of the piece (7,7) system
 *  @param[in] squareY Y coord of the piece (7,7) system
 *  @param[in] threats is the board of booleans representing the threatened
 *             square
 *
 */
void squareThreatGenerator(int incX, int incY, int squareX, int squareY,
                           bool threats[8][8]) {
  int X = squareX + incX;
  int Y = squareY + incY;

  if (isInBoardSquare(X, Y))
    threats[X][Y] = true;
}

/**
 *  @brief tells if a piece is threatened. USEFUL TO FIND IF KING IS CHECKED
 *  @param[out] threats The matrix in which is stored the result
 *  @param[in] X
 *  @param[in] Y : the coords of the checked square
 *  @param[in] threats the map of the threats
 */
bool isThreatened(int X, int Y, bool threats[8][8]) {
  return threats[X][Y];
}

/**
 *  @brief tells if a piece is surrounded ie can't move all around itself
 *          this calls a subfunction : checkSurroundigs
 *  @param[out] threats The board in which is stored the result
 *  @param[in] X
 *  @param[in] Y the coords of the piece to be checked
 *  @param[in] board the board
 *  @param[in] threats the map of threats
 */
bool isSurrounded(int X, int Y, Board board, bool threats[8][8]) {
  bool answer;
  answer = true;

  checkSurroundings(X, Y + 1, board, threats, &answer);
  checkSurroundings(X, Y - 1, board, threats, &answer);
  checkSurroundings(X + 1, Y, board, threats, &answer);
  checkSurroundings(X - 1, Y, board, threats, &answer);
  checkSurroundings(X + 1, Y + 1, board, threats, &answer);
  checkSurroundings(X + 1, Y - 1, board, threats, &answer);
  checkSurroundings(X - 1, Y + 1, board, threats, &answer);
  checkSurroundings(X - 1, Y - 1, board, threats, &answer);

  return answer;
}

/**
 *  @brief tells if a given square can't be reached
 *  @param[in, out] threats The board in which is stored the result
 *  @param[in] X
 *  @param[in] Y the coords of the piece to be checked
 *  @param[in] board the board
 *  @param[in] threats the map of threats
 *  @param answer true if the square can be reached
 *  false otherwise
 */
void checkSurroundings(int X, int Y, Board board, bool threats[8][8],
                      bool *answer) {
  if (isInBoardSquare(X, Y)) {
    if ((threats[X][Y] == false)
        && (board.square[X][Y].color != board.activeColor))
      *answer = false;
  }
}

/**
 *  @brief just moves a piece to see what becomes the board
 *  @param[in,out] board The board to update
 *  @param[in] move The move in compressed writing style
 *
 *  @note this should later take in account castlings etc..
 */
void playMoveToCheckThreat(int move, Board *board) {
  int a, b, c, d;
  stack_expand(&a, &b, &c, &d, move);

  board->square[c][d] = board->square[a][b];
  board->square[a][b].color = neutral;
  board->square[a][b].piece = empty;
}

