#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BOARD_ROWS = 6;
const int BOARD_COLS = 7;

void printBoard(char *board);
int takeTurn(char *board, int player, const char *PIECES);
int checkWin(char *board);
int checkFour(char *board, int a, int b, int c, int d);
int horizontalCheck(char *board);
int verticalCheck(char *board);
int diagonalCheck(char *board);
void clearScreen();
void waitForEnter();

int main(int argc, char *argv[])
{
   const char *PIECES = "XO";
   char board[BOARD_ROWS * BOARD_COLS];
   memset(board, ' ', BOARD_ROWS * BOARD_COLS);

   int turn, done = 0;

   for(turn = 0; turn < BOARD_ROWS * BOARD_COLS && !done; turn++){
      printBoard(board);   
      while(!takeTurn(board, turn % 2, PIECES)){
         printBoard(board);   
         printf("**Column full!**\n\n");
      }
      done = checkWin(board);
   } 
   printBoard(board);

   if(turn == BOARD_ROWS * BOARD_COLS && !done){
      printf("It's a tie!\n");
   } else {
      turn--;
      printf("Player %d (%c) wins!\n", turn % 2 + 1, PIECES[turn % 2]);
   }

   return 0;

}

void printBoard(char *board)
{
   int row, col;

   clearScreen();
   printf("\n    ****Connect Four****\n\n");
   for(row = 0; row < BOARD_ROWS; ++row){
      for(col = 0; col < BOARD_COLS; ++col){
         printf("| %c ",  board[BOARD_COLS * row + col]);
      }
      printf("|\n");
      printf("-----------------------------\n");

   }
   printf("  1   2   3   4   5   6   7\n\n");

}

int takeTurn(char *board, int player, const char *PIECES)
{
   int row = 0, col = 0;
   printf("Player %d (%c):\nEnter number coordinate: ", player + 1, PIECES[player]);

   for (;;) { 
      if(1 != scanf("%d", &col) || col < 1 || col > 7 ){
         waitForEnter();
         printf("Number out of bounds! Try again.\n");
      } else { 
         break;
      }
   }
   col--;

   for(row = BOARD_ROWS - 1; row >= 0; row--){
      if(board[BOARD_COLS * row + col] == ' '){
         board[BOARD_COLS * row + col] = PIECES[player];
         return 1;
      }
   }
   return 0;

}

int checkWin(char *board)
{
    return (horizontalCheck(board) || verticalCheck(board) || diagonalCheck(board));

}

int checkFour(char *board, int a, int b, int c, int d)
{
    return (board[a] == board[b] &&
            board[b] == board[c] &&
            board[c] == board[d] &&
            board[a] != ' ');

}

int horizontalCheck(char *board)
{
    int row, col, index;
    const int WIDTH = 1;

    for(row = 0; row < BOARD_ROWS; ++row){
       for(col = 0; col < BOARD_COLS - 3; ++col){
          index = BOARD_COLS * row + col;
          if(checkFour(board, index, index + WIDTH, index + WIDTH * 2, index + WIDTH * 3)){
             return 1;
          }
       }
    }
    return 0;

}

int verticalCheck(char *board)
{
    int row, col, index;
    const int HEIGHT = 7;

    for(row = 0; row < BOARD_ROWS - 3; ++row){
       for(col = 0; col < BOARD_COLS; ++col){
          index = BOARD_COLS * row + col;
          if(checkFour(board, index, index + HEIGHT, index + HEIGHT * 2, index + HEIGHT * 3)){
              return 1;
          }
       }
    }
    return 0;

}

int diagonalCheck(char *board)
{
   int row, col, index, count = 0;
   const int DIAGONAL_RIGHT = 6, DIAGONAL_LEFT = 8;

   for(row = 0; row < BOARD_ROWS - 3; ++row){
      for(col = 0; col < BOARD_COLS; ++col){
         index = BOARD_COLS * row + col;
         if(count <= 3 && checkFour(board, index, index + DIAGONAL_LEFT, index + DIAGONAL_LEFT * 2, index + DIAGONAL_LEFT * 3) || count >= 3 && checkFour(board, index, index + DIAGONAL_RIGHT, index + DIAGONAL_RIGHT * 2, index + DIAGONAL_RIGHT * 3)){
            return 1;
         }
         count++;
      }
      count = 0;
   }
   return 0;
}

void clearScreen()
{
#ifdef WIN64
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter()
{
    while(getchar() != '\n')
        ;
}

