#include "Game.h"

//Section 1 function
//-------------------------------------------------------------
boardPosArray** validMoves(movesArray** moves, char** board) {
	size_t movesRemoved = 0;

	boardPosArray** validPosArray = buildBoardPosArrayMatrix(N, M);
	boardPosArray* currentPosArray;

	movesArray* currentMovesArray;

	movesRemoved = removeInvalidMovements(moves, board);

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			currentMovesArray = &(moves[i][j]);
			currentPosArray = &(validPosArray[i][j]);
			getValidPositionsArray(i,j,currentPosArray, currentMovesArray);
		}
	}

	return validPosArray;

}

//creates a boardPosArray and sets it with all the valid positions that are valid from the given coordinate.
void getValidPositionsArray(char row,char col, boardPosArray* pos_arr, movesArray* moves_arr) {
	size_t size = moves_arr->size;
	boardPos* positions;

	if (size != 0)
		positions = (boardPos*)malloc(sizeof(boardPos)*size);
	else
		positions = NULL;
	
	Move* movesList = moves_arr->moves;

	for (size_t i = 0; i < size; i++) {
		moveToPos(row,col,&(movesList[i]), &(positions[i]));
	}
	pos_arr->size = size;
	pos_arr->positions = positions;
}


//get coordinates of a currnet position and passes by pointer the values of the new coordinates after making the movement in 'source'.
void moveToPos(char row,char col, Move* source, boardPos* dest) {
	(*dest)[0] = row + source->rows + ROW_CONVERSION;
	(*dest)[1] = col + source->cols + COLUMN_CONVERSION;
}




//Section 2 function
//-------------------------------------------------------------

int display(movesList* moves_list, boardPos start, char** board) {
	char** printedBoard = createBoard(N, M);
	boardPos currentPos;
	moveCell* currentMove = NULL;

	size_t index = 0;
	size_t movesRemoved = 0;

	currentPos[0] = start[0];
	currentPos[1] = start[1];

	printedBoard[start[0] - 'A'][start[1] - '1'] = START_POINT;//Start point is set by converting start values to numericals.

	currentMove = moves_list->head;


	while (currentMove!=NULL){
		if (checkMove(currentPos, currentMove->move, board,printedBoard)) {
			index++;
			setPointToBoard(currentPos, index, printedBoard);
		}
		else {
			movesRemoved++;
			currentMove = deleteMove(currentMove);
		}
		currentMove = currentMove->next;
	}
	printBoard(board, printedBoard, N, M);

	freeBoard(printedBoard, N, M);
	
	return movesRemoved;
}

//function check if a given move from a specified position is legit. if it is it will return true to the calling func, otherwise it will return false.
bool checkMove(boardPos position, Move move, char** board, char** printedBoard) {

	char row = move.rows + (position[0] - 'A');
	char col = move.cols + (position[1] - '1');

	if ((board[row][col] == BLOCKED_PATH) || (printedBoard[row][col] != CLEAR_PATH))
		return false;

	position[0] = row + 'A';
	position[1] = col + '1';
	return true;
}


//Section 3 function
//-------------------------------------------------------------

pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board) {
	removeInvalidMovements(moves, board);

	pathTree possibleMoves = createNewTree(start);
	buildPossiblePathsTree(&possibleMoves, moves, board);

	return possibleMoves;
}

/*Shell function that calls 'buildPossiblePathsTreeRec and returns its result - a path tree which contains all possible paths.*/
void buildPossiblePathsTree(pathTree* tree, movesArray** moves, char** board) {
	buildPossiblePathsTreeRec(tree->head, moves, board);
}

void buildPossiblePathsTreeRec(treeNode* node, movesArray** moves, char** board) {
	char row = node->position[0] - ROW_CONVERSION;
	char col = node->position[1] - COLUMN_CONVERSION;

	char currMoveRow = 0;
	char currMoveCol = 0;
	treeNodeListCell* currentList = NULL;

	boardPos position;

	Move* movements = moves[row][col].moves;

	board[row][col] = BLOCKED_PATH;

	if (movements == NULL)
		return;

	size_t locMoveSize = moves[row][col].size;

	for (size_t i = 0; i < locMoveSize; i++) {
		currMoveRow = movements[i].rows + row;
		currMoveCol = movements[i].cols + col;
		if (board[currMoveRow][currMoveCol] == CLEAR_PATH) {

			position[0] = currMoveRow + ROW_CONVERSION;
			position[1] = currMoveCol + COLUMN_CONVERSION;

			if (currentList == NULL)
				currentList = createNewTreeNodeList(node, position);
			else {
				currentList = createTreeNodeListCell(currentList, position);
			}
			buildPossiblePathsTreeRec(currentList->node, moves, board);

		}
	}



	board[row][col] = CLEAR_PATH;

}



//Section 4 functions
//-------------------------------------------------------------
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board) {
	removeInvalidMovements(moves, board);
	size_t clearPaths = (N*M) - numberOfBlockedPaths(N, M, board);

	return findPathByLength(start, moves, board, clearPaths);

}

//shell func for findPathByLengthRec
movesList* findPathByLength(boardPos start, movesArray** moves, char** board, size_t length) {
	char row = start[0] - ROW_CONVERSION;
	char col = start[1] - COLUMN_CONVERSION;

	moveCell* head = findPathByLengthRec(row, col, moves, board, length - 1);//length value gets length -1 because that for a path size of x we have x-1 moves.
	movesList* result = createMovesList(head);

	return result;
}

//find a path by given length.
moveCell* findPathByLengthRec(char row, char col, movesArray** moves, char** board, size_t length) {
	if (length == 0)
		return createEmptyMoveCell();

	char currRow = 0;
	char currCol = 0;
	moveCell* result = NULL;

	board[row][col] = BLOCKED_PATH;
	Move* localMove = moves[row][col].moves;
	size_t moveSize = moves[row][col].size;

	for (size_t i = 0; i < moveSize; i++) {
		currRow = localMove[i].rows + row;
		currCol = localMove[i].cols + col;

		if (board[currRow][currCol] == CLEAR_PATH) {
			result = findPathByLengthRec(currRow, currCol, moves, board, length - 1);
			if (result != NULL) {
				if ((result->move.cols == 0)&&(result->move.rows == 0))
					result->move = localMove[i];
				else {
					board[row][col] = CLEAR_PATH;
					return(createMovecellFromTail(result, localMove[i]));
				}
				board[row][col] = CLEAR_PATH;
				return result;

			}
		}

	}

	board[row][col] = CLEAR_PATH;
	return result;
}



/*Function return the number of blocked paths in a given board. arguments passed are num of rows and cols and, of course, the board itself.*/
size_t numberOfBlockedPaths(size_t rows, size_t cols, char** board) {
	size_t numOfBlockedPaths = 0;
	for (size_t i = 0; i < (size_t)rows; i++)
		for (size_t j = 0; j < cols; j++)
			if (board[i][j] == BLOCKED_PATH)
				numOfBlockedPaths++;

	return numOfBlockedPaths;
}

//section 5 function


//=====================================================================================================================================
//
//function gets to arguments. a char* containing  the name of a file and a pointer to boardPosArray named pos_arr.
//it will create a file and will pass the paths in pos_arr to it in a binary form.
//if it fails creating the file it will exit with messege (-1).
//
//======================================================================================================================================
void saveListToBinFile(char* file_name, boardPosArray* pos_arr) {
	FILE* savedBinPos = fopen(file_name, "w+b");
	if (savedBinPos == NULL)
		exit(-1);

	ushort numOfPositions = pos_arr->size;

	BYTE* listOfPos = getBinListPos(pos_arr);

	fwrite(&numOfPositions, sizeof(ushort), 1, savedBinPos);

	fwrite(listOfPos, sizeof(BYTE), numOfPositions, savedBinPos);

	fclose(savedBinPos);

	free(listOfPos);


}



//Section 6 functions
//-------------------------------------------------------------
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board) {
	int result;

	BYTE* posFromFile = NULL;
	ushort numOfPosInFile = readMoveFromFiles(file_name, &posFromFile);
	if (numOfPosInFile == -1)
		return -1;
	
	boardPosArray* pathFromFile = getPosArrBinList(posFromFile, numOfPosInFile);

	
	char row = pathFromFile->positions[0][0] - ROW_CONVERSION;
	char col = pathFromFile->positions[0][1] - COLUMN_CONVERSION;

	if (board[row][col] == BLOCKED_PATH)
		return 1;

	movesList* pathMovesList = isValidPath(moves, pathFromFile);

	if (pathMovesList == NULL)
		return 1;
	size_t numOfClearPaths = (M*N) - numberOfBlockedPaths(N, M, board);
	
	if (numOfClearPaths == pathFromFile->size)
		result = 2;
	else
		result = 3;

	display(pathMovesList, pathFromFile->positions[0], board);
	return result;

}
//function returns movesList* containing the given path in case path is valid. otherwise it returns NULL. 

//function checks if path array is valid and if it is it creates a movesList matching the path and return it to the calling function.
movesList* isValidPath(movesArray** moves, boardPosArray* path) {
	size_t pathSize = path->size;
	size_t moveArrSize = 0;

	moveCell* curr = NULL;
	movesList* pathList = NULL;

	Move* moveArr = NULL;
	Move currentMove;
	char col, row;
	bool pathValid = true;

	for (size_t i = 1;( i < pathSize)&&(pathValid); i++) {
		posToRowAndCol(path->positions[i - 1], &row, &col);
		moveArrSize = moves[row][col].size;
		moveArr = moves[row][col].moves;

		currentMove = getMove(path->positions[i], row, col);
		for (size_t j = 0; j < moveArrSize; j++) {
			if ((moveArr[j].rows == currentMove.rows) && (moveArr[j].cols == currentMove.cols)) {
				curr = createMoveCell(currentMove);
			}
			else
				curr = NULL;
		}
		if (curr != (NULL)) {
			pathValid = true;
			if (pathList == NULL)
				pathList = createMovesList(NULL);
			addMoveCell(pathList, curr);
		}
		else {
			pathValid = false;
			freeMovesList(pathList);
			pathList = NULL;
		}
	}

	return pathList;
}


boardPos* getStartPoint(movesList* list) {
	boardPos* result = (boardPos*)malloc(sizeof(boardPos));
	(*result)[0] = list->head->move.rows + ROW_CONVERSION;
	(*result)[1] = list->head->move.cols + COLUMN_CONVERSION;

	return result;

}

void posToRowAndCol(boardPos pos, char* row, char* col) {
	*row = pos[0] - ROW_CONVERSION;
	*col = pos[1] - COLUMN_CONVERSION;
}

