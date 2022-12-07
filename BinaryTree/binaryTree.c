/*
 * Author: Jakub Cimochowski
 * Purpose: Implementation of binary tree,
 *			Each node contains only one float value,
 *			Inorder traversal, ascending order,
 *			Basic menu in main function to conduct operations on List
 * Language:  C
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

// defines for actions
#define ADD 1
#define DEL 2
#define FIND 3
#define DISP 4
#define HEIGHT 5
#define HEIGHTANDBALANCED 6
#define BALANCE 7
#define EXIT 0

// defines for True and false
#define TRUE 1
#define FALSE 0

// tree height define
#define EMPTY -1

struct Node {
	float num;
	struct Node* left;
	struct Node* right;
};

int getState();

void printActions();

int confirmDel(float toDel);

void getLine(char* line, size_t lineSize);

void initN(float num, struct Node* nP);

void ascendAdd(struct Node* toAddP, struct Node** rootPP);

struct Node* ascendPosPar(struct Node* toAddP, struct Node* startP);

void inorderPrint(struct Node* rootP);

struct Node* find(float toFind, struct Node** parentDestPP, struct Node* rootP);

void deleteN(struct Node* toDelP, struct Node* parentP, struct Node** rootPP);

void keepOrder(struct Node* toRepP, struct Node* parentP, struct Node** rootPP);

struct Node* findRep(struct Node* toReplaceP, struct Node** repParentDestPP);

int hasOnlyRChild(struct Node* n);

int hasOnlyLChild(struct Node* n);

int height(struct Node* rootP);

void balance(int treeSize, struct Node** rootPP);

void treeToArr(struct Node** arr, int* indexDestP, struct Node* rootP);

void arrToBalancedTree(struct Node** arr, int startI, int endI, struct Node** rootPP);

int main() {
	struct Node* rootP = NULL;
	struct Node* foundP = NULL;
	struct Node* foundParP = NULL;
	int treeSize = 0;
	
	while (1) {
		// menu loop based on switch to run chosen actions

		printActions();
		printf("\nChoose action: ");

		int state = getState();

		switch (state) {
		case ADD: {
			float num;
			printf("Provide float to add: ");
			scanf_s("%f", &num);

			struct Node* toAddP = (struct Node*)malloc(sizeof(struct Node));
			initN(num, toAddP);

			ascendAdd(toAddP, &rootP);
			treeSize++;

			break;
		}

		case DEL: {
			if (foundP) {
				int conf = confirmDel(foundP->num);
				if (conf==TRUE) {
					printf("\n%.3f deleted.\n", foundP->num);
					deleteN(foundP, foundParP, &rootP);
					foundP = NULL;
					foundParP = NULL;
					treeSize--;
				}
				else {
					printf("\n%.3f was not deleted.\n", foundP->num);
				}
				_getch();
			}
			else {
				printf("\nProvide float to delete!\n");
				_getch();
			}
			break;
		}

		case FIND: {
			float num;
			printf("Provide float to find: ");
			scanf_s("%f", &num);

			foundP = find(num, &foundParP, rootP);

			if (!foundP) {
				printf("\nFloat not found!\n");
			}
			else {
				printf("\nFloat found.\n");
			}
			_getch();
			break;
		}

		case DISP: {
			inorderPrint(rootP);
			printf("\n");
			_getch();
			break;
		}

		case EXIT: {
			return 0;
			break;
		}

		case HEIGHT: {
			int h = height(rootP);
			if (h == EMPTY) {
				printf("Tree is empty!\n");
			}
			else {
				printf("Height: %d\n", h);
			}
			_getch();
			break;
		}

		case HEIGHTANDBALANCED: {
			int isBal = TRUE;
			int height = heightAndBalanceCheck(&isBal, rootP);
			if (height == EMPTY) {
				printf("Tree is empty!\n");
			}
			else {
				printf("Height: %d\n", height);
				if (isBal == TRUE) {
					printf("Tree is balanced.\n");
				}
				else {
					printf("Tree is not balanced.\n");
				}
			}
			_getch();
			break;
		}

		case BALANCE: {
			balance(treeSize, &rootP);
			break;
		}

		default: {
			printf("Incorrect action!\n");
			_getch();
		}

		}

		system("cls");
	}
}

int getState() {
	int state;

	do {
		scanf_s("%d", &state);
		getchar();
	} while ((state < 0) || (state > 7));

	return state;
}

void printActions() {
	system("cls");
	printf("Possible actions: \n"
			"1 - Add item\n"
			"2 - Delete item\n"
			"3 - Find item\n"
			"4 - Inorder print \n"
			"5 - Print height\n"
			"6 - Height and balance check\n"
			"0 - Exit\n");
	return;
}

int confirmDel(float toDel) {
	// Purpose: get answer if user is sure about node deletion

	printf("Are you sure you want to delete %.3f? [y/N]: ", toDel);
	char line[3]; // size for ans char, endl and null char
	char ans;
	do {
		getLine(line, sizeof(line));
		ans = tolower(line[0]); // tolower for easier comparison
		if ((ans == '\n') || (ans == 'n')) {
			return FALSE;
		}
		if (ans == 'y') {
			return TRUE;
		}
	} while (1);
}

void getLine(char* line, size_t lineSize) {
	// Purpose: get text line
	if (fgets(line, lineSize, stdin) == NULL) {
		printf("Input error.\n");
		exit(1);
	}
}

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

	if ((!rootP)||(rootP->num == toFind)) {
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
		return -1;
	}
	int leftHeight = height(startNodeP->left) + 1;
	int rightHeight = height(startNodeP->right) + 1;
	
	return max(leftHeight, rightHeight);
}

int heightAndBalanceCheck(int* isBalancedDestP, struct Node* startNodeP) {
	/* Purpose: calculate height of tree
	 *
	 * check if tree is balanced and write the answer to isBalancedDest
	 * if empty return -1
	 */

	if (!startNodeP) {
		return -1;
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
	 * balanced treeas a result
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

	if (startI > endI) {
		*rootPP = NULL;
		return;
	}

	int mid = (startI + endI) / 2;
	*rootPP = arr[mid];

	arrToBalancedTree(arr, startI, mid-1, &((*rootPP)->left));
	arrToBalancedTree(arr, mid+1, endI, &((*rootPP)->right));

	return;
}
