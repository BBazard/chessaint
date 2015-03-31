/* This file is part of the ChessAInt project 2015 */

#include "include/graph.h"
#include "include/chessboard.h"

int main(void) {
  printf("\n\n");
  printf("Welcome in ChessAint !\n");
  printf("**************************\n");
  int cur;


  while (1) {
    printf("\n\n");
    printf("---------------------------------------------\n");
    printf("- 1 to test fenToBoard with the beginning position \n");
    printf("- 2 to exit \n");
    printf("----------------------------------------------\n\n");

    scanf("%d", &cur);
    switch (cur) {
      case 1:
        /*a test with the FEN string describing the starting position*/
        fenToBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPP/RNBQKBNR w KQkq e4 0 1", &myGame);
        printBoardAndData(myGame);
        break;
      case 2:
        return EXIT_SUCCESS;
        break;
    }
  }

  return 0;
}

