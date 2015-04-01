/* This file is part of the ChessAInt project 2015 */
/** 
 *  @file graph.h
 *  @brief graph structure header
 *
 *  This file implements enumerations and structures for the graph item and 
 *  the prototype of the functions developped in graph.c file
 *
 */

#ifndef TRUNK_CHESSAINT_INCLUDE_GRAPH_H_
#define TRUNK_CHESSAINT_INCLUDE_GRAPH_H_


#include "chessboard.h"
#include "llist.h"



typedef struct Graph Graph;

/** 
 *  @struct Graph
 *  @brief Represents a graph for astar computation
 *
 *  Stores the graph data
 */

struct Graph {
  Board root;
  Board current_node;
  Llist links;
};

Llist arcsGenerator(Graph graph, int id);



#endif /*TRUNK_CHESSAINT_INCLUDE_GRAPH_H_*/
