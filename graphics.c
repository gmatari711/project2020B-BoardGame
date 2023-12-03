#include "graphics.h"


//=====================================================================================================================================
//
//the function recieves 2 arguments of type size_t - number of rows and number of columns(cols). it will allocate memory and returns a
//char** matrix and initial its values to CLEAR_PATH sign (" ").
//
//======================================================================================================================================

char** createBoard(size_t rows, size_t cols) {
	char** result = (char**)malloc(sizeof(char*)*rows);
	if (result == NULL)
		exit(-1);
	for (size_t i = 0; i < rows; i++) {
		result[i] = (char*)malloc(sizeof(char)*cols);
		if (result[i] == NULL)
			exit(-1);
	}

	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			result[i][j] = CLEAR_PATH;

	return result;
}

//=====================================================================================================================================
//
//free allocated memory of a given char** board.
//
//=====================================================================================================================================
void freeBoard(char** board,size_t rows,size_t cols) {
	for (size_t i = 0; i < rows; i++)
		free(board[i]);
	free(board);
}


//=====================================================================================================================================
//
//function get a point and sets a given index on that point on the board.
//
//
//=====================================================================================================================================
void setPointToBoard(boardPos point, size_t index, char** board) {
	char row = point[0] - 'A';
	char col = point[1] - '1';

	board[row][col] = index * PRINT_CONVERSION_FACTOR;// index is multiplied by a fuctor.
}



//=====================================================================================================================================
//
//function gets 2 boards. one contains blocked paths and the other contains used paths and prints the games board to the screen.
//
//======================================================================================================================================
void printBoard(char** board, char** movesBoard, size_t rows, size_t cols) {
	for (size_t i = 0; i <= cols; i++) {//prints numerical position signs on top of bord
		if (i == 0)
			printf("|   ");
		else
			printf("| %d ", i);
	}
	printf("\n");

	for (size_t i = 0; i < rows; i++) {
		printf("| %c ", i + 'A');//prints alphabetical position signs at the side of the board
		for (size_t j = 0; j < cols; j++) {
			if (board[i][j] == BLOCKED_PATH)//next few lines prints the game board it self.
				printf("| * ");//blocked paths
			else
				if (movesBoard[i][j] == START_POINT)
					printf("| # ");//start point
				else
					if (movesBoard[i][j] < 0)
						printf("| %d ", movesBoard[i][j] * PRINT_CONVERSION_FACTOR);//taken path signed by index multiplied by conversion factor.
					else
						printf("|   ");//clear path
		}
		printf("\n");
	}

}