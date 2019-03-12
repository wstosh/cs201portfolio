#include <stdio.h>
#include <stdlib.h>

void makeBoard(int rows, int cols) {
  int i, j, p, q;
  char matrix[rows][cols];
  for (i = 1; i <= rows; i++) {
    for (j = 1; j <= cols; j++) {
      matrix[i][j] = '*';
    }
  }
  for (i = 1; i <= rows; i++) {
    for (j = 1; j <= cols; j++) {
      printf("| %c ", matrix[i][j]);
    }
    printf("|\n");
    for (p = 1; p <= cols; p++) {
      printf("____");
    }
    printf("_");
    printf("\n");
  }
  for (q = 1; q <= cols; q++) {
    printf("  %d ", q);
  }
  printf("\n \n");
}

/*void PlayerVsPlayer(char** board, int rows, int cols) {
  int i = 0;
  int win = 0;
  for (i = 0; i < (rows * cols); i++) {
    if (i % 2 == 0) printf("Player 1, select a column number to place your piece.\n");
    else printf("Player 2, select a column number to place your piece.\n");
    scanf("%d", &move);
    while (move < 1 || move > cols) {
      printf("Select a valid column number\n");
      scanf("%d", &move);
      if (move > 0 && move <= cols) break;
    }




}
*/



int main() {
  int gameMode = 0;
  int gamesWonOne = 0;
  int gamesWonTwo = 0;
  int gamesWonPlayer = 0;
  int gamesWonComp = 0;
  int numRows = 0;
  int numCols = 0;

  printf("\n");
  printf("Hello. Select which game mode you would like to play.\n");
  printf("(Enter the integer value) \n \n");
  printf("(1) Player vs Player \n");
  printf("(2) Player vs Computer \n");
  scanf("%d", &gameMode);

  if (gameMode == 1) { // User selected Player vs Player game mode
    printf("\n");
    printf("You have selected the Player vs Player game mode.\n \n");
    printf("Enter the dimensions for your game.\n");
    printf("(An integer value greater or equal to 4)\n \n");
    printf("Rows: ");
    scanf("%d", &numRows);
    printf("\n");
    while (numRows < 4) {
      printf("Error: Enter a value greater than or equal to 4 \n");
      printf("Rows: ");
      scanf("%d", &numRows);
      if (numRows > 4) break;
    }
    printf("\n");
    printf("Columns: ");
    scanf("%d", &numCols);
    printf("\n");
    while (numCols < 4) {
      printf("Error: Enter a value greater than or equal to 4 \n");
      printf("Columns: ");
      scanf("%d", &numCols);
      if (numCols > 4) break;
    }
    printf("\n \n");
    printf("Enjoy your game! \n \n");
    printf("         SCOREBOARD         ");
    printf("\n \n");
    printf("PLAYER 1: %d || PLAYER 2: %d", gamesWonOne, gamesWonTwo);
    printf("\n");
    printf("__________________________");
    printf("\n \n");
    makeBoard(numRows, numCols);




  }

  if (gameMode == 2) { // User selected Player vs Computer game mode
    printf("\n");
    printf("You have selected the Player vs Computer game mode.\n \n");
    printf("Please select the dimensions for your game.\n");
    printf("(An integer value greater or equal to 4)\n \n");
    printf("Rows: ");
    scanf("%d", &numRows);
    printf("\n");
    while (numRows < 4) {
      printf("Error: Please enter a value greater than or equal to 4 \n");
      printf("Rows: ");
      scanf("%d", &numRows);
      if (numRows > 4) break;
    }
    printf("\n");
    printf("Columns: ");
    scanf("%d", &numCols);
    printf("\n");
    while (numCols < 4) {
      printf("Error: Please enter a value greater than or equal to 4 \n");
      printf("Columns: ");
      scanf("%d", &numCols);
      if (numCols > 4) break;
    }
    printf("\n \n");
    printf("Enjoy your game! \n \n");
    printf("        SCOREBOARD        ");
    printf("\n \n");
    printf("PLAYER: %d || COMPUTER: %d", gamesWonPlayer, gamesWonComp);
    printf("\n");
    printf("________________________");
    printf("\n \n");
    makeBoard(numRows, numCols);








  }










  return 0;
}
