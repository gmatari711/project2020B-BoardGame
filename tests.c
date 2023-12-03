#include "Game.h"

movesArray* getData(size_t rowSize,size_t colSize) {
	size_t size = 0;
	int col, row;
	movesArray** moves = (movesArray**)malloc(sizeof(movesArray*)*rowSize);
	for (size_t i = 0; i <rowSize; i++)
		moves[i] = (movesArray*)malloc(sizeof(movesArray)*colSize);

	for (size_t i = 0; i < rowSize; i++)
		for (size_t j = 0; j < colSize; j++) {
			printf("How many moves for position %c%c?: ", i + ROW_CONVERSION, j + COLUMN_CONVERSION);
			scanf("%d", &size);
			moves[i][j].size = size;
			if (size) {
				moves[i][j].moves = (Move*)malloc(sizeof(Move)*size);
				for (size_t k = 0; k < size; k++) {
					printf("Enter Moves: ");
					scanf("%d%d", &row, &col);
					moves[i][j].moves[k].rows = row;
					moves[i][j].moves[k].cols = col;
				}
			}
			else
				moves[i][j].moves = NULL;
		}
	return moves;
}

void test1() {
	char** board = createBoard(N, M);

	boardPos start = { 'A','2' };
	board[0][3] = BLOCKED_PATH;
	board[1][7] = BLOCKED_PATH;
	board[3][5] = BLOCKED_PATH;
	board[4][0] = BLOCKED_PATH;

	size_t size = 0;
	int col, row;
	movesArray** moves = (movesArray**)malloc(sizeof(movesArray*)*N);
	for (size_t i = 0; i < N; i++)
		moves[i] = (movesArray*)malloc(sizeof(movesArray)*M);

	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++) {
			/*printf("How many moves for position %c%c?: ", i + ROW_CONVERSION, j + COLUMN_CONVERSION);*/
			scanf("%d", &size);
			moves[i][j].size = size;
			if (size) {
				moves[i][j].moves = (Move*)malloc(sizeof(Move)*size);
				for (size_t k = 0; k < size; k++) {
					/*printf("Enter Moves: ");*/
					scanf("%d%d", &row, &col);
					moves[i][j].moves[k].rows = row;
					moves[i][j].moves[k].cols = col;
				}
			}
			else
				moves[i][j].moves = NULL;
		}
	boardPosArray** boardpositions = validMoves(moves, board);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			for (size_t k = 0; k < boardpositions[i][j].size; k++)
				printf("[%c][%c]\n", boardpositions[i][j].positions[k][0], boardpositions[i][j].positions[k][1]);
		}
	}

}

void test3() {
	char** board = createBoard(N, M);

	boardPos start = { 'A','2' };
	board[0][3] = BLOCKED_PATH;
	board[1][7] = BLOCKED_PATH;
	board[3][5] = BLOCKED_PATH;
	board[4][0] = BLOCKED_PATH;

	size_t size = 0;
	int col, row;
	movesArray** moves = (movesArray**)malloc(sizeof(movesArray*)*N);
	for (size_t i = 0; i < N; i++)
		moves[i] = (movesArray*)malloc(sizeof(movesArray)*M);

	for(size_t i=0;i<N;i++)
		for (size_t j = 0; j < M; j++) {
			/*printf("How many moves for position %c%c?: ", i + ROW_CONVERSION, j + COLUMN_CONVERSION);*/
			scanf("%d", &size);
			moves[i][j].size = size;
			if (size) {
				moves[i][j].moves = (Move*)malloc(sizeof(Move)*size);
				for (size_t k = 0; k < size; k++) {
					/*printf("Enter Moves: ");*/
					scanf("%d%d", &row, &col);
					moves[i][j].moves[k].rows = row;
					moves[i][j].moves[k].cols = col;
				}
			}
			else
				moves[i][j].moves= NULL;
		}
	for (size_t i = 0; i < moves[0][1].size; i++) {
		printf("%d %d\n", moves[0][1].moves[i].rows, moves[0][1].moves[i].cols);
	}
	pathTree tree = findAllPossiblePaths(start, moves, board);
	printTree(&tree);
}

void test2() {
	char** board = createBoard(N, M);

	board[0][0] = BLOCKED_PATH;
	board[3][0] = BLOCKED_PATH;
	board[3][3] = BLOCKED_PATH;
	int row,col;

	boardPos start = { 'A','2' };
	size_t k = 0;

	movesList* moves = createMovesList(NULL);
	moveCell* move;
	scanf("%d", &k);
	for (size_t i =0; i < k; i++) {
		move = (moveCell*)malloc(sizeof(moveCell));
		printf("Enter moves: \n");
		scanf("%d%d", &row, &col);
		move->move.cols=col;
		move->move.rows=row;
		move->next=move->prev = NULL;
		addMoveCell(moves,move);
		move = NULL;

	}

	display(moves, start, board);
	freeBoard(board,N,M);
}

void test4() {
	char** board = createBoard(N, M);

	boardPos start = { 'A','2' };
	board[0][0] = BLOCKED_PATH;
	board[1][1] = BLOCKED_PATH;
	

	size_t size = 0;
	int col, row;
	movesArray** moves = (movesArray**)malloc(sizeof(movesArray*)*N);
	for (size_t i = 0; i < N; i++)
		moves[i] = (movesArray*)malloc(sizeof(movesArray)*M);

	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++) {
			/*printf("How many moves for position %c%c?: ", i + ROW_CONVERSION, j + COLUMN_CONVERSION);*/
			scanf("%d", &size);
			moves[i][j].size = size;
			if (size) {
				moves[i][j].moves = (Move*)malloc(sizeof(Move)*size);
				for (size_t k = 0; k < size; k++) {
					/*printf("Enter Moves: ");*/
					scanf("%d%d", &row, &col);
					moves[i][j].moves[k].rows = row;
					moves[i][j].moves[k].cols = col;
				}
			}
			else
				moves[i][j].moves = NULL;
		}
	movesList* list = findPathCoveringAllBoard(start, moves, board);
	display(list, start, board);
}

void test5() {
	char** board = buildBoardPosArrayMatrix(3, 3);
	board[0][0] = BLOCKED_PATH;
	board[0][2] = BLOCKED_PATH;
	board[1][0] = BLOCKED_PATH;
	board[2][0] = BLOCKED_PATH;
	board[2][1] = BLOCKED_PATH;
	board[2][2] = BLOCKED_PATH;

	boardPosArray posArray;
	posArray.positions = (boardPos*)malloc(sizeof(boardPos) * 3);
	posArray.size = 3;
	posArray.positions[0][0] = 'A';
	posArray.positions[0][1] = '2';
	posArray.positions[1][0] = 'B';
	posArray.positions[1][1] = '2';
	posArray.positions[2][0] = 'B';
	posArray.positions[2][1] = '3';

	movesArray** moves = getData(3, 3);

	char* mylist = NULL;
	saveListToBinFile("my_file.txt", &posArray);
	ushort numOfPos = readMoveFromFiles("my_file.txt", &mylist);
	boardPosArray* secondPosArray = getPosArrBinList(mylist, numOfPos);
	
}

void test6() {
	char** board = buildBoardPosArrayMatrix(3, 3);
	board[0][0] = BLOCKED_PATH;
	board[0][2] = BLOCKED_PATH;
	board[1][0] = BLOCKED_PATH;
	board[2][0] = BLOCKED_PATH;
	board[2][1] = BLOCKED_PATH;
	board[2][2] = BLOCKED_PATH;

	boardPosArray posArray;
	posArray.positions = (boardPos*)malloc(sizeof(boardPos) * 3);
	posArray.size = 2;
	posArray.positions[0][0] = 'A';
	posArray.positions[0][1] = '2';
	posArray.positions[1][0] = 'B';
	posArray.positions[1][1] = '2';


	movesArray** moves = getData(3, 3);

	char* mylist = NULL;
	saveListToBinFile("my_file.txt", &posArray);
	ushort numOfPos = readMoveFromFiles("my_file.txt", &mylist);
	int num = checkAndDisplayPathFromFile("my_file.txt", moves, board);
	printf("\n%d", num);

}

int main() {
	//test1();
	///*N=6 M=4*/
	//test2();
	/*N=5, M=8*/
	//test3();
	//test4();
	/*test5();*/
	test6();
	return;
}