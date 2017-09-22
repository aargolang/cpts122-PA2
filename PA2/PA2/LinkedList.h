#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct duration{
	int minutes;
	int seconds;
} Duration;

typedef struct record {
	char *artist;
	char *albumTitle;
	char *songTitle;
	char *genre;
	Duration *songLength;
	int timesPlayed;
	int rating;
} Record;

typedef struct node {
	Record *data;
	struct node *pNext;
	struct node *pPrev;
} Node;

typedef struct list {
	int size;
	Node *pHead;
	Node *pTail;
} List;

Node *makenode(Record *dat);
BOOL insertFront(List *pList, Record *dat);
BOOL store(List *pList);
BOOL load(List *list);
void insert(List *pList);
BOOL del(List *pList);
BOOL edit(List *list);
BOOL rate(List *pList);
BOOL play(List *list);
void shuffle(List *pList);
int getArtist(List *pList, List *sList, char *artist);
Record *getRecord(List *sList, char *song);
Node *getSong(List *pList, char *song);
void freeList(List *pList);
BOOL removeNode(List *pList, Node *delNode);
void resetSubList(List *sList);
void printList(List *list);
void printSongs(List *list);
void printMenu();
void printEditMenu();
void clrscr();
char *getInput(char *in);

#endif