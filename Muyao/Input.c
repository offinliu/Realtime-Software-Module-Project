/* 
MA4830 CA1 linklist template functions

done by: Liu Muyao

Last updated: 
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>

const float pi = 3.14159265359;

typedef struct _listnode
{
	int type;				//shape and 2/3D
	float d1;				//first dimension
	float d2;				//second dimension
	float d3;				//third dimension
	float c1;				//area for 2D, surface area for 3D
	float c2;				//perimeter for 2D, volume for 3D
	struct _listnode *next; //address to next node
} ListNode;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
	ListNode *tail;
	float SD_c1[9]; // 9 for 9 different shapes in the order: 11,21,31,41,12,22,32,42,52
	float SD_c2[9];
	float mean_c1[9];
	float mean_c2[9];
} LinkedList;

typedef struct _listnodeEx //for extracting
{
	float item;
	struct _listnodeEx *next;
} ListNodeEx;	// You should not change the definition of ListNode. sorry SCSE prof, i changed it anyway.

typedef struct _linkedlistEx //for extracting 
{
	int size;
	ListNodeEx *head;
	ListNodeEx *tail;
} LinkedListEx;

void calculate(int type, float d1, float d2, float d3, float *c1, float *c2); //legacy version. not in use.
int extract(LinkedList *ll, LinkedListEx *ex, int t1, int selector);
void printList(LinkedList *ll);
void printListEx(LinkedListEx *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNodeForMainLL(LinkedList *ll, int index, int t1, float d1, float d2, float d3, float c1, float c2);
int removeNode(LinkedList *ll, int index);
int insertNodeEx(LinkedListEx *ll, int index, int value);
int freemem(LinkedList *ll);
int freememEx(LinkedListEx *ll);

int main(void)
{ //main() used to simulate input from main menu
	int t1, index, check;
	float d1, d2, d3, c1, c2;
	LinkedList mainlist;
	LinkedListEx extractedlist;
	mainlist.head= NULL;
	mainlist.tail= NULL;
	mainlist.size=0;
	extractedlist.head=NULL;
	extractedlist.tail=NULL;
	extractedlist.size=0;
	index = 0;
	check = 0;
	c1 = c2 = 10.1; // for testing purposes
	printf("Hello World!!\n");
	printf("Input t1 d1 d2 d3 in this order\nInput: ");
	scanf("%d %f %f %f", &t1, &d1, &d2, &d3);
	getchar(); //clear buffer
	calculate(t1,d1,d2,d3,&c1,&c2);
	check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
	if (check != 0)
		perror("insert fail.");
	//t1+=10;
	d1++;
	d2++;
	d3++;
	calculate(t1,d1,d2,d3,&c1,&c2);
	check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
	if (check != 0)
		perror("insert fail.");
	printList(&mainlist);
	check = 0;
	check =extract(&mainlist, &extractedlist, 11, 2);
	if (check != 0)
		perror("insert fail.");
	printListEx(&extractedlist);
	system("pause");
	printf("Exited Printing.\n");
	check = freemem(&mainlist);
	if(check !=0) printf("Memory free fail.");
	return 0;
}

void calculate(int type, float d1, float d2, float d3, float *c1, float *c2) //call by reference
{
	int t1, shape;
	if (type == 0 || d1 == 0)
	{
		perror("Initialising error in Calculation");
	}
	switch (type)
	{
	case 11: //2D rectangle
		*c1 = (d1) * (d2);
		*c2 = 2 * (d1 + d2);
		break;
	case 21: //2D Square
		*c1 = d1*d1;
		*c2 = 4*d1;
		break;
	case 31: //2D circle
		*c1 = pi*d1*d1;
		*c2 = pi*d1*2;
		break;
	case 41: //2D right angle triangle
		*c1 = 0.5*d1*d2;
		*c2 = d1+d2+sqrt(d1*d1+d2*d2);
		break;
	case 12: //3D cude
		*c1 = pow(d1,3);
		*c2 = 6*d1*d1;
		break;
	case 22: //3D block
		*c1 = d1*d2*d3;
		*c2 = 2*(d1*d2+d2*d3+d1*d3);
		break;
	case 32: //3D cylinder
		*c1 = pi * d1 * d1 *d2;
		*c2 = 2*pi*d1*d1+2*pi*d1*d2;
		break;
	case 42: //3D sphere
		*c1 = pi*pow(d1,3);
		*c2 = 4*pi*d1*d1;
		break;
	case 52: //3D cone
		*c1 = pi*d1*d1*d2*1/3;
		*c2 = pi*d1*(d1+sqrt(d2*d2+d1*d1));
		break;
	default:
		printf("Error: none of type matches pre programmed types");
		break;
	}
}

int extract(LinkedList *ll, LinkedListEx *ex, int t1, int selector){ //ll is main linked list. t1 is type, 01 for 2D, 02 for 3D. selector is for d1---c2

	ListNode *mov; //cursor to move down the inserted ll
	int i; // for error catching in insertnodeEx.
	i=0;
	if (ll == NULL)
		return -1;

	mov=ll->head;
	while(mov!=NULL){
		if(((t1/10 == 0) && ((mov->type)%10 == t1%10)) || (mov->type == t1)
		){
			switch (selector)
			{
			case 1: //extract d1
				i = insertNodeEx(ex, 0, mov->d1);
				break;
			case 2: //extract d2
				i = insertNodeEx(ex, 0, mov->d2);
				break;
			case 3: //extract d3
				if(t1%10!=2){
					printf("No thrid dimension in 2D shapes. Exiting function....");
					return -1;
				}
				i = insertNodeEx(ex, 0, mov->d3);
				break;
			case 4: // extract c1
				i = insertNodeEx(ex, 0, mov->c1);
				break;
			case 5: //extract c2
				i = insertNodeEx(ex, 0, mov->c2);
				break;
			default:
				printf("Selector error. Exiting function....");
				return -1;
			}
			if(i!=0){
				printf("Insert node error. Exiting function....");
				return -1;
			}
			if (i!=0) printf("InsertNodeEx fail.\n");

			
		}
		mov=mov->next;
	}
	if(i=0) printf("Extraction complete");
	return 0;

}

void printList(LinkedList *ll)
{

	ListNode *cur;
	int i;
	if (ll == 0)
		return;
	cur = ll->head;

	if (cur == 0)
		printf("Empty");
	while (cur != NULL)
	{

		printf("type = %d, d1 = %.3f, d2 = %.3f, d3 = %.3f, c1 = %.3f, c2 = %.3f \n", cur->type, cur->d1, cur->d2, cur->d3, cur->c1, cur->c2);
		//fflush(stdout);

		cur = cur->next;
	}
	printf("Print Complete\n");
}

void printListEx(LinkedListEx *ll)
{

	ListNodeEx *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%f\n", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNodeForMainLL(LinkedList *ll, int index, int t1, float d1, float d2, float d3, float c1, float c2)
{					//set index to 0 for inserting at the start of the list

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->type = t1;
		ll->head->d1 = d1;
		ll->head->d2 = d2;
		ll->head->d3 = d3;
		ll->head->c1 = c1;
		ll->head->c2 = c2;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->type = t1;
		pre->next->d1 = d1;
		pre->next->d2 = d2;
		pre->next->d3 = d3;
		pre->next->c1 = c1;
		pre->next->c2 = c2;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index) //set index to 0 for removing at the start of the list
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

int insertNodeEx(LinkedListEx *ll, int index, int value){

	ListNodeEx *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNodeEx));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}
}

int freemem(LinkedList *ll){
	ListNode *cur, *nex;
	printf("Freeing memory for main list......");
	if (ll == NULL)
		return -1;
	cur = ll->head;
	while (cur != NULL)
	{
		nex=cur;
		cur=cur->next;
		free(nex);
	}
	//free(ll);
	printf("Memory is free.\n");
	return 0;
}

int freememEx(LinkedListEx *ll){
		ListNodeEx *cur, *nex;
	printf("Freeing memory for extracted list......");
	if (ll == NULL)
		return -1;
	cur = ll->head;
	while (cur != NULL)
	{
		nex=cur;
		cur=cur->next;
		free(nex);
	}
	//free(ll);
	printf("Memory is free.\n");
	return 0;
}
