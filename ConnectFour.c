#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

char playerOnePiece = 'O';
char playerTwoPiece = 'X';
char playerPiece = 'O';
char CompPiece = 'X';

void copyBoard(int rows, int cols, char** matrix, char** board) {
  int i, j;
  for (i = 1; i <= rows; i++) {
    for (j = 1; j <= cols; j++) {
      matrix[i][j] = board[i][j];
    }
  }
}

void placePiece(int row, int col, char piece, char** board) {
  board[row][col] = piece;
}

void makeBoard(int rows, int cols, char** matrix) { // Function creates 2d array and initializes indices with the character '*'
  int i, j;
  for (i = 1; i <= rows; i++) {
    for (j = 1; j <= cols; j++) {
      matrix[i][j] = '*';
    }
  }
}

void printBoard(int rows, int cols, char** board) { // Function prints out the existing board and separates indices with lines
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
  printf(" ");
  for (q = 1; q <= cols; q++) {
    if (q < 10) {
      printf(" %d  ", q);
    }
    else if (q > 9) {
      printf(" %d ", q);
    }
}
}

int checkVert(int rows, int cols, char** board, char piece) { // Function checks for vertical wins (Four-in-a-row)
  int i, j;
  for (i = 1; i <= rows - 3; i++) {
    for (j = 1; j <= cols; j++) {
      if (board[i][j] == piece && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j] && board[i][j] == board[i+3][j]) return 1;
    }
  }
  return 0;
}

int checkHor(int rows, int cols, char** board, char piece) { // Function checks for horizontal wins (Four-in-a-row)
  int i, j;
  for (i = 1; i <= rows; i++) {
    for (j = 1; j <= cols - 3; j++) {
      if (board[i][j] == piece && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2] && board[i][j] == board[i][j+3]) return 1;
    }
  }
  return 0;
}

int checkDiag(int rows, int cols, char** board, char piece) { // Function checks for diagonal wins (Four-in-a-row)
  int i, j;
  for (i = 1; i <= rows - 3; i++) { // Loops check for negatively sloped diagonal wins
    for (j = 1; j <= cols - 3; j++) {
      if (board[i][j] == piece && board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2] && board[i][j] == board[i+3][j+3]) return 1;
    }
  }

  for (i = rows; i > 3; i--) { // Loops check for positively sloped diagonal wins
    for (j = 1; j <= cols - 3; j++) {
      if (board[i][j] == piece && board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2] && board[i][j] == board[i-3][j+3]) return 1;
    }
  }

return 0;
}

int checkWin(int rows, int cols, char** board, char piece) { // Function utilizes the three functions checkVert, checkHor, and checkDiag
                                                             // in order to check for an overall win
  int winVert = 0;
  int winHor = 0;
  int winDiag = 0;

  winVert = checkVert(rows, cols, board, piece);
  winHor = checkHor(rows, cols, board, piece);
  winDiag = checkDiag(rows, cols, board, piece);

  if (winVert == 1 || winHor == 1 || winDiag == 1) return 1;

  return 0;
}

int gameOver(int rows, int cols, char** board) {
  int gamePlayer = 0;
  int gameComp = 0;
  int count = 0;
  int check = 0;
  int i = 0;
  int j = 0;

  gamePlayer = checkWin(rows, cols, board, playerPiece);
  gameComp = checkWin(rows, cols, board, CompPiece);

  for (i = 1; i < 2; i++) {
    for (j = 1; j < cols; j++) {
      if (board[i][j] != '*') count++;
    }
  }
  if (count == cols) check++;
  if (gamePlayer == 1 || gameComp == 1 || check == 1) return 1;
  return 0;
}

int validLocation(int move, int cols, char** board) { // Function checks to see if player move is a valid one
  if (board[1][move] == '*') return 1;                // Is top row still empty?
  if (move < 1 || move > cols) return 2;              // Out of bounds check

  return 2;

}

int nextOpenRow(int move, int rows, char** board) { // Function finds next open row in specified column
  int j = rows;
  while (board[j][move] != '*') {
    j--;
  }
  return j;
}

int whichIndex(char window[]) {
  int countComp = 0;
  int countPlayer = 0;
  int countOpen = 0;
  int i = 0;

  for (i = 0; i < 4; i++) {
    if ((window[i] != 'O') || (window[i] != 'X')) countOpen++;
  }

  for (i = 0; i < 4; i++) {
    if (window[i] == playerPiece) countPlayer++;
  }

  for (i = 0; i < 4; i++) {
    if (window[i] == CompPiece) countComp++;
  }

  if ((countComp == 3) && (countOpen == 1)) {
    for (i = 0; i < 4; i++) {
      if (window[i] == '*') {
        return i+1;
      }
    }
  }

  else if ((countPlayer == 3) && (countOpen == 1)) {
    for (i = 0; i < 4; i++) {
      if (window[i] == '*') {
        return i+1;
      }
    }
  }

  if ((countComp == 2) && (countOpen == 2)) {
    for (i = 0; i < 4; i++) {
      if (window[i] == '*') {
        return i+1;
      }
    }
  }



  return 0;
}

int bestMove(int rows, int cols, char** board) {
  int index = -1;                                                     // Function looks at windows of four spots at each board position in a game
  int columnH = 0;
  int columnV = 0;
  int columnPD = 0;
  int columnND = 0;                                                             // (Horizontally, Vertically, Diagonally)
  int randCol = ((rand() % cols) + 1);                                          // Ultimately, a score is made by sending the windows of four to the scoreAdded function
  char rowArr[cols];
  char colArr[rows];
  char window[4];
  int i = 0;
  int j = 0;
  int p = 0;
  int c = 0;
  int x = 0;
  int t = 0;

  for (i = 1; i <= rows; i++) { // Horizontal Score Count
    for (j = 1; j <= cols; j++) {
      rowArr[i-1] = board[i][j];
    }
      for (p = 0; p < cols - 3; p++) {
        x = 0;
        for (c = p; c < p + 4; c++) {
          window[x] = rowArr[c];
          x++;
        }

        index = whichIndex(window);
        index -= 1;
        if (index >= 0) {
        columnH = j + index;
      }
        if ((columnH > 0) && (columnH <= cols)) break;
      }
      if ((columnH > 0) && (columnH <= cols)) break;
    }


  for (i = 1; i <= cols; i++) { // Vertical Score Count
    for (j = 1; j <= rows; j++) {
      colArr[i-1] = board[j][i];
    }
      for (p = 0; p < rows - 3; p++) {
        x = 0;
        for (c = p; c < p + 4; c++) {
          window[x] = colArr[c];
          x++;
        }
        index = whichIndex(window);
        index -= 1;
        if (index >= 0) {
          columnV = i;
        }
        if ((columnV > 0) && (columnV <= cols)) break;
      }
      if ((columnV > 0) && (columnV <= cols)) break;
  }

  for (i = 1; i <= rows - 3; i++) { // Negatively Sloped Score Count
    for (j = 1; j <= cols - 3; j++) {
      x = 0;
      for (t = 0; t < 4; t++) {
      window[x] = board[i+t][j+t];
      x++;
      }
      index = whichIndex(window);
      index -= 1;
      if (index >= 0) {
      columnH = j + index;
    }
      if ((columnND > 0) && (columnND <= cols)) break;
    }
    if ((columnND > 0) && (columnND <= cols)) break;
  }

  for (i = 1; i <= rows - 3; i++) { // Positively Sloped Score Count
    for (j = 1; j <= cols - 3; j++) {
      x = 0;
      for (t = 0; t < 4; t++) {
      window[x] = board[i+3-t][j+t];
      x++;
      }
      index = whichIndex(window);
      index -= 1;
      if (index >= 0) {
      columnH = j + index;
    }
      if ((columnPD > 0) && (columnPD <= cols)) break;
    }
    if ((columnPD > 0) && (columnPD <= cols)) break;
  }

  if (columnH > 0 && columnH <= cols) return columnH;
  else if (columnV > 0 && columnV <= cols) return columnV;
  else if (columnND > 0 && columnND <= cols) return columnND;
  else if (columnPD > 0 && columnPD <= cols) return columnPD;
  else return randCol;
}

/*
int* miniMax(char** board, int rows, int cols, int distance, bool maximizingPlayer) {  // https://github.com/KeithGalli/Connect4-Python/blob/master/connect4_with_ai.py
                                                                                        // Recursive function that assigns heuristic values to leaf nodes
  int gamePlayer = 0;
  int gameComp = 0;
  int game = 0;
  long value = 0;
  int column = 0;
  int row = 0;
  int score = 0;
  int i = 0;
  int t = 0;
  static int arr[2];
  int *ptr;

  char **matrix = (char **)malloc((rows + 1) * sizeof(char *));
  for (t = 1; t <= rows; t++) {
    matrix[t] = (char *)malloc((cols + 1) * sizeof(char));
  }

  game = gameOver(rows, cols, board);
  gamePlayer = checkWin(rows, cols, board, playerPiece);
  gameComp = checkWin(rows, cols, board, CompPiece);

  if (distance == 0 || game == 1) {
    if (game == 1) {
      if (gameComp == 1) {
        arr[1] = 1000000;
        return arr;
      }
      else if (gamePlayer == 1) {
        arr[1] = -1000000;
        return arr;
      }
      else {
        arr[1] = 0;
        return arr;
      }
    }
    else {
      arr[1] = boardScore(rows, cols, board, CompPiece);
      return arr;
    }
  }

  if (maximizingPlayer == true) {
    value = LONG_MIN;
    for (i = 1; i <= cols; i++) { // loop that iterates through all valid columns
      if ((board[1][i]) == '*') {
        row = nextOpenRow(i, rows, board);
        copyBoard(rows, cols, matrix, board);
        placePiece(row, i, CompPiece, matrix);
        ptr = miniMax(matrix, rows, cols, distance - 1, false);
        score = *ptr;
        if (score > value) {
          value = score;
          column = i;
          arr[0] = column;
          arr[1] = value;
        }
      }
    }
    return arr;
  }

  else { //Minimizing Player
    value = LONG_MAX;
    for (i = 1; i <= cols; i++) { // loop that iterates through all valid columns
      if ((board[1][i]) == '*') {
        row = nextOpenRow(i, rows, board);
        copyBoard(rows, cols, matrix, board);
        placePiece(row, i, playerPiece, matrix);
        ptr = miniMax(matrix, rows, cols, distance - 1, true);
        printf("before: %d\n", score);
        score = *ptr;
        printf("after: %d\n", score);
        if (score < value) {
          value = score;
          column = i;
          arr[0] = column;
          arr[1] = value;
        }
      }
    }
    return arr;
  }
}

*/
void ComputerGameplay(int rows, int cols, char** board) { // Function that controls the computers gameplay
  int column = 0;
  int row = 0;
                                                          // Ultimately places a piece in the best spot
  column = bestMove(rows, cols, board);
  row = nextOpenRow(column, rows, board);
  placePiece(row, column, CompPiece, board);

}

int PlayerVsPlayer(int rows, int cols, char** board) { // Function that controls the Player vs Player gameplay
  int i = 0;                                           // Ultimately returns an integer value that corresponds to the winning player
  int move = 0;
  int valid = 0;
  int winPlayerOne = 0;
  int winPlayerTwo = 0;

  printf("\n");

  for (i = 0; i < (rows * cols); i++) { // Loop will iterate until the longest possible game is played (a tie)
    int j = rows;
    if (i % 2 == 0) printf("Player 1, select a column number to place your piece: ");
    else printf("Player 2, select a column number to place your piece: ");
    scanf("%d", &move);
    valid = validLocation(move, cols, board);
    printf("\n");

    while (valid == 2) { // Loop executes if user selects an invalid location
      printf("Select a valid location: ");
      scanf("%d", &move);
      valid = validLocation(move, cols, board);
    }

    while (board[j][move] != '*') {
      j--;
    }

    if (i % 2 == 0) board[j][move] = playerOnePiece;
    else board[j][move] = playerTwoPiece;

    printf("\n\n");

    printBoard(rows, cols, board);
    printf("\n\n");

    winPlayerOne = checkWin(rows, cols, board, playerOnePiece);
    winPlayerTwo = checkWin(rows, cols, board, playerTwoPiece);

    if (winPlayerOne == 1) {
      printf("Player 1 has won the game!\n");
      return 1;
    }

    else if (winPlayerTwo == 1) {
        printf("Player 2 has won the game!\n");
        return 2;
    }

  }

return 0;

}

int PlayerVsComputer(int rows, int cols, char** board) { // Function that controls the Player vs Computer gameplay
  int i = 0;                                             // Ultimately returns an integer value that corresponds to the winning player
  int j = 0;
  int move = 0;
  int valid = 0;
  int winPlayer = 0;
  int winComp = 0;

  printf("\n");

  for (i = 0; i < (rows * cols); i++) { // Loop will iterate until the longest possible game is played (a tie)
    j = rows;

    if (i % 2 == 0) {
      printf("Select a column number to place your piece: ");
      scanf("%d", &move);
      valid = validLocation(move, cols, board);
      printf("\n");

      while (valid == 2) {  // Loop executes if user selects an invalid location
        printf("Select a valid location: ");
        scanf("%d", &move);
        valid = validLocation(move, cols, board);
      }

      while (board[j][move] != '*') {
        j--;
      }

      board[j][move] = playerPiece;


    }

    else {
      ComputerGameplay(rows, cols, board);
    }

    printf("\n\n");
    printBoard(rows, cols, board);
    printf("\n\n");

    winPlayer = checkWin(rows, cols, board, playerPiece);
    winComp = checkWin(rows, cols, board, CompPiece);

    if (winPlayer == 1) {
      printf("You have won the game!\n");
      return 1;
    }

    else if (winComp == 1) {
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

  while ((gameMode < 1) || (gameMode > 2)) {
    printf("Error: Enter a valid option: ");
    scanf("%d", &gameMode);
    if ((gameMode > 0) && (gameMode < 3)) break;
  }

while (game == 0) {

  if (gameMode == 1) { // User selected Player vs Player game mode
    printf("\n \n");
    printf("You have selected the Player vs Player game mode.\n \n");
    printf("Enter the dimensions for your game.\n");
    printf("(An integer value greater or equal to 4)\n");
    printf("Entering large values (e.g. 40) may worsen the gameplay.\n \n");
    printf("Rows: ");
    scanf("%d", &numRows);
    printf("\n");
    while (numRows < 4) { // Loop executes when user enters a number less than 4 (rows)
      printf("Error: Enter a value greater than or equal to 4 \n");
      printf("Rows: ");
      scanf("%d", &numRows);
      if (numRows > 4) break;
    }
    printf("\n");
    printf("Columns: ");
    scanf("%d", &numCols);
    printf("\n");
    while (numCols < 4) { // Loop executes when user enters a number less than 4 (columns)
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
    char **matrix = (char**)malloc((numRows + 1) * sizeof(char *));
    for (t = 1; t <= numRows; t++) {
      matrix[t] = (char*)malloc((numCols + 1) * sizeof(char));
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

    while ((decision < 1) || (decision > 2)) {
      printf("Error: Enter a valid option: ");
      scanf("%d", &decision);
      if ((decision > 0) && (decision < 3)) break;
    }

    if (decision == 2) {
      game = 1;
    }

  }

  if (gameMode == 2) { // User selected Player vs Computer game mode
    printf("\n \n");
    printf("You have selected the Player vs Computer game mode.\n \n");
    printf("Please select the dimensions for your game.\n");
    printf("(An integer value greater or equal to 4)\n");
    printf("Entering large values (e.g. 40) may worsen the gameplay.\n\n");
    printf("Rows: ");
    scanf("%d", &numRows);
    printf("\n");
    while (numRows < 4) { // Loop executes when user enters a number less than 4 (rows)
      printf("Error: Please enter a value greater than or equal to 4 \n");
      printf("Rows: ");
      scanf("%d", &numRows);
      if (numRows > 4) break;
    }
    printf("\n");
    printf("Columns: ");
    scanf("%d", &numCols);
    printf("\n");
    while (numCols < 4) { // Loop executes when user enters a number less than 4 (columns)
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
    char **matrix = (char **)malloc((numRows + 1) * sizeof(char *));
    for (t = 1; t <= numRows; t++) {
      matrix[t] = (char *)malloc((numCols + 1) * sizeof(char));
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

    while ((decision < 1) || (decision > 2)) {
      printf("Error: Enter a valid option: ");
      scanf("%d", &decision);
      if ((decision > 0) && (decision < 3)) break;
    }


    if (decision == 2) {
      game = 1;
    }

}
}

printf("Have a nice day!\n");

  return 0;
}
