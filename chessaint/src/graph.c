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
 *  @fn void graph_init(Graph *graph)
 *  @brief Initialisation of a graph item
 *
 *  Calls any necessary init function.
 *  @note need graph_free afterwards
 */
void graph_init(Graph *graph) {
  graph->links = NULL;
  stack_init(&(graph->current_moves));
  initAGame(&graph->root);
  initAGame(&graph->current_node);
}

void graph_free(Graph *graph) {
  stack_free(&(graph->current_moves));
}

/**
 *  @fn void movesGenerator(Graph graph)
 *  @brief gives all moves from a graph
 *  @param[in, out] graph Pointer on the graph used to compute moves
 *
 *  @note  Need to add the en passant kill
 *  @bug "root" (in graph->root and others) seems to refer to
 *  current_node (in graph struct)
 *  Need to change that
 *
 */
void movesGenerator(Graph *graph) {
  Board board = graph->current_node;
  Stack *stack = &(graph->current_moves);

  for (int j = 0 ; j < ROWCOL_NB ; ++j) {
    for (int i = 0 ; i < ROWCOL_NB ; ++i) {
      if ((board.square[i][j].color == board.activeColor) &&
          1 /** todo the piece is not pinned */ ) {
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
          kingMoveGenerator(stack, i,  j, board.activeColor, board);
          break;
        case empty:
          break;
        }
      }
    }
  }
}

/**
 *  @fn void pawnMoveGeneratorCapture(Stack *moves, int squareX, int squareY,
 *  Color activeColor, Board board, Coord enPassant)
 *  @brief gives all moves for a pawn sitting on a given square
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX 
 *  @param[in] squareY are the position of the pawx (7,7) system
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
  Color adverseColor;
  if (activeColor == white) {
    adverseColor = black;
    Y = squareY + 1;
  } else {
    adverseColor = white;
    Y = squareY - 1;
  }

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
   *
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
 *  @fn void pawnMoveGeneratorNoCapture(Stack *moves, int squareX, int squareY,
 *  Color activeColor, Board board, Coord enPassant)
 *  @brief gives all moves for a pawn sitting on a given square
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX 
 *  @param[in] squareY are the position of the pawx (7,7) system
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
    } else {
      stack_push(moves, stack_contract(squareX, 6, squareX,
                                       squareY + 2 * blackMove));
    }
  }
}
/**
 *  @fn void bishopMoveGenerator(Stack *moves, int squareX, int squareY,
 Color activeColor, Board board)
 *  @brief gives all moves for a bishop sitting on a given square by calling
           dedicated subfonctions
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX 
 *  @param[in] squareY are the position of the bishop (7,7) system
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
 *  @fn void rookMoveGenerator(Stack *moves, int squareX, int squareY,
 Color activeColor, Board board)
 *  @brief gives all moves for a rook sitting on a given square by calling
           dedicated subfonctions
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX 
 *  @param[in] squareY are the position of the rook (7,7) system
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
 *  @fn void bishopAndRook4DirectionsGen(int incX, int incY, Stack *moves,
 *                          int squareX, int squareY, Color activeColor,
 *                         Board board)
 *  @brief the subfonctions dealing with the 4 directions of movement
 *  @param[in] incX the X increment of the precise move 
 *  @param[in] incY the Y increment of the precise move 
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX 
 *  @param[in] squareY are the position of the piece (7,7) system
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
 *  find the piece which cannot move
 *  because of pinnings
 *
 *  fill pinned array
 *
 */
void findPinnings(Board *board, Color activeColor, bool pinned[8][8]) {
}

/**
 *  find if the square next to the king are threated
 *  and if the king itself is threated
 *
 *  fill threats array
 */
void findKingThreats(Board *board, Color activeColor, bool threats[8][8]) {
}

/**
 *  @fn void queenMoveGenerator(Stack *moves, int squareX, int squareY,
 Color activeColor, Board board)
 *  @brief gives all moves for a queen sitting on a given square
 *
 *  @param[in,out] moves the stack  of moves
 *  @param[in] squareX 
 *  @param[in] squareY are the position of the queen (7,7) system
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
 *  @fn void knightMoveGenerator(Stack *moves, int squareX, int squareY,
 *      Color activeColor, Board board)
 *  @brief gives all moves for a knight sitting on a given square by calling
 *          subfunctions
 *  @param[in,out] moves the stack  of moves
 *  @param[in] squareX 
 *  @param[in] squareY are the position of the knight (7,7) system
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
 *  @fn void kingMoveGenerator(Stack *moves, int squareX, int squareY,
 *      Color activeColor, Board board)
 *  @brief gives all moves for a king sitting on a given square by calling
 *          a subfunction
 *  @param[in,out] moves is the stack of moves
 *  @param[in] squareX 
 *  @param[in] squareY are the position of the king (7,7) system
 *  @param[in] activeColor is the color of the king
 *  @param[in] board is the current board
 *  @note No chess position handling here !
 *  @note No castling handling yet !
 *
 */
void kingMoveGenerator(Stack *moves, int squareX,
                       int squareY, Color activeColor, Board board) {
  /* To the North */
  knightAndKing4DirectionsGen(0, 1, moves, squareX, squareY,
                              activeColor, board);
  /* To the East */
  knightAndKing4DirectionsGen(1, 0, moves, squareX, squareY,
                              activeColor, board);
  /* To the South */
  knightAndKing4DirectionsGen(0, -1, moves, squareX, squareY,
                              activeColor, board);
  /* To the West */
  knightAndKing4DirectionsGen(-1, 0, moves, squareX, squareY,
                              activeColor, board);
  /* To the North-East */
  knightAndKing4DirectionsGen(1, 1, moves, squareX, squareY,
                              activeColor, board);
  /* To the South-East */
  knightAndKing4DirectionsGen(1, -1, moves, squareX, squareY,
                              activeColor, board);
  /* To the South-West */
  knightAndKing4DirectionsGen(-1, -1, moves, squareX, squareY,
                              activeColor, board);
  /* To the North-West */
  knightAndKing4DirectionsGen(-1, 1, moves, squareX, squareY,
                              activeColor, board);

  for (int i = 0 ; i < 4 ; ++i) {
    if (board.availableCastlings[i] == 1) {
      switch (i) {
        case 0:
          if (activeColor == white)
            castlesMoveGenerator(1, squareX, squareY, moves, board);
          break;
        case 1:
          if (activeColor == white)
            castlesMoveGenerator(-1, squareX, squareY, moves, board);
          break;
        case 2:
          if (activeColor == black)
            castlesMoveGenerator(1, squareX, squareY, moves, board);
          break;
        case 3:
          if (activeColor == black)
            castlesMoveGenerator(-1, squareX, squareY, moves, board);
          break;
      }
    }
  }
}

/**
 *  @fn void castlesMoveGenerator(int incX, int squareX, int squareY,
 *                         Stack *moves, Board board) {
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
    printf("(%d,%d)->(%d,%d)\n", squareX, squareY, nextSquareX, squareY);
  }
}

/**
 *  @fn void knightAndKing4DirectionsGen(int incX, int incY, Stack *moves,
 *                  int squareX, int squareY, Color activeColor, Board board)
 *  @brief the subfonctions dealing with the 4 directions of movement
 *  @param[in] incX the increment on X of the particular move being considered
 *  @param[in] incY the increment on Y of the particular move being considered
 *  @param[in,out] moves the stack of moves
 *  @param[in] squareX 
 *  @param[in] squareY are the position of the piece (7,7) system
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
 *  @fn isInBoardSquare(int squareX, int squareY)
 *  @brief Test if the given square given with its coordinates is in the board
 *  @param[in] squareX 
 *  @param[in] squareY are the coordinates of the square to test
 *  @param[out] bool : true if the square is in false otherwise.
 */
bool isInBoardSquare(int squareX, int squareY) {
  return (squareX >= 0) && (squareX <= 7) && (squareY >= 0) && (squareY <= 7);
}

/**
 *  @fn void play_move(int move, Board *board)
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

  /* Castling */
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
 * called by update_board,
 * should never be used in another way
 */
void update_moves(Stack *s, Board *current) {
  int current_move = stack_pop(s);

  if (current_move != -1) {
    update_moves(s, current);
    play_move(current_move, current);
  }
}

/**
 *  @fn void update_board(Arc father, Graph *graph)
 *  @brief Update graph->current node
 *  @param[in] father The arc in which the board will be updated
 *  @param[in] graph->root The reference board
 *  @param[out] graph->current_node The board updated
 *
 *  This function updates the current_node board of the graph according
 *  to the data contained in the arc identifier and the root board
 *
 *  @todo Coord enPassant not updated currently need to correct that
 *  @todo For Alexis :
 *  change idendifier_is_white by a getColor or something meaningful Alexis
 *
 */
void update_board(Arc father, Board *board) {
  Stack stack;
  stack_init(&stack);
  identifier_to_stack(father.data, &stack);
  update_moves(&stack, board);
  board->activeColor = !identifier_is_white(father.data);

  int tmp = identifier_get_cast(father.data);
  for (int i = 0; i < 3; ++i) {
    board->availableCastlings[i] = tmp%2;
    tmp /= 2;
  }
  board->halfMoveClock = identifier_get_halfmove(father.data);
  board->fullMoveNb = identifier_get_fullmove(father.data);
  stack_free(&stack);
}
