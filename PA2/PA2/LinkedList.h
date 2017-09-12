#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>

typedef struct duration
{
	int minutes;
	int seconds;
} Duration;

typedef struct record
{
	char *artist;
	char *albumTitle;
	char *songTitle;
	char *genre;
	Duration *songLength;
	int timesPlayed;
	int rating;
} Record;

typedef struct node
{
	Record *data;
	struct node *pNext;
	struct node *pPrev;
} Node;

typedef enum boolean {
	FALSE, TRUE
} Boolean;

/***********************
Function:	makeNode
input:		record
output:		pointer to new node with record
************************/
Node *makenode(Record *dat);

/***********************
Function:	insertNode
input:		pList and node to insert
output:		1 for successfully allocating space for a node; 0 otherwise
************************/
int insertFront(Node **pList, Record *dat);

/***********************
Function:	deleteNode
input:		pList and record to be deleted
output:		1 for successfully deleting node; 0 otherwise (node didnt exist)
************************/
Boolean deletenode(Node **pList, Node *dat);

/***********************
Function:	printList
input:		pList to be printed
output:		(none)
************************/
void printList(Node *Plist);

int load(Node *lis);

#endif