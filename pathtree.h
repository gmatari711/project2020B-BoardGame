#ifndef PATHTREE_H
#define PATHTREE_H
#include "util.h"

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	boardPos position;
	treeNodeListCell *next_possible_positions;
}treeNode;

struct _treeNodeListCell {
	treeNode *node;
	treeNodeListCell* next;
};

typedef struct _pathTree {
	treeNode* head;
}pathTree;


//gets a pathTree* tree and sets its head to NULL.
void initPathTree(pathTree* tree);


//function recives a treeNodeListCell* (cell) and sets its variables, 'node' and 'next', to NULL.
void initTreeNodeList(treeNodeListCell* cell);

//function allocates memory for a new node 'newNod'and sets 'newNode->position' values to these of 'position'. function returns newNode  
//to the calling function.
treeNode* createNewNode(boardPos position);

//function creates a new variable of type pathTree (tree) and sets 'tree->head' to be a new node with the boardPos position give as an 
//argument.
pathTree createNewTree(boardPos position);


//function gets 2 arguments - treeNode* (node) and boardPos (position). it allocates memory to node->next_possible_positions and 
//assign its node with a new node containing the provided boardPos 'position'.
treeNodeListCell* createNewTreeNodeList(treeNode* node, boardPos position);


//runs through next possible positions of a given node till it reaches the last next_possible_position. then the function will push a  
//new treeNodeListCell with the provided boardPos 'positions' and will return its address to th calling function.
treeNodeListCell* addNewTreeNodeList(treeNode* node, boardPos position);


//function allocates memory for a new TreeNodeListCell , sets it after the given treeNodeListCell(currnt), and creates a new node inside
//the new treeNodeListCell with the provided boardPos 'position'.
treeNodeListCell* createTreeNodeListCell(treeNodeListCell* current, boardPos position);


//'helper' function calls 'printTreeRec' with tree->head.
void printTree(pathTree* tree);


//function runs recursivly through the given tree from head (first pointer given) thoroughout all branches and prints its values.
//used for tests.
void printTreeRec(treeNode* node);
#endif
