#include "LinkedList.h"

/***********************
Function:	makeNode
input:		record
output:		pointer to new node with record
************************/
Node *makenode(Record *dat){
	Node *pNode = (Node*)malloc(sizeof(Node));
	pNode->pNext = NULL;
	pNode->pPrev = NULL;
	pNode->data = dat;

	return pNode;
}

/***********************
Function:		insertFront
input:			pList and node to insert
output:			1 for successfully allocating space for a node; 0 otherwise
description:	insert node at the (!!!)FRONT(!!!) of the list
************************/
int insertFront(Node **pList, Record *dat)
{
	int success = 1;
	Node *pMem = NULL;
	Node *pTemp = NULL;
	pMem = makenode(dat);

	if ((*pList) == NULL){ // list is empty
		if (pMem == NULL){
			success = 0;
		}
		else{
			(pList) = pMem;
		}
	}
	else { // if the list is not empty
		pTemp = (pList);
		(pList) = pMem;
		pTemp->pPrev = pMem;
		pMem->pNext = pTemp;
		pMem->pPrev = (pList);
	}
	return success;
}

int load(Node *lis)
{
	int success = 0, index = 1;
	FILE *filePointer = NULL;
	char line[100] = { '\0' }, copyLine[100] = { '\0' };
	char strBuff[100];
	Record *rMem = NULL;
	Duration *dMem = NULL;

	filePointer = fopen("musicPlayList.csv", "r");
	rMem = (Record*)malloc(sizeof(Record)); // record
	dMem = (Duration*)malloc(sizeof(Duration)); // duration

	while (fgets(line, 100, filePointer) != NULL) {
		strcpy(copyLine, line);

		printf("playlist line = %s\n", line);
		printf("playlist copyLine = %s\n", copyLine);

		if (copyLine[0] == '"') {
			strcpy(strBuff, strtok(copyLine, "\""));
		}
		else {
			strncpy(strBuff, strtok(copyLine, ","), 50);
		}
		rMem->artist = (char*)malloc(strlen(strBuff) + 1);
		strcpy(rMem->artist, strBuff);

		strcpy(strBuff, strtok(NULL, ","));
		rMem->albumTitle = (char*)malloc(strlen(strBuff) + 1);
		strcpy(rMem->albumTitle, strBuff);

		strcpy(strBuff, strtok(NULL, ","));
		rMem->songTitle = (char*)malloc(strlen(strBuff) + 1);
		strcpy(rMem->songTitle, strBuff);

		strcpy(strBuff, strtok(NULL, ","));
		rMem->genre = (char*)malloc(strlen(strBuff) + 1);
		strcpy(rMem->genre, strBuff);

		strcpy(strBuff, strtok(NULL, ":"));
		dMem->minutes = atoi(strBuff);

		strcpy(strBuff, strtok(NULL, ","));
		dMem->seconds = atoi(strBuff);

		strcpy(strBuff, strtok(NULL, ","));
		rMem->timesPlayed = atoi(strBuff);

		strcpy(strBuff, strtok(NULL, ","));
		rMem->rating = atoi(strBuff);

		rMem->songLength = dMem;

		insertFront(lis, rMem);

		index++;
	}
	return success;
}

/***********************
Function:	deleteNode
input:		pList and record to be deleted
output:		1 for successfully deleting node; 0 otherwise (node didnt exist)
************************/
int deletenode(Node **pList, Node *dat)
{
	// TODO: needs to be revised to delete the node passed in
	Node *pTemp = *pList;

	if (*pList == NULL)
		return FALSE;
	else
	{
		*pList = pTemp->pNext;
		pTemp->pPrev = *pList;
		//free(pTemp->name);
		free(pTemp);
		return TRUE;
	}
}

/***********************
Function:	printList
input:		pList to be printed
output:		(none)
************************/
void printList(Node *dat)
{
	// TODO: write thiss
	printf("TODO: implement printList!\n");

}
