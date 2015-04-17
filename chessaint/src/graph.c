/* This file is part of the ChessAInt project 2015 */
/**
 *  @file graph.c
 *  @brief graph structure basic functions
 *
 *  This file implements functions to manage graph and generate moves
 *
 */

#include "include/graph.h"

#include <assert.h>
#include <string.h>

/**
 *  @fn void graph_init(Graph *graph)
 *  @brief Initialisation of a graph item
 *  @param[in, out] graph Pointer to the graph
 *
 *  Calls any necessary init function.
 */

void graph_init(Graph *graph) {
  graph->links = NULL;
  stack_init(&(graph->current_moves));
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
  int i = 0;
  int j = 0;

  for (i = 0 ; i <= ROWCOL_NB - 1; ++i) {
    for (j = 0 ; j <= (ROWCOL_NB - 1) ; ++j) {
      if (graph->current_node.square[i][j].color ==
          graph->current_node.activeColor) {
        switch (graph->current_node.square[i][j].piece) {
        case pawn:
          pawnMoveGenerator(&(graph->current_moves), 7 - j, 7 - i,
                            graph->current_node.activeColor,
                            graph->current_node);
          break;
        case bishop:
          bishopMoveGenerator(&(graph->current_moves), 7 - j, 7 - i,
                              graph->current_node.activeColor,
                              graph->current_node);
          break;
        case knight:
          knightMoveGenerator(&(graph->current_moves), 7 - j, 7 - i,
                              graph->current_node.activeColor,
                              graph->current_node);
          break;
        case rook:
          rookMoveGenerator(&(graph->current_moves), 7 - j, 7 - i,
                            graph->current_node.activeColor,
                            graph->current_node);
          break;
        case queen:
          queenMoveGenerator(&(graph->current_moves), 7 - j, 7 - i,
                             graph->current_node.activeColor,
                             graph->current_node);
          break;
        case king:
          kingMoveGenerator(&(graph->current_moves), 7 - j, 7 - i,
                            graph->current_node.activeColor,
                            graph->current_node);
          break;
        case empty:
          break;
        }
      }
    }
  }
}

/**
 *  @fn void pawnMoveGenerator(Stack *moves, int squareX, int squareY,
 *  Color activeColor, Board board, Coord enPassant)
 *  @brief gives all moves for a pawn sitting on a given square
 *  @param[in] squareX and squareY are the position of the bishop (7,7) system
 *              activeColor is the color of the bishop
 *               board is the current board
 *
 *  This function gives all move for a colored pawn except the chess
 *  position handling.
 *  @note  Need promotion handling
 */

void pawnMoveGenerator(Stack *moves, int squareX,
                       int squareY, Color activeColor, Board board) {
  int whiteMove, blackMove;
  int nextSquareX, nextSquareY;
  if (activeColor == white) {
    nextSquareY = squareY + 1;
  } else {
    nextSquareY = squareY - 1;
  }

  /* The simple move forward */
  nextSquareX = squareX;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color == neutral) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }

  /* The classic capture of pieces towards left of the board */
  nextSquareX = squareX + 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if ((board.square[nextSquareY][nextSquareX].color != neutral) &&
        (board.square[nextSquareY][nextSquareX].color != activeColor)) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }

  /* The classic capture of pieces towards right of the board */
  nextSquareX = squareX - 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if ((board.square[nextSquareY][nextSquareX].color != neutral) &&
        (board.square[nextSquareY][nextSquareX].color != activeColor)) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }

  /* The capture en passant */
  if (isInBoardSquare(board.enPassant.line,
                      board.enPassant.column)) {
    nextSquareX = squareX + 1;
    if ((nextSquareY == board.enPassant.line) &&
        (nextSquareX == board.enPassant.column)) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
    nextSquareX = squareX - 1;
    if ((nextSquareY == board.enPassant.line) &&
        (nextSquareX == board.enPassant.column)) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }


  /* Pawn moving 2 squares UP only from 2th row for white and 7th for black */
  whiteMove = 1;
  blackMove = -1;
  if (
      ((activeColor == white) &&
       (board.square[squareY + 1 * whiteMove][squareX].color == neutral) &&
       (board.square[squareY + 2 * whiteMove][squareX].color != activeColor) &&
       (squareY == 1)) ||
      ((activeColor == black) &&
       (board.square[squareY + 1 * blackMove][squareX].color == neutral) &&
       (board.square[squareY + 2 * blackMove][squareX].color != activeColor) &&
       (squareY == 6))
      ) {
    if (activeColor == white) {
      stack_push(moves, stack_exchange(squareX, 1, squareX,
                                       squareY + 2 * whiteMove));
    } else {
      stack_push(moves, stack_exchange(squareX, 6, squareX,
                                       squareY + 2 * blackMove));
    }
  }
}

/**
 *  @fn void bishopMoveGenerator(Stack *moves, int squareX, int squareY,
 Color activeColor, Board board)
 *  @brief gives all moves for a bishop sitting on a given square
 *  @param[in] squareX and squareY are the position of the bishop (7,7) system
 *              activeColor is the color of the bishop
 *              board is the current board
 *
 *
 *  This function gives all legal move for a colored bishop except
 *  those linked with chess position
 *  (just waiting for the stack structure)
 */

void bishopMoveGenerator(Stack *moves, int squareX, int squareY,
                         Color activeColor, Board board) {
  int nextSquareX, nextSquareY;

  /* Bishop going North-East */
  nextSquareX = squareX + 1;
  nextSquareY = squareY + 1;
  while (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color == activeColor) {
      break;
    }
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
      if (board.square[nextSquareY][nextSquareX].color != neutral) {
        break;
      }
    } else {
      break;
    }
    ++nextSquareX;
    ++nextSquareY;
  }

  /* Bishop going South-East */
  nextSquareX = squareX + 1;
  nextSquareY = squareY - 1;
  while (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color == activeColor) {
      break;
    }
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
      if (board.square[nextSquareY][nextSquareX].color != neutral) {
        break;
      }
    } else {
      break;
    }
    ++nextSquareX;
    --nextSquareY;
  }

  /* Bishop going South-West */
  nextSquareX = squareX - 1;
  nextSquareY = squareY - 1;
  while (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color == activeColor) {
      break;
    }
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
      if (board.square[nextSquareY][nextSquareX].color != neutral) {
        break;
      }
    } else {
      break;
    }
    --nextSquareX;
    --nextSquareY;
  }

  /* Bishop going North-West */
  nextSquareX = squareX - 1;
  nextSquareY = squareY + 1;
  while (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color == activeColor) {
      break;
    }
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
      if (board.square[nextSquareY][nextSquareX].color != neutral) {
        break;
      }
    } else {
      break;
    }
    --nextSquareX;
    ++nextSquareY;
  }
}

/**
 *  @fn void rookMoveGenerator(Stack *moves, int squareX, int squareY,
 Color activeColor, Board board)
 *  @brief gives all moves for a rook sitting on a given square
 *  @param[in] squareX and squareY are the position of the bishop (7,7) system
 *              activeColor is the color of the rook
 *              board is the current board
 *
 *  This function gives all legal move for a colored rook except those linked
 *  with chess position
 *  (just waiting for the stack structure)
 */

void rookMoveGenerator(Stack *moves, int squareX, int squareY,
                       Color activeColor, Board board) {
  int nextSquareX, nextSquareY;

  /* Rook going North */
  nextSquareX = squareX;
  nextSquareY = squareY + 1;
  while (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color == activeColor) {
      break;
    }
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
      if (board.square[nextSquareY][nextSquareX].color != neutral) {
        break;
      }
    } else {
      break;
    }
    ++nextSquareY;
  }

  /* Rook going South */
  nextSquareX = squareX;
  nextSquareY = squareY - 1;
  while (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color == activeColor) {
      break;
    }
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
      if (board.square[nextSquareY][nextSquareX].color != neutral) {
        break;
      }
    } else {
      break;
    }
    --nextSquareY;
  }

  /* Rook going East */
  nextSquareX = squareX + 1;
  nextSquareY = squareY;
  while (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color == activeColor) {
      break;
    }
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
      if (board.square[nextSquareY][nextSquareX].color != neutral) {
        break;
      }
    } else {
      break;
    }
    ++nextSquareX;
  }

  /* Rook going West */
  nextSquareX = squareX - 1;
  nextSquareY = squareY;
  while (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color == activeColor) {
      break;
    }
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
      if (board.square[nextSquareY][nextSquareX].color != neutral) {
        break;
      }
    } else {
      break;
    }
    --nextSquareX;
  }
}

/**
 *  @fn void queenMoveGenerator(Stack *moves, int squareX, int squareY,
 Color activeColor, Board board)
 *  @brief gives all moves for a queen sitting on a given square
 *  @param[in] squareX and squareY are the position of the queen (7,7) system
 *              activeColor is the color of the queen
 *              board is the current board
 *
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
 Color activeColor, Board board)
 *  @brief gives all moves for a knight sitting on a given square
 *  @param[in] squareX and squareY are the position of the knight (7,7) system
 *              activeColor is the color of the knight
 *              board is the current board
 *
 *  This function gives legal move for a colored knight except those linked
 *  with chess position
 *  (just waiting for the stack structure)
 */
void knightMoveGenerator(Stack *moves, int squareX,
                         int squareY, Color activeColor, Board board) {
  int nextSquareX, nextSquareY;

  /* move : North then East
     | |F|  Finish
     | |
     |S|    Start */
  nextSquareX = squareX + 1;
  nextSquareY = squareY + 2;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* move : North then West
     |F| |  Finish
     | |
     |S|    Start */
  nextSquareX = squareX - 1;
  nextSquareY = squareY + 2;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* move : East then North
     |F|  Finish
     |S| | |  Start */
  nextSquareX = squareX + 2;
  nextSquareY = squareY + 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* move : East then South
     |S| | |  Start
     |F|  Finish */
  nextSquareX = squareX + 2;
  nextSquareY = squareY - 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* move : South then West
     |S|  Start
     | |
     |F| |  Finish */
  nextSquareX = squareX - 1;
  nextSquareY = squareY - 2;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* move : South then East
     |S|    Start
     | |
     | |F|  Finish */
  nextSquareX = squareX + 1;
  nextSquareY = squareY - 2;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* move : West then North
     |F|      Finish
     | | |S|  Start */
  nextSquareX = squareX - 2;
  nextSquareY = squareY + 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* move : West then South
     | | |S|  Start
     |F|      Finish */
  nextSquareX = squareX - 2;
  nextSquareY = squareY - 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
}

/**
 *  @fn void kingMoveGenerator(Stack *moves, int squareX, int squareY,
 Color activeColor, Board board)
 *  @brief gives all moves for a king sitting on a given square
 *  @param[in] squareX and squareY are the position of the king (7,7) system
 *              activeColor is the color of the king
 *              board is the current board
 *
 *  @note No chess position handling here !
 *  @note No castling handling yet !
 *
 *  This function gives legal move (except those linked with
 *  chess position for a colored king.
 *  (just waiting for the stack structure)
 */
void kingMoveGenerator(Stack *moves, int squareX,
                       int squareY, Color activeColor, Board board) {
  int nextSquareX, nextSquareY;

  /* To the North */
  nextSquareX = squareX;
  nextSquareY = squareY + 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* To the East */
  nextSquareX = squareX + 1;
  nextSquareY = squareY;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* To the South */
  nextSquareX = squareX;
  nextSquareY = squareY - 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* To the West */
  nextSquareX = squareX - 1;
  nextSquareY = squareY;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* To the North-East */
  nextSquareX = squareX + 1;
  nextSquareY = squareY + 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* To the South-East */
  nextSquareX = squareX + 1;
  nextSquareY = squareY - 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* To the South-West */
  nextSquareX = squareX - 1;
  nextSquareY = squareY - 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
  /* To the North-West */
  nextSquareX = squareX - 1;
  nextSquareY = squareY + 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareY][nextSquareX].color != activeColor) {
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }
}

/**
 *  @fn isInBoardSquare(int squareX, int squareY)
 *  @brief Test if the given square given with its coordinates is in the board
 *  @param[in] squareX and squareY are the coordinates of the square to test
 *  @param[out] true if the square is in false otherwise.
 */

bool isInBoardSquare(int squareX, int squareY) {
  return (squareX >= 0) && (squareX <= 7) && (squareY >= 0) && (squareY <= 7);
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
 *  @note function update_moves is recursive and called by update_board, and should never be
 *  used in another way
 *
 *  @todo Coord enPassant not updated currently need to correct that
 *
 */

void update_moves(Stack *s, Board *current){
  int current_move = stack_pop(s);
  int a, b, c, d;
  stack_revexchange(&a, &b, &c, &d, current_move);

  if (current_move != -1)
    update_moves(s, current);
  current->square[c][d] = current->square[a][b];
  current->square[a][b].color = neutral;
  current->square[a][b].piece = empty;
}
    

void update_board(Arc father, Graph *graph) {
  Stack stack;
  int tmp;
  int i;
  identifier_to_stack(father.data, &stack);
  update_moves(&stack, &(graph->current_node));
  graph->current_node.activeColor = !identifier_is_white(father.data);
  tmp = identifier_get_cast(father.data);
  for (i = 0; i<3; i++) {
    graph->current_node.availableCastlings[i] = tmp%2;
    tmp /=2;
  }
  graph->current_node.halfMoveClock = identifier_get_halfmove(father.data);
  graph->current_node.fullMoveNb = !identifier_get_fullmove(father.data);
}
