#include "LinkedList.h"

// create node with record data
Node *makenode(Record *dat){
	Node *pNode = (Node*)malloc(sizeof(Node));
	pNode->pNext = NULL;
	pNode->pPrev = NULL;
	pNode->data = dat;

	return pNode;
}

// inserts node at the front made with the data passed in
BOOL insertFront(List *pList, Record *dat) {
	BOOL success = FALSE;
	Node *pMem = NULL;
	Node *pTemp = NULL;
	pMem = makenode(dat);

	if ((pList->pHead == NULL) && (pMem != NULL)){	// if list is empty
		pList->pHead = pMem;
		pList->pTail = pMem;
		pList->size++;
		success = TRUE;
	}
	else {											// if the list is not empty
		pTemp = pList->pHead;
		pMem->pNext = pTemp;
		pTemp->pPrev = pMem;
		pList->pHead = pMem;
		pList->size++;
		success = TRUE;
	}
	
	return success;
}

// stores the list data into csv file
BOOL store(List *pList) {
	BOOL success = FALSE;
 	FILE *filepointer = fopen("temp.csv", "w+");
	Node *pCur = pList->pTail;
	char nameBuff[25];
	int index = 0;

	if(filepointer != NULL){
		success = TRUE;
		while (index < pList->size) {
			if (strstr(pCur->data->artist, ",") != NULL) {
				strcpy(nameBuff, "\"");
				strcat(nameBuff, pCur->data->artist);
				strcat(nameBuff, "\"");
			}
			else {
				strcpy(nameBuff, pCur->data->artist);
			}

			fprintf(filepointer, "%s,%s,%s,%s,%i:%i,%i,%i\n", nameBuff, pCur->data->albumTitle, pCur->data->songTitle, pCur->data->genre, pCur->data->songLength->minutes, pCur->data->songLength->seconds, pCur->data->timesPlayed, pCur->data->rating);
			pCur = pCur->pPrev;
			index++;
		}
		fclose(filepointer);
	}
	return success;
}

// loads/reloads information from csv file
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

// inserts new node with data designated by user
void insert(List *pList) {
	Record *rMem = NULL;
	Duration *dMem = NULL;
	BOOL done = FALSE;
	char userInput[50] = { '\0' };

	rMem = (Record*)malloc(sizeof(Record));
	dMem = (Duration*)malloc(sizeof(Duration));
	printf("what is the artist's name?: ");
	getInput(userInput);
	rMem->artist = (char*)malloc(strlen(userInput) + 1);
	strcpy(rMem->artist, userInput);
	
	printf("what is the album title?: ");
	getInput(userInput);
	rMem->albumTitle = (char*)malloc(strlen(userInput) + 1);
	strcpy(rMem->albumTitle, userInput);
	
	printf("what is the song title?: ");
	getInput(userInput);
	rMem->songTitle = (char*)malloc(strlen(userInput) + 1);
	strcpy(rMem->songTitle, userInput);
	
	printf("what is the genre you wish to specify?: ");
	getInput(userInput);
	rMem->genre = (char*)malloc(strlen(userInput) + 1);
	strcpy(rMem->genre, userInput);
	
	printf("how many minutes long is the song?: ");
	getInput(userInput);
	dMem->minutes = atoi(userInput);
	
	printf("...and how many seconds long is the song?: ");
	getInput(userInput);
	dMem->seconds = atoi(userInput);

	rMem->songLength = dMem;

	printf("how many 'times played' do you wish to specify?: ");
	getInput(userInput);
	rMem->timesPlayed = atoi(userInput);

	printf("what do you rate the song?: ");
	getInput(userInput);
	rMem->rating = atoi(userInput);

	insertFront(pList, rMem);
}

// delete by name of song
BOOL del(List *pList) {
	BOOL success = FALSE;
	BOOL exit = FALSE;
	char userInput[50] = { '\0' };
	Node *pCur = NULL;

	if (pList->size > 0) {
		while (exit == FALSE){
			printSongs(pList);
			printf("Which song would you like to delete? (\"exit\" to leave): ");
			getInput(userInput);

			pCur = getSong(pList, userInput);

			if (pCur != NULL) {
				removeNode(pList, pCur);
				clrscr();
				// remove node
			}
			else if (strcmp(userInput, "exit") == 0) {
				exit = TRUE;
			}
			else {
				printf("song not found\n");
			}
		}
	}
	return success;
}

// edit any values in any record
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
		freeList(subList);
		// user chooses artist and song to change
		while (recordToChange == NULL) {

			printSongs(list);
			printf("\nwhich artist would you like to look up? (\"exit\" to cancel): ");

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
					printf("\nwhich song would you like to edit?: ");
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

// changes the rating of a song
BOOL rate(List *pList){
	BOOL success = FALSE;
	BOOL exit = FALSE;
	char userInput[50] = { '\0' };
	int atoiInput = 0;
	Record *rMem = NULL;

	while (exit == FALSE) {
		printSongs(pList);
		printf("\nWhich song (by song name) do you want to change?: ");
		getInput(userInput);
		rMem = getRecord(pList, userInput);

		if (rMem != NULL) {
			while (exit == FALSE){
				printf("\nHow many stars do you wish to rate it?: ");
				getInput(userInput);
				atoiInput = atoi(userInput);
				// restrict rating from 1 to 5
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

// play playlist from the song selected
BOOL play(List *pList) {
	BOOL success = FALSE;
	BOOL exit = FALSE;
	char userInput[50] = { '\0' };
	Node *pStart = NULL;

	while (strcmp(userInput, "exit") != 0) {
		clrscr();
		printSongs(pList);
		printf("\nFrom which song (by song name) do you want to play? (\"exit\" to stop): ");
		getInput(userInput);
		pStart = getSong(pList, userInput);

		if (pStart == NULL)
			printf("song not found\n");

		while (pStart != NULL) {
			clrscr();
			printf("Currently Playing:\n%s\n%s\n%s\n", pStart->data->artist, pStart->data->albumTitle, pStart->data->songTitle);
			Sleep(2000);
			pStart->data->timesPlayed++;
			pStart = pStart->pNext;
			success = TRUE;
		}
	}
	return success;
}

// sorts the list in a pseudo insertion sort 
BOOL sort(List *pList) {
	BOOL exit = FALSE, success = FALSE;
	int length = pList->size, sorted = 0, type = 0;
	char userInput[50] = { '\0' };
	Node *i = NULL, *max = NULL;
	List sortedList;
	Record *rMem = NULL;
	sortedList.pHead = NULL;
	sortedList.pTail = NULL;
	sortedList.size = 0;

	// select type of data to sort by
	while(exit == FALSE){
		clrscr();
		printSongs(pList);
		printf("what would you like to sort the list by?\n");
		printf("(1) artist\n");
		printf("(2) album\n");
		printf("(3) rating\n");
		printf("(4) times played\n");

		type = atoi(getInput(userInput));
		
		// restrict type to 1 - 4
		if ((type > 0) && (type < 5)) {
			while (sorted != length) {
				i = pList->pHead;
				max = pList->pHead;
				// get the max of the pList
				while (i != NULL) {				
					if (nodecmp(max, i, type) < 0) {
						max = i;
					}
					i = i->pNext;
				}
				
				// insert max->data into front of sorted list
				popNode(pList, max);
				pList->size--;
				rMem = max->data;
				free(max);
				insertFront(&sortedList, rMem);
				sorted++;
			}

			// point pList head to new sorted list pHead (sorry this is hacky)
			pList->pHead = sortedList.pHead;
			pList->pTail = sortedList.pTail;
			pList->size = sortedList.size;
			sortedList.pHead = NULL;
			sortedList.pTail = NULL;
			sortedList.size = 0;
			success = TRUE;
			sorted = 0;
		}
		else if (strcmp(userInput, "exit") == 0) {
			return success;
		}
		else {
			printf("input not recognized, try again");
		}
	}
	return success;
}

// compares two nodes by the specified type 
int nodecmp(Node *n1, Node *n2, int type) {
	/*
	type = 1 :: artist
	type = 2 :: album
	type = 3 :: rating
	type = 4 :: times played
	*/
	int compare = 0;
	if (type == 1) {
		compare = strcmp(n1->data->artist, n2->data->artist);
	}
	else if (type == 2) {
		compare = strcmp(n1->data->albumTitle, n2->data->albumTitle);
	}
	else if (type == 3) {
		compare = n1->data->rating - n2->data->rating;
	}
	else {
		compare = n1->data->timesPlayed - n2->data->timesPlayed;
	}

	if (compare > 0)
		return 1;
	else if (compare < 0)
		return -1;
	else
		return 0;
}

// plays the songs of the list in random order
void shuffle(List *pList) {
	char userInput[50] = { '\0' };
	int songsPlayed = 0, ran = 0, position = 0, *check = NULL;
	Node *pCur = NULL;
	BOOL played = FALSE;
	time_t t;
	
	// gets random number and checks it against indicator array
	// this way wastes cycles if there are collisions 
	if(pList->pHead != NULL){
		pCur = pList->pHead;
		check = malloc((pList->size) * sizeof(int));
		while (songsPlayed != (pList->size)) {		
			ran = ((rand() % pList->size));
			if (check[ran] != 1) {
				check[ran] = 1;
				played = FALSE;
				while(played == FALSE){
					if (position > ran) {
						// move position and pcur backwards in list
						pCur = pCur->pPrev;
						position--;
					}
					else if (position < ran) {
						// move position and pcur forwards in list
						pCur = pCur->pNext;
						position++;
					}
					else {
						printf("playing song: %s\n", pCur->data->songTitle);
						Sleep(1000);
						pCur->data->timesPlayed++;
						// play song
						songsPlayed++;
						played = TRUE;
					}
				}
			}
		}
	}
}

// returns a sublist of songs by the *artist 
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

// return the pointer to the record of the name *song
Record *getRecord(List *sList, char *song) {
	Record *rec = NULL;
	Node *subListHead = sList->pHead;

	while (subListHead != NULL) {
		if (strncmp(subListHead->data->songTitle, song, 50) == 0) {
			rec = subListHead->data;
		}
		subListHead = subListHead->pNext;
	}
	return rec;
}

// get the pointer to the node for the song by the name *song
Node *getSong(List *pList, char *song) {
	Node *listHead = pList->pHead;

	while (listHead != NULL) {
		if (strcmp(listHead->data->songTitle, song) == 0) {
			return listHead;
		}
		listHead = listHead->pNext;
	}
	return NULL;
}

// deletes all nodes into list and frees all memory
void freeList(List *pList) {
	BOOL removed = TRUE;
	Node *pCur = NULL;

	while (removed == TRUE) {
		pCur = pList->pHead;
		removed = removeNode(pList, pCur);
	}
}

// removes the node passed in
BOOL removeNode(List *pList, Node *remNode){
	BOOL success = FALSE;
	Node *pAfter = NULL;
	Node *pBefore = NULL;

	while(remNode != NULL){
		if (pList->size == 1) { // only node
			pList->pHead = NULL;
		}
		else if (remNode->pPrev == NULL) { // first node
			pAfter = remNode->pNext;
			pAfter->pPrev = NULL;
			pList->pHead = pAfter;
			remNode->pNext = NULL;
		}
		else if (remNode->pNext == NULL) { // last node
			pBefore = remNode->pPrev;
			pBefore->pNext = NULL;
			pList->pTail = pBefore;
			remNode->pPrev = NULL;
		}
		else  { // middle node
			pBefore = remNode->pPrev;
			pAfter = remNode->pNext;
			pBefore->pNext = pAfter;
			pAfter->pPrev = pBefore;
			remNode->pNext = NULL;
			remNode->pPrev = NULL;
		}

		// free the memory!!

		free(remNode->data->albumTitle);
		free(remNode->data->artist);
		free(remNode->data->genre);
		free(remNode->data->songLength);
		free(remNode->data->songTitle);
		free(remNode->data);
		free(remNode);
		remNode = NULL;
		pList->size--;

		success = TRUE;
	}

	return success;
}

// removes the node passed in without freeing or deleting
BOOL popNode(List *pList, Node *remNode) {
	BOOL success = FALSE;
	Node *pAfter = NULL;
	Node *pBefore = NULL;

	if (pList->size == 1) { // only node
		pList->pHead = NULL;
	}
	else if (remNode->pPrev == NULL) { // first node
		pAfter = remNode->pNext;
		pAfter->pPrev = NULL;
		pList->pHead = pAfter;
		remNode->pNext = NULL;
	}
	else if (remNode->pNext == NULL) { // last node
		pBefore = remNode->pPrev;
		pBefore->pNext = NULL;
		pList->pTail = pBefore;
		remNode->pPrev = NULL;
	}
	else { // middle node
		pBefore = remNode->pPrev;
		pAfter = remNode->pNext;
		pBefore->pNext = pAfter;
		pAfter->pPrev = pBefore;
		remNode->pNext = NULL;
		remNode->pPrev = NULL;
	}
	success = TRUE;

	return success;
}

// 
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
		printf("Artist: \t%s\n", pCur->data->artist);
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
Function:	printSongs
input:		pList to be printed
output:		(none)
************************/
void printSongs(List *list) {
	int i = 1;
	Node *pCur = (list)->pHead;
	while (pCur != NULL) {
		printf("%i: %s - %s : %s (rating) %i (times played) %i\n", i, pCur->data->artist, pCur->data->songTitle, pCur->data->albumTitle, pCur->data->rating , pCur->data->timesPlayed);
		pCur = pCur->pNext;
		i++;
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
	printf("(11/\"exit\") exit\n");
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
char *getInput(char *in) {
	fgets(in, 50, stdin);
	if (in[strlen(in) - 1] == '\n')
		in[strlen(in) - 1] = '\0';

	return in;
}