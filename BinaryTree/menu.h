/*
 * Author: Jakub Cimochowski
 * Purpose: Basic menu to conduct operations on List
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

void menuIteration(struct Node** rootPP, struct Node** foundPP, struct Node** foundParPP, int* treeSizeP);

#endif /* menu.h */
