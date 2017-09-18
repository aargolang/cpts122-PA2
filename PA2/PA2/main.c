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
				- musicPlayList.csv
*********************************/

#include "LinkedList.h"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	BOOL success = FALSE;
	List songList;
	songList.pHead = NULL;
	songList.pTail = NULL;
	songList.size = 0;
	int exit = 0;
	char userInput[51] = { '0' };
	char message[51] = { '\0' };


	while (exit != 1)
	{
		printf("MESSAGE: %s\n", message);
		printMenu();
		getInput(userInput);
		switch (atoi(userInput)) {
		case 1:
			clrscr();
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
			if (success = TRUE)
				strncpy(message, "successfully written to file", 50);
			else
				strncpy(message, "failed to open file to write+", 50);
			clrscr();
			break;
		case 3:
			clrscr();
			printList(&songList);
			strncpy(message, "\0", 2); 
			break;
		case 4:
			printf("(4) insert (not inplemented)\n");
			break;
		case 5:
			printf("(5) delete (not implemented)\n");
			break;
		case 6:
			clrscr();
			success = edit(&songList);
			if (success = TRUE)
				strncpy(message, "changes made to list", 50);
			else
				strncpy(message, "no changes made", 50);
			clrscr();
			break;
		case 7:
			printf("(7) sort (not implemented)\n");
			break;
		case 8:
			clrscr();
			rate(&songList);
			clrscr();
			break;
		case 9:
			play(&songList);
			clrscr();
			break;
		case 10:
			printf("(10) shuffle (not implemented)\n");
			break;
		case 11:
			store(&songList);
			exit = 1;
			break;
		default:
			printf("input not recognized :(\ntry again\n");
			strncpy(message, "\0", 2);
		}
	}
	return 0;
}