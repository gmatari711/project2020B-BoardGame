#ifndef MOVE_H
#define MOVE_H
#include "util.h"

typedef struct _movesArray {
	size_t size;
	Move* moves;
}movesArray;

typedef struct _moveCell {
	Move move;
	struct _moveCell *next, *prev;
}moveCell;

typedef struct _movesList {
	moveCell *head;
	moveCell *tail;
}movesList;


//function recieves a pointer to a moveCell. it then remove the given cell and free its allocated memory and connect the previos and next
//items as needed.
moveCell* deleteMove(moveCell* move);


//function gets a Move argument, allocate memory to a new moveCell* result and assign the given Move move to result->move.
//it also sets prev and next to NULL. AT THE END OF THE RUN THE FUNCTION WILL RETURN result BACK TO THE CALLING FUNC.
moveCell* createMoveCell(Move move);

//fuction recieve 2 arguments - a moveCell* (tail) and Move (move). it creates a new moveCell* with the Move provided to it and "push" it
//in front of the given moveCell.
moveCell* createMovecellFromTail(moveCell* tail, Move move);

//function allocates a moveCell* result. sets result->move.col/row to 0 and sets prev and next to NULL.
//AT THE END OF THE RUN THE FUNCTION WILL RETURN result TO THE CALLING FUNC.
moveCell* createEmptyMoveCell();


//function recieves an argument moveCell* (head). it allocate memory to movesList* result, then if 'head' set to NULL it will assume
//empty list and will set 'head'&'tail' to NULL. otherwise it will set 'result->head' as 'head' and tail as the last member on the list.
movesList* createMovesList(moveCell* head);

//function gets 2 arguments - a movesList* (list) and a Move (move). if list is empty, 'move' is assigned to result->head'&'result->tail'
//otherwise, move will be pushed to the end of the list and assigned to 'result->tail'.
void addMoveToLis(movesList* list, Move* move);

//function gets movesList* (list) as an argument. it then calls freeMoveCells with 'list->head' and afterwards frees memory allocated
//to its given argument 'movesList* list'.
void freeMovesList(movesList* list);

//functions runs through a given linked moveCell list and free all allocated memories
void freeMoveCells(moveCell* head);

//fucntion recives 3 arguments. a boardPos (pos) - which is a desired destination ,and coordinates of current position of type 'char' - 
//a 'row' and a 'col'. the function will return a Move result with containing how many columns and rows should be passed in one move
//in order to land on the desired 'pos'.
Move getMove(boardPos pos, char row, char col);

//function runs through moves and board and removes all moves that are leading to a blocked path or outside the boundries of the game
//board.
//it returns how many paths removed.(good for tests as indication)
ushort removeInvalidMovements(movesArray** moves, char** board);

void addMoveCell(movesList* list, moveCell* move);

//this function is a helping function to the func given above it. it runs through a specific move array taken from moves matrix and
//remove invalid moves from the given array. it returns the number of paths removed.(good for tests as indication)
ushort removeInvalidMovesFromArray(size_t row, size_t col, Move** moves, size_t* size, char** board);

#endif