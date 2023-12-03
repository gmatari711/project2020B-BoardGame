#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "util.h"

//the function recieves 2 arguments of type size_t - number of rows and number of columns(cols). it will allocate memory and returns a
//char** matrix and initial its values to CLEAR_PATH sign (" ").
char** createBoard(size_t rows, size_t cols);

//free allocated memory of a given char** board.
void freeBoard(char** board, size_t rows, size_t cols);


//function get a point and sets a given index on that point on the board.
void setPointToBoard(boardPos point,size_t index ,char** board);


//function gets 2 boards. one contains blocked paths and the other contains used paths and prints the games board to the screen.
void printBoard(char** board, char** movesBoard, size_t rows, size_t cols);

#endif