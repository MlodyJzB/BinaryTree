#include <stdio.h>
#include <stdlib.h>

struct Node {
	float num;
	struct Node* left;
	struct Node* right;
};

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
	struct Node* parentP = NULL;

	struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
	initN(4, n1);
	
	struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));
	initN(5, n2);

	struct Node *n3 = (struct Node*)malloc(sizeof(struct Node));
	initN(7, n3);

	struct Node* n4 = (struct Node*)malloc(sizeof(struct Node));
	initN(3.5, n4);

	struct Node* n5 = (struct Node*)malloc(sizeof(struct Node));
	initN(4.5, n5);

	struct Node* n6 = (struct Node*)malloc(sizeof(struct Node));
	initN(6, n6);

	struct Node* n7 = (struct Node*)malloc(sizeof(struct Node));
	initN(8, n7);

	struct Node* n8 = (struct Node*)malloc(sizeof(struct Node));
	initN(4.2, n8);

	struct Node* n9 = (struct Node*)malloc(sizeof(struct Node));
	initN(4.6, n9);

	ascendAdd(n1, &rootP);
	ascendAdd(n2, &rootP);
	ascendAdd(n3, &rootP);
	ascendAdd(n4, &rootP);
	ascendAdd(n5, &rootP);
	ascendAdd(n6, &rootP);
	ascendAdd(n7, &rootP);
	ascendAdd(n8, &rootP);
	ascendAdd(n9, &rootP);

	struct Node* found3 = find(5, &parentP, rootP);
	delete(found3, parentP, &rootP);
	return 0;
}

void printActions() {
	system("cls");
	printf("Possible actions: \n1 - Add item\n2 - Delete item\n3 - Find item\n4 - Edit item\n5 - Show all items from beginning\n6 - Show all items from end\n0 - Exit\n");
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
	struct Node* cur = startP;
	struct Node* prevCur = startP;

	while (cur) {
		prevCur = cur;
		if (toAddP->num <= cur->num) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	return prevCur;
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

	struct Node* found = NULL;
	found = find(toFind, parentDestPP, rootP->left);
	if (!found) {
		*parentDestPP = rootP;
		found = find(toFind, parentDestPP, rootP->right);
	}

	return found;
}

void delete(struct Node* toDelP, struct Node* parentP, struct Node** rootPP) {
	keepOrder(toDelP, parentP, rootPP);
	free(toDelP);

	return;
}

void keepOrder(struct Node* toDelP, struct Node* parentP, struct Node** rootPP) {
	struct Node* repParent;
	struct Node* rep = findRep(toDelP, &repParent);

	repParent->left = NULL;

	if (!parentP) {
		*rootPP = rep;
	}
	else if (parentP->left == toDelP) {
		parentP->left = rep;
	}
	else {
		parentP->right = rep;
	}

	if (rep) {
		if ((!rep->left) && (toDelP->left != rep)) {
			rep->left = toDelP->left;
		}
		if ((!rep->right) && (toDelP->right != rep)) {
			rep->right = toDelP->right;
		}
	}

	return;
}

struct Node* findRep(struct Node* toReplaceP, struct Node** repParentDestPP) {
	 // search for the replacement of the deleted node to mantain order
	
	struct Node* replacement = NULL;
	struct Node* parent = toReplaceP;
	
	if ((toReplaceP->right) && (toReplaceP->left)) {
		replacement = toReplaceP->right;
		while (replacement->left) {
			parent = replacement;
			replacement = replacement->left;
		}
	}
	else if ((toReplaceP->right) && !(toReplaceP->left)) {
		replacement = toReplaceP->right;
		parent = toReplaceP;
	}
	else if (!(toReplaceP->right) && (toReplaceP->left)) {
		replacement = toReplaceP->left;
		parent = toReplaceP;
	}
	*repParentDestPP = parent;

	return replacement;
}
