#ifndef BOARDLOCATIONSBIN_H
#define BOARDLOCATIONSBIN_H

#include "util.h"
#include "boardPosArray.h"

//function gets to arguments. a char* containing  the name of a file and a pointer to boardPosArray named pos_arr.
//it will create a file and will pass the paths in pos_arr to it in a binary form.
//if it fails creating the file it will exit with messege (-1).
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);

//function gets a size_t (size) and allocates an array of BYTE named binArr at the size of the argument. it returns binArr to the
//calling function.
//
BYTE* createBinArr(size_t size);

//fuction recieves an argument of boardPos (pos), convert its posision coordinates to its decimal value -1. get their binary values and
//set it on a BYTE type variable named result which then returned to the calling function.
BYTE getBinPosValue(boardPos pos);

//function gets a boardPosArray* pos_arr and sets its paths to a BYTE file in a binary form.
BYTE* getBinListPos(boardPosArray* pos_arr);

#endif
