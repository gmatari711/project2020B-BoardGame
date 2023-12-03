#include"boardPosArray.h"


//=====================================================================================================================================
//
//function gets 2 arguments of type size_t (rows and cols). it then allocates memory to a matrix of boardPosArray with 'row' rows 
//and 'col' columns.
//
//=====================================================================================================================================

boardPosArray** buildBoardPosArrayMatrix(size_t rows, size_t cols) {
	boardPosArray** result = ((boardPosArray**)malloc(sizeof(boardPosArray*)*rows));
	if (result == NULL)
		exit(-1);

	for (size_t i = 0; i < rows; i++) {
		result[i] = (boardPosArray*)malloc(sizeof(boardPosArray)*cols);
		if (result[i] == NULL)
			exit(-1);
	}

	return result;
}





//=====================================================================================================================================
//
//function recieves 3 aruments - a matrix of boardPosArray (matrix) and 2 size_t arguments containing the number of rows and columns. it then
//runs through all cells of the function and free the memory of matrix[row][cols].positions, using 'freeBoardPosArray', and at the end
//free the memory allocated for 'matrix'.
//=====================================================================================================================================
void freeBoardPosArrayMatrix(boardPosArray** matrix, size_t rows, size_t cols) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			freeBoardPosArray(matrix[i][j]);
		}
		free(matrix[i]);
	}
	free(matrix);
}


//=====================================================================================================================================
//
//function gets a boardPosArray (arr) and free allocated memory allocated to arr.positions.
//
//=====================================================================================================================================

void freeBoardPosArray(boardPosArray arr) {
	free(arr.positions);
}

