//============================== FINAL PROJECT 2020B==================================
//  MADE BY
//	GAL MATARI 300599909
//	VLADI BINYAMINOV 311014807
//
//====================================================================================

#ifndef GAME_H
#define GAME_H

#include "util.h"
#include "boardPosArray.h"
#include "Move.h"
#include "graphics.h"
#include "pathtree.h"
#include "boardLocationsBin.h"
#include "GameFILEIO.h"

//Section 1 function
//-------------------------------------------------------------
boardPosArray** validMoves(movesArray** moves, char** board);
//-------------------------------------------------------------


void getValidPositionsArray(char row, char col, boardPosArray* pos_arr, movesArray* moves_arr);

void moveToPos(char row, char col, Move* source, boardPos* dest);
//void getValidPositionsArray(boardPos currentPos,boardPosArray* position, movesArray* movesList, boardPosArray blockedPaths);


//Section 2  function.
//-------------------------------------------------------------
int display(movesList* moves_list, boardPos start, char** board);

bool checkMove(boardPos position, Move move, char** board, char** printedBoard);
//-------------------------------------------------------------

//Section 3 function.
//---------------------------------------------------------------
pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);



void buildPossiblePathsTree(pathTree* tree, movesArray** moves, char** board);

void buildPossiblePathsTreeRec(treeNode* node, movesArray** moves, char** board);

movesList* findPathByLength(boardPos start, movesArray** moves, char** board, size_t length);

size_t numberOfBlockedPaths(size_t rows, size_t cols, char** board);

moveCell* findPathByLengthRec(char row, char col, movesArray** moves, char** board, size_t length);
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);

int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);

movesList* isValidPath(movesArray** moves, boardPosArray* path);

boardPos* getStartPoint(movesList* list);

void posToRowAndCol(boardPos pos, char* row, char* col);

#endif // !GAME_H
