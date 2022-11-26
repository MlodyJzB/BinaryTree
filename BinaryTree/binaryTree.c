#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// defines for actions
#define ADD 1
#define DEL 2
#define FIND 3
#define DISP 4
#define EXIT 0

struct Node {
	float num;
	struct Node* left;
	struct Node* right;
};

int getState();

void printActions();

void initN(float num, struct Node* nP);

void ascendAdd(struct Node* toAddP, struct Node** rootPP);

struct Node* ascendPosPar(struct Node* toAddP, struct Node* startP);

void inorderPrint(struct Node* rootP);

struct Node* find(float toFind, struct Node** parentDestPP, struct Node* rootP);

void delete(struct Node** toDelPP, struct Node** rootPP);

void keepOrder(struct Node* toRepP, struct Node* parentP, struct Node** rootPP);

struct Node* findRep(struct Node* toReplaceP, struct Node** repParentDestPP);

int main() {
	struct Node* rootP = NULL;
	struct Node* foundP = NULL;
	struct Node* foundParP = NULL;
	
	while (1) {
		printActions();
		printf("\nChoose action: ");

		int state = getState();

		switch (state) {
		case ADD: {
			float f;
			printf("Provide float to add: ");
			scanf_s("%f", &f);

			struct Node* toAddP = (struct Node*)malloc(sizeof(struct Node));
			initN(f, toAddP);

			ascendAdd(toAddP, &rootP);
			break;
		}

		case DEL: {
			break;
		}

		case FIND: {
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

		default: {
			printf("Incorrect action!\n");
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
	} while ((state < 0) || (state > 6));

	return state;
}

void printActions() {
	system("cls");
	printf("Possible actions: \n1 - Add item\n2 - Delete item\n3 - Find item\n4 - Show\n0 - Exit\n");
	return;
}

void initN(float num, struct Node* nP) {
	nP->num = num;
	nP->left = NULL;
	nP->right = NULL;
	return;
}

void ascendAdd(struct Node* toAddP, struct Node** rootPP) {
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
	if ((!rootP)||(rootP->num == toFind)) {
		return rootP;
	}
	else {
		*parentDestPP = rootP;
	}

	struct Node* foundP = NULL;
	foundP = find(toFind, parentDestPP, rootP->left);
	if (!foundP) {
		*parentDestPP = rootP;
		foundP = find(toFind, parentDestPP, rootP->right);
	}

	return foundP;
}

void delete(struct Node* toDelP, struct Node* parentP, struct Node** rootPP) {
	keepOrder(toDelP, parentP, rootPP);
	free(toDelP);

	return;
}

void keepOrder(struct Node* toDelP, struct Node* parentP, struct Node** rootPP) {
	struct Node* repParentP;
	struct Node* repP = findRep(toDelP, &repParentP);

	repParentP->left = NULL;

	if (!parentP) {
		*rootPP = repP;
	}
	else if (parentP->left == toDelP) {
		parentP->left = repP;
	}
	else {
		parentP->right = repP;
	}

	if (repP) {
		if ((!repP->left) && (toDelP->left != repP)) {
			repP->left = toDelP->left;
		}
		if ((!repP->right) && (toDelP->right != repP)) {
			repP->right = toDelP->right;
		}
	}

	return;
}

struct Node* findRep(struct Node* toReplaceP, struct Node** repParentDestPP) {
	 // search for the replacement of the deleted node to mantain order
	
	struct Node* replacementP = NULL;
	struct Node* parentP = toReplaceP;
	
	if ((toReplaceP->right) && (toReplaceP->left)) {
		replacementP = toReplaceP->right;
		while (replacementP->left) {
			parentP = replacementP;
			replacementP = replacementP->left;
		}
	}
	else if ((toReplaceP->right) && !(toReplaceP->left)) {
		replacementP = toReplaceP->right;
		parentP = toReplaceP;
	}
	else if (!(toReplaceP->right) && (toReplaceP->left)) {
		replacementP = toReplaceP->left;
		parentP = toReplaceP;
	}
	*repParentDestPP = parentP;

	return replacementP;
}
