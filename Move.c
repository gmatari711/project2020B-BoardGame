#include "Move.h"

//=====================================================================================================================================
//
//function recieves a pointer to a moveCell. it then remove the given cell and free its allocated memory and connect the previos and next
//items as needed.
//=====================================================================================================================================
moveCell* deleteMove(moveCell* move) {
	moveCell* result;
	if (move->prev == NULL) {
		result = move->next;
	}
	else {
		result = move->prev;
		result->next = move->next;
		move->next->prev = result;
	}
	free(move);
	return result;

}

//=====================================================================================================================================
//
//fuction recieve 2 arguments - a moveCell* (tail) and Move (move). it creates a new moveCell* with the Move provided to it and "push" it
//in front of the given moveCell.
//=====================================================================================================================================
moveCell* createMovecellFromTail(moveCell* tail, Move move) {
	tail->prev = (createMoveCell(move));
	tail->prev->next = tail;

	return tail->prev;
}

//=====================================================================================================================================
//
//function gets a Move argument, allocate memory to a new moveCell* result and assign the given Move move to result->move.
//it also sets prev and next to NULL. AT THE END OF THE RUN THE FUNCTION WILL RETURN result BACK TO THE CALLING FUNC.
//
//=====================================================================================================================================
moveCell* createMoveCell(Move move) {
	moveCell* result = (moveCell*)malloc(sizeof(moveCell));
	result->move = move;
	result->next = result->prev = NULL;

	return result;
}

//=====================================================================================================================================
//
//function allocates a moveCell* result. sets result->move.col/row to 0 and sets prev and next to NULL.
//AT THE END OF THE RUN THE FUNCTION WILL RETURN result TO THE CALLING FUNC.
//
//=====================================================================================================================================
moveCell* createEmptyMoveCell() {
	moveCell* result = (moveCell*)malloc(sizeof(moveCell));
	result->move.cols = 0;
	result->move.rows = 0;
	result->next = result->prev = NULL;

	return result;
}

//=====================================================================================================================================
//
//function recieves an argument moveCell* (head). it allocate memory to movesList* result, then if 'head' set to NULL it will assume
//empty list and will set 'head'&'tail' to NULL. otherwise it will set 'result->head' as 'head' and tail as the last member on the list.
//=====================================================================================================================================
movesList* createMovesList(moveCell* head) {
	movesList* result = (movesList*)malloc(sizeof(movesList));

	if (head == NULL)
		result->head = result->tail = NULL;
	else {
		moveCell* curr = head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		result->head = head;
		result->tail = curr;
	}

	return result;

}


//=====================================================================================================================================
//
//function gets 2 arguments - a movesList* (list) and a Move (move). if list is empty, a new moveCell* with 'move' is assigned to 
//result->head'&'result->tail', otherwise, move will be pushed to the end of the list and assigned to 'result->tail'.
//
//=====================================================================================================================================
void addMoveToList(movesList* list, Move* move) {
	moveCell* current = list->head;
	if (current == NULL) {
		list->head = list->tail = createMoveCell(*move);
	}
	else{
		while (current->next != NULL)
			current = current->next;

		current->next =createMoveCell(*move);
		current->next->prev = current;
		current->next->next = NULL;

		list->tail = current->next;
	}

	
}
//=====================================================================================================================================
//
//function gets 2 arguments - a movesList* (list) and a Move (move). if list is empty, 'move' is assigned to result->head'&'result->tail'
//otherwise, move will be pushed to the end of the list and assigned to 'result->tail'.
//
//=====================================================================================================================================
void addMoveCell(movesList* list, moveCell* move) {
	moveCell* current = list->head;
	if (current == NULL) {
		list->head = list->tail = move;
	}
	else {
		while (current->next != NULL)
			current = current->next;

		current->next = move;
		current->next->prev = current;
		current->next->next = NULL;

		list->tail = current->next;
	}
}


//=====================================================================================================================================
//
//fucntion recives 3 arguments. a boardPos (pos) - which is a desired destination ,and coordinates of current position of type 'char' - 
//a 'row' and a 'col'. the function will return a Move result with containing how many columns and rows should be passed in one move
//in order to land on the desired 'pos'.
//
//=====================================================================================================================================
Move getMove(boardPos pos, char row, char col) {
	Move result;
	result.rows = (pos[0] - ROW_CONVERSION) - row;
	result.cols = (pos[1] - COLUMN_CONVERSION) - col;

	return result;
}

//=====================================================================================================================================
//function gets movesList* (list) as an argument. it then calls freeMoveCells with 'list->head' and afterwards frees memory allocated
//to its given argument 'movesList* list'.
//=====================================================================================================================================
void freeMovesList(movesList* list){
	if(list!=NULL)
		freeMoveCells(list->head);
	free(list);
}
//=====================================================================================================================================
//
//functions runs through a given linked moveCell list and free all allocated memories.
//
//=====================================================================================================================================
void freeMoveCells(moveCell* head) {
	if (head->next == NULL) {
		free(head);
	}
	else {
		freeMoveCells(head->next);
		free(head);
	}
}


//=====================================================================================================================================
//
//function runs through moves and board and removes all moves that are leading to a blocked path or outside the boundries of the game
//board.
//it returns how many paths removed.(good for tests as indication)
//=====================================================================================================================================
ushort removeInvalidMovements(movesArray** moves, char** board) {
	Move** movesArr;
	size_t* movesArrSize;
	ushort movesRemoved = 0;
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			movesArr = &(moves[i][j].moves);
			movesArrSize = &(moves[i][j].size);
			movesRemoved += removeInvalidMovesFromArray(i, j, movesArr, movesArrSize, board);
		}
	}

	return movesRemoved;
}


//=====================================================================================================================================
//
//this function is a helping function to the func given above it. it runs through a specific move array taken from moves matrix and
//remove invalid moves from the given array. it returns the number of paths removed.(good for tests as indication)
//=====================================================================================================================================
ushort removeInvalidMovesFromArray(size_t row, size_t col, Move** moves, size_t* size, char** board) {
	size_t movesRemoved = 0;

	if (board[row][col] == BLOCKED_PATH) {
		free(*moves);
		*moves = NULL;
		*size = 0;
		movesRemoved = *size;
		return (ushort)movesRemoved;
	}

	Move* localMoves = *moves;
	size_t localSize = *size;


	char currRow = 0;
	char currCol = 0;


	for (size_t i = 0; i < localSize; i++) {
		currRow = localMoves[i].rows + (char)row;
		currCol = localMoves[i].cols + (char)col;
		if ((currRow < 0) || (currRow >= N) || (currCol < 0) || (currCol >= M))
			movesRemoved++;
		else if (board[currRow][currCol] == BLOCKED_PATH)
			movesRemoved++;
		else if (movesRemoved)
			localMoves[i - movesRemoved] = localMoves[i];
	}
	localSize -= movesRemoved;
	localMoves = NULL;

	if (localSize != 0) {
		*moves = (Move*)realloc(*moves, sizeof(Move)*(localSize));//if localSize is 0, realloc will return NULL.
	}
	else {
		free(*moves);
		*moves = NULL;
	}
	*size = localSize;


	return (ushort)movesRemoved;
}
