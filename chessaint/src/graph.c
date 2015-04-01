/* This file is part of the ChessAInt project 2015 */
/** 
 *  @file graph.c
 *  @brief graph structure basic functions
 *
 *  This file implements functions to add or remove Arc from a linked list,
 *  totally suppress a list and print an Arc or a list
 *
 */

#include "include/graph.h"

#include <assert.h>
#include <string.h>



//With a game given, it will generate all next moves possible
Llist arcsGenerator(Graph graph, int id) {
  int i = 0;
  Llist rawArcs = NULL;

  for (i = 0 ; i <= 63 ; ++i) {
    if (graph.root.square[i].color == graph.root.activeColor) {
      switch (graph.root.square[i].piece) {
        case pawn:
          //pawnMoveGenerator(graph.root, id, &rawArcs);
          break;
        case bishop:
          break;
        case knight:
          break;
        case rook:
          break;
        case queen:
          break;
        case king:
          break;
        case empty:
         // we'll never happen bc activeColor will never be neutral
          break;
      }
    }
  }


  return rawArcs;
} 