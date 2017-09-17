#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef enum boolean {
	FALSE, TRUE
} Boolean;

typedef struct list {
	int size;
	Node *pHead;
	Node *pTail;
} List;

Node *makenode(Record *dat);
Boolean insertFront(List *pList, Record *dat);
Boolean deletenode(Node ***pList, Node *dat);
Boolean load(List *list);
Boolean edit(List *list);
int getArtist(List *pList, List *sList, char *artist);
Record *getRecord(List *sList, char *song);
void resetSubList(List *sList);
void printList(List *list);
void printMenu();
void printEditMenu();
void getInput(char *in);
void clrscr();


#endif