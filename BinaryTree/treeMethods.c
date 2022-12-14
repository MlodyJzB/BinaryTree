#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../BinaryTree/treeMethods.h"

// defines for True and false
#define TRUE 1
#define FALSE 0

void initN(float num, struct Node* nP) {
	// Purpose: init new node with a given value

	nP->num = num;
	nP->left = NULL;
	nP->right = NULL;
	return;
}

void ascendAdd(struct Node* toAddP, struct Node** rootPP) {
	// Purpose: add new node to the tree; keep ascending order

	if (!(*rootPP)) {
		*rootPP = toAddP;
	}
	else {
		struct Node* parent = ascendPosPar(toAddP, *rootPP);

		if (toAddP->num <= parent->num) {
			parent->left = toAddP;
		}
		else {
			parent->right = toAddP;
		}
	}
	return;
}

struct Node* ascendPosPar(struct Node* toAddP, struct Node* startP) {
	// Purpose: give parent for new node according to ascending order

	struct Node* curP = startP;
	struct Node* prevCurP = startP;

	while (curP) {
		prevCurP = curP;
		if (toAddP->num <= curP->num) {
			curP = curP->left;
		}
		else {
			curP = curP->right;
		}
	}

	return prevCurP;
}

void inorderPrint(struct Node* rootP) {
	if (!rootP) {
		return;
	}

	inorderPrint(rootP->left);
	printf("%.4f ", rootP->num);
	inorderPrint(rootP->right);
	return;
}

struct Node* find(float toFind, struct Node** parentDestPP, struct Node* rootP) {
	/* Purpose: find fisrt node with given float value
	*
	* inorder search
	*/

	if ((!rootP) || (rootP->num == toFind)) {
		return rootP;
	}
	else {
		*parentDestPP = rootP;
	}

	struct Node* foundP = NULL;
	foundP = find(toFind, parentDestPP, rootP->left);
	if (!foundP) {
		*parentDestPP = rootP; /*
					   * setting parentDestPP to rootP again
					   * instead of keeping this value equal to rootP->left
					   */
		foundP = find(toFind, parentDestPP, rootP->right);
	}

	return foundP;
}

void deleteN(struct Node* toDelP, struct Node* parentP, struct Node** rootPP) {
	/* Purpose: delete given node
	 *
	 * with keeping ascending order by replacing deleted node
	 */

	keepOrder(toDelP, parentP, rootPP);
	free(toDelP);

	return;
}

void keepOrder(struct Node* toDelP, struct Node* parentP, struct Node** rootPP) {
	/* Purpose: place other node to deleted node position
	 *
	 * keep ascending order
	 */

	struct Node* replacementParentP;
	struct Node* replacementP = findRep(toDelP, &replacementParentP);

	replacementParentP->left = NULL; // deleting old position

	if (!parentP) { // if root is deleted
		*rootPP = replacementP;
	}
	else if (parentP->left == toDelP) {
		parentP->left = replacementP;
	}
	else {
		parentP->right = replacementP;
	}

	// update child nodes
	if (replacementP) {
		if ((!replacementP->left) && (toDelP->left != replacementP)) {
			replacementP->left = toDelP->left;
		}
		if ((!replacementP->right) && (toDelP->right != replacementP)) {
			replacementP->right = toDelP->right;
		}
	}

	return;
}

struct Node* findRep(struct Node* toReplaceP, struct Node** repParentDestPP) {
	// Purpose: search for the replacement of the deleted node to mantain order

	struct Node* replacementP = NULL;
	struct Node* parentP = toReplaceP;

	if ((toReplaceP->right) && (toReplaceP->left)) {
		// looking for the first greater node than deleted one

		replacementP = toReplaceP->right;
		while (replacementP->left) {
			parentP = replacementP;
			replacementP = replacementP->left;
		}
	}
	else if (hasOnlyRChild(toReplaceP)) {
		replacementP = toReplaceP->right;
	}
	else if (hasOnlyLChild(toReplaceP)) {
		replacementP = toReplaceP->left;
	}
	*repParentDestPP = parentP;

	return replacementP;
}

int hasOnlyRChild(struct Node* n) {
	// Purpose: check if node has only right child

	return n->right && !n->left;
}

int hasOnlyLChild(struct Node* n) {
	// Purpose: check if node has only left child

	return !n->right && n->left;
}

int height(struct Node* startNodeP) {
	/* Purpose: calculate height of tree,
	 *
	 * if empty return -1
	 */

	if (!startNodeP) {
		return 0;
	}
	int leftHeight = height(startNodeP->left) + 1;
	int rightHeight = height(startNodeP->right) + 1;

	return max(leftHeight, rightHeight);
}

int isBalanced(int treeSize, struct Node* rootP) {
	/* Purpose: check if tree is balanced
	 *
	 * check height of balanced tree with given size
	 * compare to actual height
	 */

	int actualHeight = height(rootP);
	int heightIfBalanced = (int)ceil(log(treeSize+1) / log(2));

	return actualHeight == heightIfBalanced;
}

int heightAndBalanceCheck(int* isBalancedDestP, struct Node* startNodeP) {
	/* Purpose: calculate height and check if tree is balanced
	 *
	 * write balance answer to isBalancedDest
	 */

	if (!startNodeP) {
		return 0;
	}
	int leftHeight = heightAndBalanceCheck(isBalancedDestP, startNodeP->left) + 1;
	int rightHeight = heightAndBalanceCheck(isBalancedDestP, startNodeP->right) + 1;

	if (*isBalancedDestP != FALSE) {
		if (abs(leftHeight - rightHeight) < 2) {
			*isBalancedDestP = TRUE;
		}
		else {
			*isBalancedDestP = FALSE;
		}
	}
	return max(leftHeight, rightHeight);
}

void balance(int treeSize, struct Node** rootPP) {
	/* Purpose: balance a tree
	 *
	 * first put it to array and then remake a tree from array
	 * balanced tree as a result
	 */

	int index = 0;
	struct Node** pointerArr = (struct Node**)malloc(treeSize * sizeof(struct Node*));

	treeToArr(pointerArr, &index, *rootPP);
	arrToBalancedTree(pointerArr, 0, treeSize - 1, rootPP);

	return;
}

void treeToArr(struct Node** arr, int* indexDestP, struct Node* rootP) {
	/* Purpose: put tree node pointers into the array
	 *
	 * ascending order
	 */

	if (!rootP) {
		return;
	}

	treeToArr(arr, indexDestP, rootP->left);
	arr[(*indexDestP)++] = rootP;
	treeToArr(arr, indexDestP, rootP->right);

	return;
}

void arrToBalancedTree(struct Node** arr, int startI, int endI, struct Node** rootPP) {
	/* Purpose: create tree from array of node pointers
	 *
	 * take node from mid of array as new node
	 * create two subarrays and work in recursive way
	 */

	if (startI > endI) { // end of array 
		*rootPP = NULL;
		return;
	}

	int mid = (startI + endI) / 2;
	*rootPP = arr[mid];

	arrToBalancedTree(arr, startI, mid - 1, &((*rootPP)->left)); // left subarray, left child
	arrToBalancedTree(arr, mid + 1, endI, &((*rootPP)->right)); // right subarray, right child

	return;
}