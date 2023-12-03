#ifndef BOARDPOSARRAY_H
#define BOARDPOSARRAY_H
#include "util.h"

typedef struct _boardPosArray {
	unsint size;
	boardPos* positions;
}boardPosArray;

//function gets 2 arguments of type size_t (rows and cols). it then allocates memory to a matrix of boardPosArray with 'row' rows 
//and 'col' columns.
boardPosArray** buildBoardPosArrayMatrix(size_t rows, size_t cols);


//function gets a boardPosArray (arr) and free allocated memory allocated to arr.positions.
void freeBoardPosArray(boardPosArray arr);


//function recieves 3 aruments - a matrix of boardPosArray (matrix) and 2 size_t arguments containing the number of rows and columns. it then
//runs through all cells of the function and free the memory of matrix[row][cols].positions, using 'freeBoardPosArray', and at the end
//free the memory allocated for 'matrix'.
void freeBoardPosArrayMatrix(boardPosArray** matrix, size_t rows, size_t cols);
#endif // !BOARDPOSARRAY_H

