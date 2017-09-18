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

//typedef enum BOOL {
//	FALSE, TRUE
//} BOOL;

typedef struct list {
	int size;
	Node *pHead;
	Node *pTail;
} List;


Node *makenode(Record *dat);
BOOL insertFront(List *pList, Record *dat);
BOOL deletenode(Node ***pList, Node *dat);
BOOL load(List *list);
BOOL edit(List *list);
BOOL play(List *list);
int getArtist(List *pList, List *sList, char *artist);
Record *getRecord(List *sList, char *song);
void resetSubList(List *sList);
char *getInput(char *in);
void printList(List *list);
void printMenu();
void printEditMenu();

void clrscr();

#endif