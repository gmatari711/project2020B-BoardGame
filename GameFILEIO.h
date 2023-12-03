#ifndef GAMEFILEIO_H
#define GAMEFILEIO_H
#include "util.h"
#include "boardPosArray.h"

#define BYTE_SIZE 8
#define POS_SIZE 6
#define SIGN_SIZE 3
#define MASK 7



//function gets 2 arguments - a name of a file(string) and a pointer to an array of BYTEs.
//the function will read the following information from the given file: number of positions (unsigned short) which returned by the func
//and an array of BYTES into the given array. THE FUNCTION WILL RETURN (-1) IF FILE IS FAILED TO OPEN.
//
ushort readMoveFromFiles(char* file_name, BYTE** dest);




//the function recieves 2 arguments - a BYTE containing the encoded moves in binary form and the number of positions in an unsigned int.
//the function extracts data from the array list and push it to boarPosArray 'listOfPos'.

//function returns 'listOfPos'

boardPosArray* getPosArrBinList(BYTE* list, ushort numOfPositions);


#endif