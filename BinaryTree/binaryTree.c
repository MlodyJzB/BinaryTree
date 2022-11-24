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

int main() {
	struct Node* root = NULL;
	struct Node n1;
	initn(9, &n1);
	
	struct Node n2;
	initn(10, &n2);

	struct Node n3;
	initn(9, &n3);

	ascendadd(&n1, &root);
	ascendadd(&n2, &root);
	ascendadd(&n3, &root);

	inorderprint(root);
}

void printActions() {
	system("cls");
	printf("Possible actions: \n1 - Add item\n2 - Delete item\n3 - Find item\n4 - Edit item\n5 - Show all items from beginning\n6 - Show all items from end\n0 - Exit\n");
}

void initN(float num, struct Node* n) {
	n->num = num;
	n->left = NULL;
	n->right = NULL;
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
}