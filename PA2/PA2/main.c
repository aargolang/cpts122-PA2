/********************************
Name:			Arthur Lang
Assignment:		PA2 - Digital Music Manager
Date Started:	9/11/17

Description:	create and implement a imitation digital music manager
				to showcase the functionality of a doubly linked list
				and properties of a queue

Files:			- main.c
				- LinkedList.h
				- LinkedList.c
*********************************/

#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int load(Node *lis)
//{
//	int success = 0, index = 1;
//	FILE *filePointer = NULL;
//	char line[100] = {'\0'}, copyLine[100] = {'\0'};
//	char strBuff[100];
//	Record *rMem = NULL;
//	Duration *dMem = NULL;
//
//	filePointer = fopen("musicPlayList.csv", "r");
//	rMem = (Record*)malloc(sizeof(Record)); // record
//	dMem = (Duration*)malloc(sizeof(Duration)); // duration
//
//	while (fgets(line, 100, filePointer) != NULL) {
//		strcpy(copyLine, line);
//
//		printf("playlist line = %s\n", line);
//		printf("playlist copyLine = %s\n", copyLine);
//
//		if (copyLine[0] == '"') {
//			strcpy(strBuff, strtok(copyLine, "\""));
//		}
//		else {
//			strncpy(strBuff, strtok(copyLine, ","), 50);
//		}
//		rMem->artist = (char*)malloc(strlen(strBuff)+1);
//		strcpy(rMem->artist, strBuff);
//
//		strcpy(strBuff, strtok(NULL, ","));
//		rMem->albumTitle = (char*)malloc(strlen(strBuff) + 1);
//		strcpy(rMem->albumTitle, strBuff);
//
//		strcpy(strBuff, strtok(NULL, ","));
//		rMem->songTitle = (char*)malloc(strlen(strBuff) + 1);
//		strcpy(rMem->songTitle, strBuff);
//
//		strcpy(strBuff, strtok(NULL, ","));
//		rMem->genre = (char*)malloc(strlen(strBuff) + 1);
//		strcpy(rMem->genre, strBuff);
//
//		strcpy(strBuff, strtok(NULL, ":"));
//		dMem->minutes = atoi(strBuff);
//
//		strcpy(strBuff, strtok(NULL, ","));
//		dMem->seconds = atoi(strBuff);
//
//		strcpy(strBuff, strtok(NULL, ","));
//		rMem->timesPlayed = atoi(strBuff);
//
//		strcpy(strBuff, strtok(NULL, ","));
//		rMem->rating = atoi(strBuff);
//
//		rMem->songLength = dMem;
//
//		insertFront(lis, rMem);
//
//		index++;
//	}
//	return success;
//}

void printMenu(){
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

int main()
{
	Node *list = NULL;
	char *userInput[50] = { '0' };
	while (strncmp(userInput,"11",50)!=0)
	{
		printMenu();
		// scanf_s("%s", userInput, 50);
		strcpy(userInput, "1");
		printf("user input = %s\n", userInput); // DEBUG
		printf("user input atoi = %i\n", atoi(userInput)); // DEBUG
		switch (atoi(userInput)) {
		case 1:
			printf("\tloading...\n");

			load(list);
			break;
		case 2:
			printf("(2) store\n");
			break;
		case 3:
			printf("(3) display\n");
			break;
		case 4:
			printf("(4) insert\n");
			break;
		case 5:
			printf("(5) delete\n");
			break;
		case 6:
			printf("(6) edit\n");
			break;
		case 7:
			printf("(7) sort\n");
			break;
		case 8:
			printf("(8) rate\n");
			break;
		case 9:
			printf("(9) play\n");
			break;
		case 10:
			printf("(10) shuffle\n");
			break;
		case 11:
			printf("(11) exit\n");
			break;
		default:
			printf("input not recognized :(\ntry again\n");
		}
	}
	
	printf("thats all folks!\n");
	getchar();

	return 0;
}