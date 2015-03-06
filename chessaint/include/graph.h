/** 
 *  @file graph.h
 *  @brief graph structure header
 *  @author ALescouet
 *  @version 1.0
 *  @date 6 March 2015
 *
 * This file implements enumerations and structures for the graph item and the prototype of the functions developped in graph.c file
 *
 */

#include <stdlib.h>
#include <stdio.h>

/** 
 *  @enum Set
 *  @brief Which set belongs the item
 *  
 *  This enumeration represents the set in which is the item for astar calculation
 *  
 */

enum Set {
  none, /**< Not belonging to any set */
  open, /**< Belongs to open set */
  closed /**< Belongs to closed set */
};

/** 
 *  @enum Color
 *  @brief Which turn belongs the item
 *  
 *  This enumeration represents which player played this move.
 *
 */

enum Color {
  white, /**< Played during the white's turn */ 
  black /**< Played during the black's turn */
};

/** 
 *  @struct Arc
 *  @brief Represents the arc between two nodes of a graph
 *
 */

typedef struct Arc Arc;
struct Arc {
  int id; /**< The id of the arc */
  char* from; /**< from  */
  char* to; /**< to */
  int score; /**< The cumulated score of the move */
  enum Set whichSet; /**< The set in which is the arc for the astar calculation */
  enum Color whoPlays; /**< The player by whom was played the move */
};

/** 
 *  @struct Element
 *  @brief Definition of an list element
 *
 */

typedef struct Element Element;
struct Element {
  Arc value; /**< The value of the element, an arc */
  struct element *next; /**< The link to the next element of the list */
}; 

typedef Element *Llist;

void llist_add (Arc newvalue, Llist *list);
Arc llist_suppr (Llist *list);
void llist_free (Llist *list);
void llist_value_print (Arc value);

void arc_print (Arc value);
void llist_print (Llist list);
