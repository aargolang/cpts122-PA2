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
output:			TRUE for successfully allocating space for a node; FALSE otherwise
description:	insert node at the (!!!)FRONT(!!!) of the list
************************/
BOOL insertFront(List *pList, Record *dat) {
	BOOL success = FALSE;
	Node *pMem = NULL;
	Node *pTemp = NULL;
	pMem = makenode(dat);

	if ((pList->pHead == NULL) && (pMem != NULL)){ 
		// list is empty
		pList->pHead = pMem;
		pList->pTail = pMem;
		pList->size++;
		success = TRUE;
	}
	else { // if the list is not empty
		pTemp = pList->pHead;
		pMem->pNext = pTemp;
		pTemp->pPrev = pMem;
		pList->pHead = pMem;
		pList->size++;
		success = TRUE;
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
output:		TRUE for successfully loading, FALSE otherwise
************************/
BOOL load(List *pList) {
	BOOL success = 0;
	int index = 1;
	FILE *filePointer = NULL;
	char line[100] = { '\0' }, copyLine[100] = { '\0' }, strBuff[100];
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
		success = TRUE;
		index++;
	}

	rMem = NULL;
	dMem = NULL;

	return success;
}

/***********************
Function:	edit
input:		changes values in the records
output:		TRUE if successful, FALSE if otherwise
************************/
BOOL edit(List *list) {
	List subList;
	subList.pHead = NULL;
	subList.pTail = NULL;
	subList.size = 0;
	Record *recordToChange = NULL;
	BOOL edited = FALSE;
	BOOL escape = FALSE;
	char userInput[51] = { '0' };
	int songCount = 0;

	while (escape == FALSE) {
		resetSubList(&subList);
		// user chooses artist and song to change
		while (recordToChange == NULL) {

			printf("which artist would you like to look up? (\"exit\" to cancel): ");
			getInput(userInput);

			printf("debug");

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
				while (recordToChange == NULL) {
					clrscr();
					printList(&subList);
					printf("which song would you like to edit?: ");
					getInput(userInput);
					recordToChange = getRecord(&subList, userInput);
					if (recordToChange == NULL) {
						printf("\ninput not recognized");
					}
				}
			}
		}
		clrscr();

		// user edits the song chosen
		while (recordToChange != NULL) {
			clrscr();
			printf("artist: %s\n", recordToChange->artist);
			printf("album title: %s\n", recordToChange->albumTitle);
			printf("song title: %s\n", recordToChange->songTitle);
			printf("genre: %s\n", recordToChange->genre);
			printf("song length(minutes): %i\n", recordToChange->songLength->minutes);
			printf("song length(seconds): %i\n", recordToChange->songLength->seconds);
			printf("times played: %i\n", recordToChange->timesPlayed);
			printf("rating: %i\n\n", recordToChange->rating);

			printEditMenu();
			printf("choose the attribute to change? (\"exit\" when finished): ");
			// canf_s("%s", userInput, 50);
			getInput(userInput);
			switch (atoi(userInput)) {
			case 1:
				printf("what would you like to change Artist to?: ");
				getInput(userInput);
				strcpy(recordToChange->artist, userInput);
				clrscr();
				break;
			case 2:
				printf("What would you like to change Album title to?: ");
				getInput(userInput);
				strcpy(recordToChange->albumTitle, userInput);
				clrscr();
				break;
			case 3:
				printf("What would you like to change Song title to?: ");
				getInput(userInput);
				strcpy(recordToChange->songTitle, userInput);
				clrscr();
				break;
			case 4:
				printf("What would you like to change Genre to?: ");
				getInput(userInput);
				strcpy(recordToChange->genre, userInput);
				clrscr();
				break;
			case 5:
				printf("what would youl like minutes changed to?: ");
				getInput(userInput);
				recordToChange->songLength->minutes = atoi(userInput);
				printf("what would youl like seconds changed to?");
				getInput(userInput);
				recordToChange->songLength->seconds = atoi(userInput);
				clrscr();
				break;
			case 6:
				printf("what would youl like times played changed to?: ");
				getInput(userInput);
				recordToChange->timesPlayed = atoi(userInput);
				clrscr();
				break;
			case 7:
				printf("what would youl like rating changed to?: ");
				getInput(userInput);
				recordToChange->rating = atoi(userInput);
				clrscr();
				break;
			default:
				if (strncmp(userInput, "exit", 50) == 0) {
					recordToChange = NULL;
					clrscr();
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
Function:	edit
input:		changes values in the records
output:		TRUE if successful, FALSE if otherwise
************************/
BOOL rate(List *pList){
	BOOL success = FALSE;
	BOOL exit = FALSE;
	char userInput[50] = { '\0' };
	int atoiInput = 0;
	Record *rMem = NULL;

	while (exit == FALSE) {
		printf("Which song (by song name) do you want to change?: ");
		getInput(userInput);
		rMem = getRecord(pList, userInput);

		if (rMem != NULL) {
			while (exit == FALSE){
				printf("How many stars do you wish to rate it?: ");
				getInput(userInput);
				atoiInput = atoi(userInput);
				if ((atoiInput > 0) && (atoiInput < 6)){
					rMem->rating = atoiInput;
					success = TRUE;
					exit = TRUE;
				}
				else {
					printf("value needs to be between 1 and 5\n");
				}
			}
		}
		else {
			printf("Song not found \n");
		}
	}

	return success;
}

/***********************
Function:	edit
input:		changes values in the records
output:		TRUE if successful, FALSE if otherwise
************************/
BOOL play(List *pList) {
	BOOL success = FALSE;
	BOOL exit = FALSE;
	char userInput[50] = { '\0' };
	Record *rMem = NULL;

	while (strcmp(userInput, "exit") != 0) {
		clrscr();
		printList(pList);
		printf("Which song (by song name) do you want to play? (\"exit\" to stop): ");
		getInput(userInput);
		rMem = getRecord(pList, userInput);

		if (rMem != NULL) {
			printf("playing %s - %s\n", rMem->artist, rMem->songTitle);
			Sleep(3000);
			rMem == NULL;
			success = TRUE;
		}
		else {
			printf("Song not found \n");
		}
	}

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
		// printf("songTitle: %s\nsong: %s\n", subListHead->data->songTitle, song);
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

	while (sList->pHead != NULL) {
		// free all of the nodes in the sublist, not supposed to free record data
		sList->pHead->data = NULL;
		sList->pHead->pPrev = NULL;
		temp = sList->pHead;
		sList->pHead = sList->pHead->pNext;
		temp->pNext = NULL;
		free(temp);
		sList->size--;
	}
	sList->pTail = NULL;
}

/***********************
Function:	printList
input:		pList to be printed
output:		(none)
************************/
void printList(List *list) {
	Node *pCur = (list)->pHead;
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
void clrscr() {
	system("@cls||clear");
}

// gets input in a smart way
char *getInput(char *in)
{
	//clear();
	fgets(in, 50, stdin);
	if (in[strlen(in) - 1] == '\n')
		in[strlen(in) - 1] = '\0';

	return in;
}