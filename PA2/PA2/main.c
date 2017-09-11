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

int load(Node **lis)
{
	int success = 0;



	return success;
}

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
		scanf_s("%s", userInput, 50);
		printf("user input = %s\n", userInput); // DEBUG
		printf("user input atoi = %i\n", atoi(userInput)); // DEBUG
		switch (atoi(userInput)) {
		case 1:
			printf("\tloading...\n");
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