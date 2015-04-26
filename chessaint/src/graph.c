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

  for (j = 0 ; j <= ROWCOL_NB - 1 ; ++j) {
    for (i = 0 ; i <= ROWCOL_NB - 1 ; ++i) {
      if (graph->current_node.square[i][j].color ==
          graph->current_node.activeColor) {
        switch (graph->current_node.square[i][j].piece) {
        case pawn:
          pawnMoveGenerator(&(graph->current_moves), i, j,
                            graph->current_node.activeColor,
                            graph->current_node);
          break;
        case bishop:
          bishopMoveGenerator(&(graph->current_moves), i, j,
                              graph->current_node.activeColor,
                              graph->current_node);
          break;
        case knight:
          knightMoveGenerator(&(graph->current_moves), i, j,
                              graph->current_node.activeColor,
                              graph->current_node);
          break;
        case rook:
          rookMoveGenerator(&(graph->current_moves), i,  j,
                            graph->current_node.activeColor,
                            graph->current_node);
          break;
        case queen:
          queenMoveGenerator(&(graph->current_moves), i, j,
                             graph->current_node.activeColor,
                             graph->current_node);
          break;
        case king:
          kingMoveGenerator(&(graph->current_moves), i,  j,
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
    if (board.square[nextSquareX][nextSquareY].color == neutral) {
    /*
      printf("(%d,%d)->(%d,%d)\n",squareX,squareY,nextSquareX,nextSquareY);
    */
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }

  /* The classic capture of pieces towards left of the board */
  nextSquareX = squareX + 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if ((board.square[nextSquareX][nextSquareY].color != neutral) &&
        (board.square[nextSquareX][nextSquareY].color != activeColor)) {
   /*
      printf("(%d,%d)->(%d,%d)\n",squareX,squareY,nextSquareX,nextSquareY);
  */
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }

  /* The classic capture of pieces towards right of the board */
  nextSquareX = squareX - 1;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if ((board.square[nextSquareX][nextSquareY].color != neutral) &&
        (board.square[nextSquareX][nextSquareY].color != activeColor)) {
 /*
      printf("(%d,%d)->(%d,%d)\n",squareX,squareY,nextSquareX,nextSquareY);
*/
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
    /*
      printf("(%d,%d)->(%d,%d)\n",squareX,squareY,nextSquareX,nextSquareY);
    */
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
    nextSquareX = squareX - 1;
    if ((nextSquareY == board.enPassant.line) &&
        (nextSquareX == board.enPassant.column)) {
    /*
      printf("(%d,%d)->(%d,%d)\n",squareX,squareY,nextSquareX,nextSquareY);
    */
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
    }
  }


  /* Pawn moving 2 squares UP only from 2th row for white and 7th for black */
  whiteMove = 1;
  blackMove = -1;
  if (
      ((activeColor == white) &&
       (board.square[squareX][squareY + 1 * whiteMove].color == neutral) &&
       (board.square[squareX][squareY + 2 * whiteMove].color != activeColor) &&
       (squareY == 1)) ||
      ((activeColor == black) &&
       (board.square[squareX][squareY + 1 * blackMove].color == neutral) &&
       (board.square[squareX][squareY + 2 * blackMove].color != activeColor) &&
       (squareY == 6))
      ) {
    if (activeColor == white) {
     /* 
      printf("(%d,%d)->(%d,%d)\n",squareX, 1, squareX,
                                       squareY + 2 * whiteMove);
      */
      stack_push(moves, stack_exchange(squareX, 1, squareX,
                                       squareY + 2 * whiteMove));
    } else {
      /*
      printf("(%d,%d)->(%d,%d)\n",squareX, 1, squareX,
                                       squareY + 2 * whiteMove);
      */
      stack_push(moves, stack_exchange(squareX, 6, squareX,
                                       squareY + 2 * blackMove));
    }
  }
}

/**
 *  @fn void bishopMoveGenerator(Stack *moves, int squareX, int squareY,
 Color activeColor, Board board)
 *  @brief gives all moves for a bishop sitting on a given square by calling
           dedicated subfonctions
 *  @param[in] squareX and squareY are the position of the bishop (7,7) system
 *              activeColor is the color of the bishop
 *              board is the current board
 *  @param[in, out] Stack *moves is a stack that keep track of the results
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
 *  @param[in] squareX and squareY are the position of the bishop (7,7) system
 *              activeColor is the color of the bishop
 *              board is the current board
 *  @param[in, out] Stack *moves is a stack that keep track of the results
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
 *  @param[in] squareX and squareY are the position of the bishop or
 *                rook (7,7) system
 *              activeColor is the color of the bishop
 *              board is the current board
 *               incX and incY determines the directions we wanna move
 *  @param[in, out] Stack *moves is a stack that keep track of the results
 *
 *
 *  This function gives all legal move for a colored bishop or rook except
 *  those linked with chess position
 */

void bishopAndRook4DirectionsGen(int incX, int incY, Stack *moves, int squareX,
                          int squareY, Color activeColor, Board board) {
  int nextSquareX;
  int nextSquareY;

  nextSquareX = squareX + incX;
  nextSquareY = squareY + incY;
  while (isInBoardSquare(nextSquareX, nextSquareY)) {
    /* printf("\n------------\n");
    printf("Next move :\n");
    printf("activeColor : %d\n", activeColor );
    printf("dest color : %d\n", board.square[nextSquareY][nextSquareX].color);
    */
    if (board.square[nextSquareX][nextSquareY].color == activeColor) {
      break;
    }
    if (board.square[nextSquareX][nextSquareY].color != activeColor) {
      /* Enable to see moves 
      printf("(%d,%d)->(%d,%d)\n",squareX,squareY,nextSquareX,nextSquareY);*/
      stack_push(moves, stack_exchange(squareX, squareY,
                                       nextSquareX, nextSquareY));
      if (board.square[nextSquareX][nextSquareY].color != neutral) {
        break;
      }
    } else {
      break;
    }
    nextSquareX += incX;
    nextSquareY += incY;
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
 *      Color activeColor, Board board)
 *  @brief gives all moves for a knight sitting on a given square by calling
 *          subfunctions
 *  @param[in] squareX and squareY are the position of the knight (7,7) system
 *              activeColor is the color of the knight
 *              board is the current board
 *  @param[in, out] a stack of moves to keep track of moves
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
 *  @param[in] squareX and squareY are the position of the king (7,7) system
 *              activeColor is the color of the king
 *              board is the current board
 *  @param[in, out] a stack of moves to keep track of moves
 *
 *  @note No chess position handling here !
 *  @note No castling handling yet !
 *
 */
void kingMoveGenerator(Stack *moves, int squareX,
                       int squareY, Color activeColor, Board board) {
  int i;
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

  for (i = 0 ; i < 4 ; ++i) {
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
 *  @param[in] sqaureX original position of the king who wanna castle
 *  @param[in] sqaureY original position of the king who wanna castle
 *  @param[in, out] Stack *moves is a stack that keep track of the results
 *  @param[in] board is the board of the game 
 */
void castlesMoveGenerator(int incX, int squareX, int squareY, Stack *moves,
                           Board board) {
  int nextSquareX;
  bool canCastle = true;
  int testSquare = squareX;
  nextSquareX = 2 * incX + squareX;

  if (incX < 0) {
    if (board.square[1][squareY].color != neutral)
      canCastle = false;
  }  
  
  do {
    testSquare += incX;
    if(board.square[testSquare][squareY].color != neutral) {
      canCastle = false;
    }
  } while(testSquare != nextSquareX);

  if (canCastle) {
    printf("(%d,%d)->(%d,%d)\n", squareX, squareY, nextSquareX, squareY); 
  }  
}
/**
 *  @fn void knightAndKing4DirectionsGen(int incX, int incY, Stack *moves,
 *                  int squareX, int squareY, Color activeColor, Board board)
 *  @brief the subfonctions dealing with the 4 directions of movement
 *  @param[in] squareX and squareY are the position of the knight or king
 *              activeColor is the color of the bishop
 *              board is the current board
 *               incX and incY determines the directions we wanna move
 *  @param[in, out] Stack *moves is a stack that keep track of the results
 *
 *
 *  This function gives all legal move for a colored knight or king except
 *  those linked with chess position
 */
void knightAndKing4DirectionsGen(int incX, int incY, Stack *moves, int squareX,
                          int squareY, Color activeColor, Board board) {
  int nextSquareX, nextSquareY;

  nextSquareX = squareX + incX;
  nextSquareY = squareY + incY;
  if (isInBoardSquare(nextSquareX, nextSquareY)) {
    if (board.square[nextSquareX][nextSquareY].color != activeColor) {
      /* Enable to see moves :
      printf("(%d,%d)->(%d,%d)\n",squareX,squareY,nextSquareX,nextSquareY);
      */
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
 *  @fn void play_move(int move, Board *board)
 *  @brief play a move on a board
 *  @param[in] move the move to play, Ex : 4143 pour e2e4
 *  @param[in,out] board the board on which to play the move
 *
 */

void play_move(int move, Board *board) {
  int a, b, c, d;
  stack_revexchange(&a, &b, &c, &d, move);

  board->square[c][d] = board->square[a][b];
  board->square[a][b].color = neutral;
  board->square[a][b].piece = empty;
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

void update_moves(Stack *s, Board *current) {
  int current_move = stack_pop(s);

  if (current_move != -1) {
    update_moves(s, current);
    play_move(current_move, current);
  }
}

void update_board(Arc father, Graph *graph) {
  Stack stack;
  int tmp;
  int i;
  identifier_to_stack(father.data, &stack);
  update_moves(&stack, &(graph->current_node));
  graph->current_node.activeColor = !identifier_is_white(father.data);
  tmp = identifier_get_cast(father.data);
  for (i = 0; i < 3; i++) {
    graph->current_node.availableCastlings[i] = tmp%2;
    tmp /=2;
  }
  graph->current_node.halfMoveClock = identifier_get_halfmove(father.data);
  graph->current_node.fullMoveNb = identifier_get_fullmove(father.data);
}
