#include "LinkedList.h"

/***********************
Function:	makeNode
input:		record
output:		pointer to new node with record
************************/
Node *makenode(Record *dat)
{
	Node *pTemp = NULL;


	return pTemp;
}

/***********************
Function:	insertNode
input:		pList and node to insert
output:		1 for successfully allocating space for a node; 0 otherwise
************************/
int insertnode(Node **pList, Record *dat)
{
	Node * pMem = NULL;

	if (*pList == NULL)
	{
		pMem = makenode(dat);
		if (pMem == NULL)
		{
			return FALSE;
		}
		else
		{
			*(pList) = pMem;
		}
	}
	else // traversing the list 
	{
		Node *pTemp = *pList, *pPrevv = NULL;

		while (pTemp->pNext != NULL)
		{
			pPrevv = pTemp;
			pTemp = pTemp->pNext;
		}

		if (pPrevv == *pList) // head of list
		{
			(*pList)->pNext = pMem;
			pMem->pPrev = (*pList);

		}
		else if (pTemp->pNext == NULL && pPrevv != (*pList))
		{
			pTemp->pNext = pMem;
			pMem->pPrev = pTemp;
		}
	}
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
