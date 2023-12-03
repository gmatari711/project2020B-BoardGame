#include "pathtree.h"

//=====================================================================================================================================
//
//gets a pathTree* tree and sets its head to NULL.
//
//=====================================================================================================================================

void initPathTree(pathTree* tree) {
	tree->head = NULL;
}

//=====================================================================================================================================
//
//function recives a treeNodeListCell* (cell) and sets its variables, 'node' and 'next', to NULL.
//
//=====================================================================================================================================
void initTreeNodeList(treeNodeListCell* cell) {
	cell->node = NULL;
	cell->next = NULL;
}

//=====================================================================================================================================
//
//function allocates memory for a new node 'newNod'and sets 'newNode->position' values to these of 'position'. function returns newNode  
//to the calling function.
//
//=====================================================================================================================================
treeNode* createNewNode(boardPos position) {
	treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
	newNode->position[0] = position[0];
	newNode->position[1] = position[1];

	newNode->next_possible_positions = NULL;

	return newNode;
}

//=====================================================================================================================================
//
//function creates a new variable of type pathTree (tree) and sets 'tree->head' to be a new node with the boardPos position give as an 
//argument.
//
//=====================================================================================================================================
pathTree createNewTree(boardPos position) {
	pathTree tree;
	tree.head = createNewNode(position);

	return tree;
}

//=====================================================================================================================================
//
//function gets 2 arguments - treeNode* (node) and boardPos (position). it allocates memory to node->next_possible_positions and 
//assign its node with a new node containing the provided boardPos 'position'.
//
//=====================================================================================================================================
treeNodeListCell* createNewTreeNodeList(treeNode* node, boardPos position) {
	node->next_possible_positions = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	node->next_possible_positions->next = NULL;
	node->next_possible_positions->node = createNewNode(position);

	return node->next_possible_positions;
}


//=====================================================================================================================================
//
//runs through next possible positions of a given node till it reaches the last next_possible_position. then the function will push a  
//new treeNodeListCell with the provided boardPos 'positions' and will return its address to th calling function.
//
//=====================================================================================================================================
treeNodeListCell* addNewTreeNodeList(treeNode* node, boardPos position) {
	if (node->next_possible_positions == NULL)
		return createNewTreeNodeList(node, position);
	else {
		treeNodeListCell* current = node->next_possible_positions;
		while (current->next != NULL)
			current = current->next;

		return createTreeNodeListCell(current, position);
	}
}

//=====================================================================================================================================
//
//function allocates memory for a new TreeNodeListCell , sets it after the given treeNodeListCell(currnt), and creates a new node inside
//the new treeNodeListCell with the provided boardPos 'position'.
//
//=====================================================================================================================================
treeNodeListCell* createTreeNodeListCell(treeNodeListCell* current, boardPos position) {
	current->next = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	current = current->next;
	current->node = createNewNode(position);
	current->next = NULL;

	return current;
}

//=====================================================================================================================================
//
//'helper' function calls 'printTreeRec' with tree->head.
//
//=====================================================================================================================================
void printTree(pathTree* tree) {
	printTreeRec(tree->head);
}


//=====================================================================================================================================
//
//function runs recursivly through the given tree from head (first pointer given) thoroughout all branches and prints its values.
//used for tests.
//=====================================================================================================================================
void printTreeRec(treeNode* node) {
	treeNodeListCell* curr = NULL;
	printf("%c%c\n", node->position[0], node->position[1]);
	curr = node->next_possible_positions;
	while(curr!=NULL){
		printTreeRec(curr->node);
		curr = curr->next;
	}
		
	

}