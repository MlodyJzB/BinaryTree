#include <stdio.h>
#include <stdlib.h>

struct Node {
	float num;
	struct Node* left;
	struct Node* right;
};

void printActions();

void initN(float num, struct Node* n);

void ascendAdd(struct Node* toAdd, struct Node** root);

struct Node* ascendPosPar(struct Node* toAdd, struct Node* start);

void inorderPrint(struct Node* root);

struct Node* find(float toFind, struct Node** parentDest, struct Node* root);

void delete(struct Node** toDel, struct Node** root);

void keepOrder(struct Node* toRep, struct Node* parent, struct Node** root);

struct Node* findRep(struct Node* toReplace, struct Node** repParentDest);

int main() {
	struct Node* root = NULL;
	struct Node* parent = NULL;

	struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
	initN(9, n1);
	
	struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));
	initN(8, n2);

	struct Node *n3 = (struct Node*)malloc(sizeof(struct Node));
	initN(10, n3);

	ascendAdd(n1, &root);
	ascendAdd(n2, &root);
	ascendAdd(n3, &root);

	
	struct Node* found3 = find(8, &parent, root);
	delete(found3, parent, &root);
	return 0;
}

void printActions() {
	system("cls");
	printf("Possible actions: \n1 - Add item\n2 - Delete item\n3 - Find item\n4 - Edit item\n5 - Show all items from beginning\n6 - Show all items from end\n0 - Exit\n");
	return;
}

void initN(float num, struct Node* n) {
	n->num = num;
	n->left = NULL;
	n->right = NULL;
	return;
}

void ascendAdd(struct Node* toAdd, struct Node** root) {
	if (!(*root)) {
		*root = toAdd;
	}
	else {
		struct Node* parent = ascendPosPar(toAdd, *root);

		if (toAdd->num <= parent->num) {
			parent->left = toAdd;
		}
		else {
			parent->right = toAdd;
		}
	}
	return;
}

struct Node* ascendPosPar(struct Node* toAdd, struct Node* start) {
	struct Node* cur = start;
	struct Node* prevCur = start;

	while (cur) {
		prevCur = cur;
		if (toAdd->num <= cur->num) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	return prevCur;
}

void inorderPrint(struct Node* root) {
	if (!root) {
		return;
	}

	inorderPrint(root->left);
	printf("%.4f ", root->num);
	inorderPrint(root->right);
	return;
}

struct Node* find(float toFind, struct Node** parentDest, struct Node* root) {
	if ((!root)||(root->num == toFind)) {
		return root;
	}
	else {
		*parentDest = root;
	}

	struct Node* found = NULL;
	found = find(toFind, parentDest, root->left);
	if (!found) {
		found = find(toFind, parentDest, root->right);
	}

	return found;
}

void delete(struct Node* toDel, struct Node* parent, struct Node** root) {
	keepOrder(toDel, parent, root);
	free(toDel);

	return;
}

void keepOrder(struct Node* toDel, struct Node* parent, struct Node** root) {
	struct Node* repParent;
	struct Node* rep = findRep(toDel, &repParent);

	repParent->left = NULL;

	if (!parent) {
		*root = rep;
	}
	else if (parent->left == toDel) {
		parent->left = rep;
	}
	else {
		parent->right = rep;
	}

	return;
}

//struct Node* findRep(struct Node* toReplace, struct Node** repParentDest) {
//	 // search for the replacement of the deleted node to mantain order
//	
//	struct Node* replacement;
//	struct Node* parent;
//	
//	if ((toReplace->right) && (toReplace->left)) {
//
//	}
//	else if ((toReplace->right) && !(toReplace->left)) {
//		replacement = toReplace->right;
//		parent = toReplace;
//	}
//	else if (!(toReplace->right) && (toReplace->left)) {
//		replacement = toReplace->left;
//		parent = toReplace;
//	}
//}

struct Node* findRep(struct Node* toReplace, struct Node** repParentDest) {
	// search for the replacement of the deleted node to ma2intain order
	
	struct Node* replacement;
	struct Node* parent = toReplace;

	if (!toReplace->right) {
		replacement = toReplace->left;
	}
	else {
		replacement = toReplace->right;
		while(replacement->left) {
			parent = replacement;
			replacement = replacement->left;
		}
	}
	*repParentDest = parent;

	return replacement;
}