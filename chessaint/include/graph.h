#include <stdlib.h>
#include <stdio.h>

enum Set {none, open, closed};
enum Color {white, black};

typedef struct arc {int id; char* from; char* to; int score; enum Set whichSet; enum Color whoPlays;} Arc;

typedef struct element {Arc value; struct element *next;} Element; 
typedef Element *Llist;

void llist_add (Arc newvalue, Llist *list);
Arc llist_suppr (Llist *list);
void llist_free (Llist *list);
void llist_value_print (Arc value);

void arc_print (Arc value);
void llist_print (Llist list);
