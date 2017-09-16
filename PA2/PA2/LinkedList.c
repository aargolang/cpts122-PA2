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
			pList->size++;
		}
	}
	else { // if the list is not empty

		pTemp = (pList)->pHead;

		while (pTemp->pNext != NULL){
			pTemp = pTemp->pNext;
		}
	
		pTemp->pNext = pMem;
		pMem->pPrev = pTemp;
		pList->size++;
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
		rMem->songTitle = (char*)malloc((strlen(strBuff) + 1) * sizeof(char));
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

/***********************
Function:	getArtist
input:		list, subList, artists name
output:		number of songs found by the artist
************************/
int getArtist(List *pList, List *sList, char *artist) {
	int count = 0;
	Node *listHead = pList->pHead;

	while (listHead->pNext != NULL) {
		// if the artist if found then copy the pointer to the record into the sublist
		if (strncmp(listHead->data->artist, artist, 50) == 0) {
			insertFront(sList, listHead->data);
			count++;
		}
		listHead = listHead->pNext;
	}

	return count;
}

/***********************
Function:	getRecord
input:		sublist, songname
output:		pointer to the record to be changed, NULL if search failed
************************/
Record *getRecord(List *sList, char *song) {
	Record *rec = NULL;
	Node *subListHead = sList->pHead;

	while (subListHead != NULL) {
		// return the pointer to the record of the name "*song"
		printf("songTitle: %s\nsong: %s\n", subListHead->data->songTitle, song);
		if (strncmp(subListHead->data->songTitle, song, 50) == 0) {
			rec = subListHead->data;
		}
		subListHead = subListHead->pNext;
	}
	return rec;
}

/***********************
Function:	resetSubList
input:		sublist
output:		none
************************/
void resetSubList(List *sList) {
	
	Node *listHead = sList->pHead;
	Node *temp;

	while (listHead != NULL) {
		// free all of the nodes in the sublist, not supposed to free record data
		listHead->data = NULL;
		listHead->pPrev = NULL;
		temp = listHead;
		listHead = listHead->pNext;
		free(temp);
	}
}

/***********************
Function:	edit
input:		changes values in the records
output:		TRUE if successful
************************/
Boolean edit(List *list){
	List subList;
	subList.pHead = NULL;
	subList.pTail = NULL;
	subList.size = 0;
	
	Record *recordToChange = NULL;
	Boolean edited = FALSE;
	Boolean escape = FALSE;
	char userInput[51] = { '0' };
	int songCount = 0;

	while (escape == FALSE) {
		resetSubList(&subList);
		// user chooses artist and song to change
		while (recordToChange == NULL) {
			
			printf("which artist would you like to look up?: (\"exit\" to cancel)");
			scanf_s("%s", userInput, 50);

			songCount = getArtist(list, &subList, userInput);

			if (strncmp(userInput, "exit", 50) == 0) {
				return edited;
			}
			else if (songCount == 0) {
				printf("Artist not found\n");
			}
			else if (songCount == 1) {
				recordToChange = subList.pHead->data;
			}
			else {
				while (recordToChange == NULL){
					clrscr();
					printList(&subList);
					printf("which song would you like to edit?: ");
					clear();
					fgets(userInput, 50, stdin);
					if (userInput[strlen(userInput) - 1] == '\n')
						userInput[strlen(userInput) - 1] = '\0';

					recordToChange = getRecord(&subList, userInput);
					if (recordToChange == NULL) {
						printf("\ninput not recognized");
					}
				}
			}
		}

		// user edits the song chosen
		while (recordToChange != NULL) {
			clrscr();
			printEditMenu();
			printf("choose the attribute to change: (\"exit\" when finished)\n");
			scanf_s("%s", userInput, 50);
			switch (atoi(userInput)) {
			case 1:
				printf("case 1\n");
				break;
			case 2:
				printf("case 2\n");
				break;
			case 3:
				printf("case 3\n");
				break;
			case 4:
				printf("case 4\n");
				break;
			case 5:
				printf("case 5\n");
				break;
			case 6:
				printf("case 6\n");
				break;
			case 7:
				printf("case 7\n");
				break;
			default:
				if (strncmp(userInput, "exit", 50) == 0) {
					recordToChange = NULL;
				}
				else {
					printf("input not recognized");
				}
			}
		}
	}
	return edited;
}

/***********************
Function:	printList
input:		pList to be printed
output:		(none)
************************/
void printList(List *list) {
	Node *pCur = (list)->pHead;

	//while (pCur->pNext != NULL) {
	//	printf("\nArtist: \t%s\n", pCur->pNext->data->artist);
	//	printf("Album: \t\t%s\n", pCur->pNext->data->albumTitle);
	//	printf("Title: \t\t%s\n", pCur->pNext->data->songTitle);
	//	printf("Genre: \t\t%s\n", pCur->pNext->data->genre);
	//	printf("Length: \t%i:", pCur->pNext->data->songLength->minutes);
	//	printf("%i\n", pCur->pNext->data->songLength->seconds);
	//	printf("Times Played: \t%i\n", pCur->pNext->data->timesPlayed);
	//	printf("Rating: \t%i\n\n", pCur->pNext->data->rating);
	//	pCur = pCur->pNext;
	//}

	while (pCur != NULL) {
		printf("\nArtist: \t%s\n", pCur->data->artist);
		printf("Album: \t\t%s\n", pCur->data->albumTitle);
		printf("Title: \t\t%s\n", pCur->data->songTitle);
		printf("Genre: \t\t%s\n", pCur->data->genre);
		printf("Length: \t%i:", pCur->data->songLength->minutes);
		printf("%i\n", pCur->data->songLength->seconds);
		printf("Times Played: \t%i\n", pCur->data->timesPlayed);
		printf("Rating: \t%i\n\n", pCur->data->rating);
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
	printf("(1) Artist\n");
	printf("(2) Album title\n");
	printf("(3) Song title\n");
	printf("(4) Genre\n");
	printf("(5) Song length\n");
	printf("(6) Times played\n");
	printf("(7) rating\n");
}

// clears the screen. nuff said.
void clrscr(){
	system("@cls||clear");
}

void clear(void)
{
	while (getchar() != '\n');
}