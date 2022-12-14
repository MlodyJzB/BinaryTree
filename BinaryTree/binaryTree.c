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
#include "../BinaryTree/treeMethods.h"

// defines for actions
#define ADD 1
#define DEL 2
#define FIND 3
#define DISP 4
#define HEIGHT 5
#define ISBALANCED 6
#define HEIGHTANDBALANCED 7
#define BALANCE 8
#define EXIT 0

// defines for True and false
#define TRUE 1
#define FALSE 0

int getState();

void printActions();

int confirmDel(float toDel);

void getLine(char* line, size_t lineSize);

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
			printf("\nFloat added successfully!\n");
			_getch();

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
			printf("Floats: ");
			inorderPrint(rootP);
			printf("\n");
			_getch();
			break;
		}

		case HEIGHT: {
			int h = height(rootP);
			if (h == 0) {
				printf("Tree is empty!\n");
			}
			else {
				printf("Height: %d\n", h);
			}
			_getch();
			break;
		}

		case ISBALANCED: {
			if (treeSize == 0) {
				printf("Tree is empty");
			}
			else if (isBalanced(treeSize, rootP)) {
				printf("Tree is balanced.");
			}
			else {
				printf("Tree is not balanced.");
			}
			_getch();
			break;
		}

		case HEIGHTANDBALANCED: {
			int isBal = TRUE;
			int height = heightAndBalanceCheck(&isBal, rootP);
			if (height == 0){
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
			printf("Tree was balanced successfully!");
			_getch();
			break;
		}

		case EXIT: {
			return 0;
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

	scanf_s("%d", &state);
	while ((state < 0) || (state > 8)) {
		printf("Incorrect action! Try again: ");
		scanf_s("%d", &state);
		getchar();
	}

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
			"6 - Balance check\n"
			"7 - Height and balance check\n"
			"8 - Balance\n"
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
