#ifndef UTIL_H
#define UTIL_H

#define _CRT_SECURE_NO_WARNINGS
#define M 3 //columns
#define N 3 //rows

#define BLOCKED_PATH '*' 
#define START_POINT '#' 
#define CLEAR_PATH ' ' //clear path is defined by a white space
#define PRINT_CONVERSION_FACTOR -1
#define COLUMN_CONVERSION '1'
#define ROW_CONVERSION 'A'

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char boardPos[2];
typedef unsigned int unsint;
typedef unsigned short ushort;
typedef unsigned long long ulong;
typedef unsigned char BYTE;

typedef struct _move {
	char rows, cols;
}Move;





#endif
