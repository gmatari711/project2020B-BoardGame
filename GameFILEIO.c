#include "GameFILEIO.h"

//=====================================================================================================================================
//
//function gets 2 arguments - a name of a file(string) and a pointer to an array of BYTEs.
//the function will read the following information from the given file: number of positions (unsigned short) which returned by the func
//and an array of BYTES into the given array. THE FUNCTION WILL RETURN (-1) IF FILE IS FAILED TO OPEN.
//
//======================================================================================================================================
ushort readMoveFromFiles(char* file_name,BYTE** dest){
	char* movesArr = NULL;
	ushort numOfPos = 0;
	FILE* movesListFile = fopen(file_name, "r+b");
	if (movesListFile == NULL)
		return -1;
	fread(&numOfPos, sizeof(ushort), 1, movesListFile);

	movesArr = (char*)malloc(sizeof(char)*numOfPos);

	fread(movesArr, sizeof(char)*(numOfPos + 1), 1, movesListFile);

	fclose(movesListFile);

	*dest= movesArr;

	return numOfPos;

}

//=====================================================================================================================================
//
//the function recieves 2 arguments - a BYTE containing the encoded moves in binary form and the number of positions in an unsigned int.
//the function extracts data from the array list and push it to boarPosArray 'listOfPos'.
//
//function returns 'listOfPos'
//======================================================================================================================================

boardPosArray* getPosArrBinList(BYTE* list, ushort numOfPositions) {
	BYTE mask =0;//used to isolate desired bits.
	size_t index = 0;//BYTE array index
	boardPosArray* listOfPos = (boardPosArray*)malloc(sizeof(boardPosArray));

	listOfPos->positions = (boardPos*)malloc(sizeof(boardPos)*numOfPositions);
	listOfPos->size = numOfPositions;

	size_t currPos = 0;//counts how many positions extracted from BYTE array.
	BYTE curr = 0;
	size_t bytesSign= SIGN_SIZE;//size of the board numerical or alphabetical sign which is 3.
	size_t usedBytes = BYTE_SIZE;//how many used bytes left in the list[index].
	size_t shiftSize=0;//how far bits are shifted
	size_t dataExtracted = 0;//how many chars extracted from list.

	while (currPos < numOfPositions) {//runs until all moves extracted.
		if (usedBytes >=bytesSign) {
			shiftSize = usedBytes - bytesSign;//in these lines the mask is adjusted
			mask = MASK << shiftSize;

			curr = (list[index] & mask)>>shiftSize;//data extracted using a mask
		
			usedBytes -= bytesSign;//subtract drawn bits from usedBytes
			if (!usedBytes) {//after using all the bytes in list[index] we increment index and init usedBytes
				usedBytes = BYTE_SIZE;
				index++;
			}

		}
		else {
			shiftSize = bytesSign - usedBytes;//in these lines the mask is adjusted and used to extract data
			mask = MASK >> shiftSize;
			curr = (list[index] & mask)<<shiftSize;
			index++;//after using all the bytes in list[index] we increment index and init usedBytes

			mask = MASK <<(BYTE_SIZE-shiftSize);//in these lines the mask is adjusted and used to extract data
			curr = curr|((list[index] & mask) >> (BYTE_SIZE - shiftSize));

			usedBytes = BYTE_SIZE-shiftSize;//subtract drawn bits from usedBytes
			

		}
		if (dataExtracted % 2)//information is pushed to listOfPos
			listOfPos->positions[currPos][1] = curr + COLUMN_CONVERSION;
		else
			listOfPos->positions[currPos][0] = curr + ROW_CONVERSION;

		dataExtracted++;
		if (dataExtracted % 2 == 0)
			currPos++;
	}
	return listOfPos;
}