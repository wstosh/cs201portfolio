#include <stdio.h>
#include <stdlib.h>

void makeBoard(int rows, int cols, char** matrix) {
  int i, j;
  for (i = 1; i <= rows; i++) {
    for (j = 1; j <= cols; j++) {
      matrix[i][j] = '*';
    }
  }
}

void printBoard(int rows, int cols, char** board) {
  int i, j, p, q;
  for (i = 1; i <= rows; i++) {
    for (j = 1; j <= cols; j++) {
      printf("| %c ", board[i][j]);
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
}

int checkVert(int rows, int cols, char** board) {
  int i, j;
  for (i = 1; i <= rows - 3; i++) {
    for (j = 1; j <= cols; j++) {
      if (board[i][j] != '*' && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j] && board[i][j] == board[i+3][j]) return 1;
    }
  }
  return 0;
}

int checkHor(int rows, int cols, char** board) {
  int i, j;
  for (i = 1; i <= rows; i++) {
    for (j = 1; j <= cols - 3; j++) {
      if (board[i][j] != '*' && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2] && board[i][j] == board[i][j+3]) return 1;
    }
  }
  return 0;
}

int checkDiag(int rows, int cols, char** board) {
  int i, j;
  for (i = 1; i <= rows - 3; i++) {
    for (j = 1; j <= cols - 3; j++) {
      if (board[i][j] != '*' && board[i][j] == board[i+1][j-1] && board[i][j] == board[i+2][j-2] && board[i][j] == board[i+3][j-3]) return 1;
    }
  }

  for (i = 1; i <= rows - 3; i++) {
    for (j = 1; j <= cols - 3; j++) {
      if (board[i][j] != '*' && board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2] && board[i][j] == board[i+3][j+3]) return 1;
    }
  }

return 0;
}

int checkWin(int rows, int cols, char** board) {
  int winVert = 0;
  int winHor = 0;
  int winDiag = 0;

  winVert = checkVert(rows, cols, board);
  winHor = checkHor(rows, cols, board);
  winDiag = checkDiag(rows, cols, board);

  if (winVert == 1 || winHor == 1 || winDiag == 1) return 1;

  return 0;
}

int validLocation(int move, int cols, char** board) {
  if (board[1][move] == '*') return 1;
  if (move < 1 || move > cols) return 2;

  return 2;

}

void ComputerGameplay(int rows, int cols, char** board) {






}

int PlayerVsPlayer(int rows, int cols, char** board) {
  int i = 0;
  int win = 0;
  int move = 0;
  int valid = 0;

  for (i = 0; i < (rows * cols); i++) {
    int j = rows;
    if (i % 2 == 0) printf("Player 1, select a column number to place your piece: ");
    else printf("Player 2, select a column number to place your piece: ");
    scanf("%d", &move);
    valid = validLocation(move, cols, board);
    printf("\n");

    while (valid == 2) {
      printf("Select a valid location: ");
      scanf("%d", &move);
      valid = validLocation(move, cols, board);
    }

    while (board[j][move] != '*') {
      j--;
    }

    if (i % 2 == 0) board[j][move] = 'O';
    else board[j][move] = 'X';

    printf("\n\n");

    printBoard(rows, cols, board);
    printf("\n\n");

    win = checkWin(rows, cols, board);

    if (win == 1 && (i % 2 == 0)) {
      printf("Player 1 has won the game!\n");
      return 1;
    }
    else if (win == 1 && (i % 2 == 1)) {
        printf("Player 2 has won the game!\n");
        return 2;
    }

  }

return 0;

}

int PlayerVsComputer(int rows, int cols, char** board) {
  int i = 0;
  int j = 0;
  int move = 0;
  int valid = 0;

  for (i = 0; i < (rows * cols); i++) {
    j = rows;

    if (i % 2 == 0) {
      printf("Select a column number to place your piece: ");
      scanf("%d", &move);
      valid = validLocation(move, cols, board);
      printf("\n");

      while (valid == 2) {
        printf("Select a valid location: ");
        scanf("%d", &move);
        valid = validLocation(move, cols, board);
      }

      while (board[j][move] != '*') {
        j--;
      }

      board[j][move] == 'O';

    }

    else {
      ComputerGameplay(rows, cols, board);
    }

    printf("\n\n");
    printBoard(rows, cols, board);
    printf("\n\n");

    win = checkWin(rows, cols, board);

    if (win == 1 && (i % 2 == 0)) {
      printf("You have won the game!\n");
      return 1;
    }
    else if (win == 1 && (i % 2 == 1)) {
        printf("The computer has won the game!\n");
        return 2;
    }

  }

return 0;

}

int main() {
  int gameMode = 0;
  int gamesWonOne = 0;
  int gamesWonTwo = 0;
  int gamesWonPlayer = 0;
  int gamesWonComp = 0;
  int numRows = 0;
  int numCols = 0;
  int whoWon = 0;
  int game = 0;
  int decision = 0;
  int t = 0;

  printf("\n");
  printf("Hello. Select which game mode you would like to play.\n");
  printf("(Enter the integer value) \n \n");
  printf("(1) Player vs Player \n");
  printf("(2) Player vs Computer \n");
  scanf("%d", &gameMode);

  while (gameMode != 1 && gameMode != 2) {
    printf("Error: Enter a valid option\n");
    scanf("%d", &gameMode);
    if (gameMode == 1 || gameMode == 2) break;
  }

while (game == 0) {

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
    char **matrix = (char**)malloc(numRows * sizeof(char *));
    for (t = 1; t <= numRows; t++) {
      matrix[t] = (char*)malloc(numCols * sizeof(char));
    }
    makeBoard(numRows, numCols, matrix);
    printBoard(numRows, numCols, matrix);
    whoWon = PlayerVsPlayer(numRows, numCols, matrix);
    if (whoWon == 0) printf("It is a tie!\n\n");
    if (whoWon == 1) gamesWonOne++;
    if (whoWon == 2) gamesWonTwo++;

    printf("Options:\n");
    printf("(1) Play another game.\n");
    printf("(2) Exit.\n");
    printf("(Enter the integer value)\n\n");
    scanf("%d", &decision);

    if (decision == 2) game++;

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
    char **matrix = (char **)malloc(numRows * sizeof(char *));
    for (t = 1; t <= numRows; t++) {
      matrix[t] = (char *)malloc(numCols * sizeof(char));
    }
    makeBoard(numRows, numCols, matrix);
    printBoard(numRows, numCols, matrix);
    whoWon = PlayerVsComputer(numRows, numCols, matrix);
    if (whoWon == 0) printf("It is a tie!\n\n");
    if (whoWon == 1) gamesWonPlayer++;
    if (whoWon == 2) gamesWonComp++;

    printf("Options:\n");
    printf("(1) Play another game.\n");
    printf("(2) Exit.\n");
    printf("(Enter the integer value)\n\n");
    scanf("%d", &decision);

    if (decision == 2) game++;

  }

}

printf("Have a nice day!\n");

  return 0;
}
