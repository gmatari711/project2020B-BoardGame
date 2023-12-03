#include "boardLocationsBin.h"

#define BYTE_SIZE 8
#define POS_SIZE 6


//=====================================================================================================================================
//
//function gets a boardPosArray* pos_arr and sets its paths to a BYTE file in a binary form.
//
//======================================================================================================================================
BYTE* getBinListPos(boardPosArray* pos_arr) {
	BYTE* binArr = createBinArr(pos_arr->size);//creating the BYTE variable at the deired size.
	
	size_t numOfPos = pos_arr->size;//number of positions needed to be extracted
	size_t index = 0;
	size_t currPos = 0;
	size_t shiftSize = 0;
	size_t numOfFreeBits = BYTE_SIZE;//how many unused bits left at binArr[index].
	size_t bitsInCurrent = 0;//bits needed to be put into binArr.
	
	BYTE curr = 0;//BYTE variables used as a buffers
	BYTE next = 0;//


	while (currPos < numOfPos) {
		curr = getBinPosValue(pos_arr->positions[currPos++]);
		bitsInCurrent = POS_SIZE;

		if (numOfFreeBits >= bitsInCurrent) {//information extracted and manipulated and then put into binArr in the desired form of binary code.
			shiftSize = (numOfFreeBits - bitsInCurrent);
			curr = curr << shiftSize;
			binArr[index] = binArr[index] | curr;
			numOfFreeBits -= bitsInCurrent;
			if (numOfFreeBits == 0) {
				numOfFreeBits = 0;
				index++;
			}
		}
		else {
			shiftSize = bitsInCurrent - numOfFreeBits;

			next = curr << (BYTE_SIZE - shiftSize);
			curr = curr >> shiftSize;
			
			binArr[index] = binArr[index] | curr;
			index++;
			binArr[index] = binArr[index] | next;
			
			numOfFreeBits = BYTE_SIZE - shiftSize;
		}

	}

	return binArr;//returns the array


}

//=====================================================================================================================================
//function gets a size_t (size) and allocates an array of BYTE named binArr at the size of the argument. it returns binArr to the
//calling function.
//
//=====================================================================================================================================
BYTE* createBinArr(size_t size) {
	BYTE* binArr = (BYTE*)malloc(sizeof(BYTE)*size);

	for (size_t i = 0; i < size; i++)
		binArr[i] = 0;



	return binArr;
}

//=====================================================================================================================================
//
//fuction recieves an argument of boardPos (pos), convert its posision coordinates to its decimal value -1. get their binary values and
//set it on a BYTE type variable named result which then returned to the calling function.
//
//=====================================================================================================================================

BYTE getBinPosValue(boardPos pos) {

	BYTE result = 0;
	BYTE curr=0;
	char row = pos[0] - ROW_CONVERSION;
	char col = pos[1] - COLUMN_CONVERSION;

	for (size_t i = 0; i < POS_SIZE; i++) {
		if (i < 3) {
			curr = col % 2;
			col /= 2;
			curr = curr << i;
			result = result | curr;
		}
		else {
			curr = row % 2;
			row /= 2;
			curr = curr << i;
			result = result | curr;
		}
	}

	return result;
}