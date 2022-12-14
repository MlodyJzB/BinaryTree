#ifndef TREEMETHODS_H
#define TREEMETHODS_H

struct Node {
	float num;
	struct Node* left;
	struct Node* right;
};

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

int isBalanced(int treeSize, struct Node* rootP);

int heightAndBalanceCheck(int* isBalancedDestP, struct Node* startNodeP);

void balance(int treeSize, struct Node** rootPP);

void treeToArr(struct Node** arr, int* indexDestP, struct Node* rootP);

void arrToBalancedTree(struct Node** arr, int startI, int endI, struct Node** rootPP);

#endif /* treeMethods.h */