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

Node *makenode(Record *dat);
int insertFront(Node ***pList, Record *dat);
Boolean deletenode(Node **pList, Node *dat);
int load(Node **lis);
void printList(Node *Plist);
void printMenu();

#endif