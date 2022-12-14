/*
 * Author: Jakub Cimochowski
 * Purpose: Basic menu in main function to conduct operations on List
 *
 * Language:  C
 */

#ifndef MENU_H
#define MENU_H

void runMenu();

int getState();

void printActions();

int confirmDel(float toDel);

void getLine(char* line, int lineSize);

void menuIteration(struct Node* rootP, struct Node* foundP, struct Node* foundParP, int* treeSizeP);

#endif /* menu.h */
