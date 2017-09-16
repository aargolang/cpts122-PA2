#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>

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
	Node *pHead;
	Node *pTail;
} List;

Node *makenode(Record *dat);
int insertFront(List *pList, Record *dat);
Boolean deletenode(Node ***pList, Node *dat);
int load(List *list);
int searchArtist(List *sList);
int edit(List *list);
void printList(List *list);
void printMenu();
void printEditMenu();
void clrscr();

#endif