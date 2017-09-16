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
int insertFront(List *pList, Record *dat){
	int success = 1;
	Node *pMem = NULL;
	Node *pTemp = NULL;
	pMem = makenode(dat);

	if ((pList)->pHead == NULL){ // list is empty
		if (pMem == NULL){
			success = 0;
		}
		else{
			(pList)->pHead = pMem;
			(pList)->pTail = pMem;
		}
	}
	else { // if the list is not empty

		pTemp = (pList)->pHead;

		while (pTemp->pNext != NULL){
			pTemp = pTemp->pNext;
		}
	
		pTemp->pNext = pMem;
		pMem->pPrev = pTemp;
	}
	return success;
}

/***********************
Function:	deleteNode
input:		pList and record to be deleted
output:		1 for successfully deleting node; 0 otherwise (node didnt exist)
************************/
int deletenode(Node ***pList, Node *dat){
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
Function:	load
input:		read from file into list
output:		1 for successfully loading, 0 otherwise
************************/
int load(List *pList) {
	int success = 0, index = 1;
	FILE *filePointer = NULL;
	char line[100] = { '\0' }, copyLine[100] = { '\0' };
	char strBuff[100];
	Record *rMem = NULL;
	Duration *dMem = NULL;

	filePointer = fopen("musicPlayList.csv", "r");


	while (fgets(line, 100, filePointer) != NULL) {
		strcpy(copyLine, line);

		rMem = (Record*)malloc(sizeof(Record)); // record
		dMem = (Duration*)malloc(sizeof(Duration)); // duration

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

		insertFront(pList, rMem);

		index++;
	}

	rMem = NULL;
	dMem = NULL;

	return success;
}

int searchArtist(List *sList) {

	return 0;
}

/***********************
Function:	load
input:		read from file into list
output:		1 for successfully loading, 0 otherwise
************************/
int edit(List *list){
	List *subList = NULL;
	Record *recordToChange = NULL;
	Boolean ret = FALSE;
	char userInput[51] = { '0' };
	int songNumber = 0;

	printf("which artist would you like to look up?: ", userInput);

	songNumber = searchArtist(&subList);

	if (songNumber > 1) {
		// ask which song to edit
	}



	while (ret != 1) {
		printEditMenu();
		scanf_s("%s", userInput, 50);
		switch (atoi(userInput)) {
		case 1:
			clrscr();
			
			scanf_s("%s", userInput, 50);
			clrscr();
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			ret = TRUE;
			break;
		}
	}
}

/***********************
Function:	printList
input:		pList to be printed
output:		(none)
************************/
void printList(List *list) {
	Node *pCur = (list)->pHead;

	while (pCur->pNext != NULL) {
		printf("\nArtist: \t%s\n", pCur->pNext->data->artist);
		printf("Album: \t\t%s\n", pCur->pNext->data->albumTitle);
		printf("Title: \t\t%s\n", pCur->pNext->data->songTitle);
		printf("Genre: \t\t%s\n", pCur->pNext->data->genre);
		printf("Length: \t%i:", pCur->pNext->data->songLength->minutes);
		printf("%i\n", pCur->pNext->data->songLength->seconds);
		printf("Times Played: \t%i\n", pCur->pNext->data->timesPlayed);
		printf("Rating: \t%i\n\n", pCur->pNext->data->rating);
		pCur = pCur->pNext;
	}
}

/***********************
Function:	printMenu
input:		(none)
output:		(none)
************************/
void printMenu() {
	printf("(1) load\n");
	printf("(2) store\n");
	printf("(3) display\n");
	printf("(4) insert\n");
	printf("(5) delete\n");
	printf("(6) edit\n");
	printf("(7) sort\n");
	printf("(8) rate\n");
	printf("(9) play\n");
	printf("(10) shuffle\n");
	printf("(11) exit\n");
}

/***********************
Function:	printEditMenu
input:		(none)
output:		(none)
************************/
void printEditMenu() {
	printf("What attribute would you like to edit?\n");
	printf("(1) Artist\n");
	printf("(2) Album title\n");
	printf("(3) Song title\n");
	printf("(4) Genre\n");
	printf("(5) Song length\n");
	printf("(6) Times played\n");
	printf("(7) rating\n");
	printf("(8) return\n");
}

// clears the screen. nuff said.
void clrscr(){
	system("@cls||clear");
}