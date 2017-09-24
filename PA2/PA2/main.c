/********************************
Name:			Arthur Lang
Assignment:		PA3 - Digital Music Manager part 2
Date Started:	9/18/17

Description:	create and implement a imitation digital music manager
				to showcase the functionality of a doubly linked list
				and properties of a queue

Files:			- main.c
				- LinkedList.h
				- LinkedList.c
				- musicPlayList.csv
*********************************/

#include "LinkedList.h"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int main()
{
	BOOL success = FALSE;
	BOOL edited = FALSE;
	BOOL exit = FALSE;
	List songList;
	songList.pHead = NULL;
	songList.pTail = NULL; 
	songList.size = 0;
	char userInput[50] = { '0' };
	char message[50] = { '\0' };
	srand(time(NULL));

	while (exit == FALSE){
		success = FALSE;
		printf("MESSAGE: %s\n", message);
		printf("list size: %i\n", songList.size);
		printMenu();
		getInput(userInput);
		// if user likes to type "exit" rather than 11
		if (strcmp(userInput, "exit") == 0) {
			exit = TRUE;
		}
		switch (atoi(userInput)) {
		case 1:
			clrscr();
			freeList(&songList);
			success = load(&songList);
			if (success = TRUE)
				strncpy(message, "loaded from file",50);
			else 
				strncpy(message, "file failed to load", 50);
			clrscr();
			break;
		case 2:
			clrscr();
			success = store(&songList);
			if (success = TRUE){
				strncpy(message, "successfully written to file", 50);
				edited = FALSE;
			}
			else
				strncpy(message, "failed to open file to write+", 50);
			clrscr();
			break;
		case 3:
			clrscr();
			printList(&songList);
			printf("press any key to continue");
			getInput(userInput);
			strncpy(message, "\0", 2); 
			clrscr();
			break;
		case 4:
			clrscr();
			insert(&songList);
			if (success = TRUE) {
				strncpy(message, "changes made to list", 50);
				edited = TRUE;
			}
			else
				strncpy(message, "no changes made", 50);
			clrscr();
			break;
		case 5:
			clrscr();
			success = del(&songList);
			if (success = TRUE) {
				strncpy(message, "changes made to list", 50);
				edited = TRUE;
			}
			else
				strncpy(message, "no changes made", 50);
			clrscr();
			break;
		case 6:
			clrscr();
			success = edit(&songList);
			if (success = TRUE){
				strncpy(message, "changes made to list", 50);
				edited = TRUE;
			}
			else
				strncpy(message, "no changes made", 50);
			clrscr();
			break;
		case 7:
			clrscr();
			sort(&songList);
			if (success = TRUE) {
				strncpy(message, "changes made to list", 50);
				edited = TRUE;
			}
			else
				strncpy(message, "no changes made", 50);
			clrscr();
			break;
		case 8:
			clrscr();
			rate(&songList);
			if (success = TRUE) {
				strncpy(message, "changes made to list", 50);
				edited = TRUE;
			}
			else
				strncpy(message, "no changes made", 50);
			clrscr();
			break;
		case 9:
			play(&songList);
			clrscr();
			break;
		case 10:
			clrscr();
			shuffle(&songList);
			clrscr();
			break;
		case 11:
			while(exit == FALSE && edited == TRUE){
				printf("Your changes have not been saved. Would you like to save? (yes/no): ");
				getInput(userInput);
				if (strcmp(userInput, "yes") == 0) {
					store(&songList);
					exit = TRUE;
				}
				else if (strcmp(userInput, "no") == 0) {
					exit = TRUE;
				}
				else {
					printf("\n");
				}
			}
			exit == TRUE;
			freeList(&songList);
			break;
		default:
			strncpy(message, "input not recognized", 50);
			clrscr();
		}
	}
	return 0;
}