/* 
MA4830 CA1 linklist template functions

done by: Liu Muyao

Last updated: 04/10/2021 1650
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

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

void calculate(int type, float d1, float d2, float d3, float *c1, float *c2);
int extract(LinkedList *ll, LinkedListEx *ex, int t1, int selector);
void printList(LinkedList *ll);
void printListEx(LinkedListEx *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNodeForMainLL(LinkedList *ll, int index, int t1, float d1, float d2, float d3, float c1, float c2);
int removeNode(LinkedList *ll, int index);
int insertNodeEx(LinkedListEx *ll, int index, int value);
int freemem(LinkedList *ll);
int freememEx(LinkedListEx *ll);
void divider(char* typeD2, char* typeD3, int type);
void drawGraph(float* values, int numvalues);
void drawTable(char* typeD1, char* typeD2, char* typeD3, char* typeC1, char* typeC2, float* valueD1, float* valueD2,
	float* valueD3, float* valueC1, float* valueC2, int numvalues, float SDC1, float SDC2, float meanC1, float meanC2);
void graphical(int type, float* valueD1, float* valueD2, float* valueD3, float* valueC1, float* valueC2,
	int numvalues, float SDC1, float SDC2, float meanC1, float meanC2);
void copyList(float* value, int numvalues, float* tempList);

void convertListEx(LinkedListEx* ll, int numvalues, float* tempList);

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
	for (int i = 0; i < 10; i++)
	{
		d1++;
		d2++;
		d3++;
		calculate(t1, d1, d2, d3, &c1, &c2);
		check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
		if (check != 0)
			perror("insert fail.");
	}
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

	// GRAPH

	int shape = 11;

	//D1
	extract(&mainlist, &extractedlist, shape, 1); 
	int numvalues = extractedlist.size;
	float tempList[numvalues];
	float valueD1[numvalues], valueD2[numvalues], valueD3[numvalues], valueC1[numvalues], valueC2[numvalues];

	convertListEx(&extractedlist, numvalues, tempList);
	copyList(valueD1, numvalues, tempList);

	//D2
	extract(&mainlist, &extractedlist, shape, 2);
	convertListEx(&extractedlist, numvalues, tempList);
	copyList(valueD2, numvalues, tempList);

	//D3
	extract(&mainlist, &extractedlist, shape, 3);
	convertListEx(&extractedlist, numvalues, tempList);
	copyList(valueD3, numvalues, tempList);

	//C1
	extract(&mainlist, &extractedlist, shape, 4);
	convertListEx(&extractedlist, numvalues, tempList);
	copyList(valueC1, numvalues, tempList);

	//C2
	extract(&mainlist, &extractedlist, shape, 5);
	convertListEx(&extractedlist, numvalues, tempList);
	copyList(valueC2, numvalues, tempList);

	float meanC1 = 123;
	float SDC1 = 321;
	float meanC2 = 123;
	float SDC2 = 321;

	/*
	float a[] = { 10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200 };
	float b[] = { 1.5, 1.7, 1.9, 2.5, 2.1, 4.5, 4.1, 5.4, 6.8, 5.9, 9.9, 8.8, 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1, 1.2 };
	float c[] = { 1.5, 1.7, 1.9, 2.5, 2.1, 4.5, 4.1, 5.4, 6.8, 5.9, 9.9, 8.8, 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1, 1.2 };
	float d[] = { 1.5, 1.7, 1.9, 2.5, 2.1, 4.5, 4.1, 5.4, 6.8, 5.9, 9.9, 8.8, 7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.1, 1.2 };
	float e[] = { 10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200 };
	valueD1 = a;
	valueD2 = b;
	valueD3 = c;
	valueC1 = d;
	valueC2 = e;

	numvalues = 20;
	float meanC1 = 123;
	float SDC1 = 321;
	float meanC2 = 123;
	float SDC2 = 321;

	graphical(21, valueD1, valueD2, valueD3, valueC1, valueC2, numvalues, SDC1, SDC2, meanC1, meanC2);
	*/

	graphical(21, valueD1, valueD2, valueD3, valueC1, valueC2, numvalues, SDC1, SDC2, meanC1, meanC2);
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

void printListEx(LinkedListEx* ll)
{

	ListNodeEx* cur;
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

void convertListEx(LinkedListEx* ll, int numvalues, float *tempList)
{
	ListNodeEx* cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	int i = 0;
	while (cur != NULL)
	{
		tempList[i] =  cur->item;
		cur = cur->next;
		i++;
	}
}

void copyList(float* value, int numvalues, float* tempList) 
{
	int i;
	for (i = 0; i < numvalues; i++) 
	{
		value[i] = tempList[i];
	}
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


//default: "-"; 1: "_", 2: "=", 3: " " 
void divider(char* typeD2, char* typeD3, int type)
{
	switch (type)
	{
	case 1: //Top (Underscore)
		printf(" ______________");
		if (typeD2[0]) printf("_______________");
		if (typeD3[0]) printf("_______________");
		printf("_______________");
		printf("_______________\n");
		break;

	case 2: // "=" divider
		printf("|==============|");
		if (typeD2[0]) printf("==============|");
		if (typeD3[0]) printf("==============|");
		printf("==============|");
		printf("==============|\n");
		break;

	case 3: //Bot 
		printf("|______________|");
		if (typeD2[0]) printf("______________|");
		if (typeD3[0]) printf("______________|");
		printf("______________|");
		printf("______________|\n");
		break;

	default: // "-" divider
		printf("|--------------|");
		if (typeD2[0]) printf("--------------|");
		if (typeD3[0]) printf("--------------|");
		printf("--------------|");
		printf("--------------|\n");
		break;

	}
}



void drawGraph(float *values, int numvalues)
{
	int scale = 10;
	int i, j;
	int maxval;
	int maxcount = 0;
	int maxwidth = 180; // CHANGE THIS ACCORDING TO SCREEN SIZE or preference. Max 180 (for 1980x1080 res)


	for (i = 0; i < numvalues; i++)
	{
		if ((int)values[i] > maxval) maxval = (int)values[i];
	}

	int minval = maxval;

	for (i = 0; i < numvalues; i++)
	{
		if ((int)values[i] < minval) minval = (int)values[i];
	}



	int freqsize = maxval - minval;
	int step = freqsize / scale;
	if (step < 1) step = 1;

	freqsize = freqsize / step + 1;


	int frequency[freqsize];
	for (i = 0; i < freqsize; i++)
	{
		frequency[i] = 0;
	}

	for (i = 0; i < numvalues; i++)
	{
		int index = (int)(values[i] / step) - minval / step;
		frequency[index]++;
		if (frequency[index] > maxcount) maxcount = frequency[index];
	}

	int spacersize = maxwidth / maxcount;
	if (!spacersize) spacersize = 1;
	char spacer[spacersize];

	for (i = 0; i < spacersize; i++)
	{
		spacer[i] = '_';
	}
	spacer[spacersize] = '\0';


	for (i = 0; i < freqsize; i++)
	{
		if (i) printf("                 |");
		else printf("                  ");

		for (j = 0; j < frequency[i]; j++)
		{
			printf("%s", spacer);
		}

		printf("\n");

		printf("%4d <= x < %4d |", minval + i * step, minval + i * step + step);
		for (j = 0; j < frequency[i]; j++)
		{
			printf("%s", spacer);
		}

		if (frequency[i]) printf("|");
		printf("\n");
		if (freqsize - i - 1) printf("                 |\n");

	}

}


void drawTable(char* typeD1, char* typeD2, char* typeD3, char* typeC1, char* typeC2, float *valueD1, float* valueD2, 
	float* valueD3, float* valueC1, float* valueC2, int numvalues, float SDC1, float SDC2, float meanC1, float meanC2)
{
	//Header

	divider(typeD2, typeD3, 1);

	printf("|%13s |", typeD1);
	if (typeD2[0]) printf("%13s |", typeD2);
	if (typeD3[0]) printf("%13s |", typeD3);
	printf("%13s |", typeC1);
	printf("%13s |\n", typeC2);

	divider(typeD2, typeD3, 2);

	//Body

	for (int i = 0; i < numvalues; i++)
	{
		printf("|%13.2f |", valueD1[i]);
		if (typeD2[0]) printf("%13.2f |", valueD2[i]);
		if (typeD3[0]) printf("%13.2f |", valueD3[i]);
		printf("%13.2f |", valueC1[i]);
		printf("%13.2f |\n", valueC2[i]);

		divider(typeD2, typeD3, 0);
	}

	//Mean
	printf("|     MEAN     |");
	if (typeD2[0]) printf("     MEAN     |");
	if (typeD3[0]) printf("     MEAN     |");
	printf("%13.2f |", meanC1);
	printf("%13.2f |\n", meanC2);

	//SD
	divider(typeD2, typeD3, 0);
	printf("|      SD      |");
	if (typeD2[0]) printf("      SD      |");
	if (typeD3[0]) printf("      SD      |");
	printf("%13.2f |", SDC1);
	printf("%13.2f |\n", SDC2);

	//END
	divider(typeD2, typeD3, 3);


	/*
	//Header

	divider(typeD2, typeD3, 1);

	printf("|%7s |", typeD1);
	if (typeD2[0]) printf("%7s |", typeD2);
	if (typeD3[0]) printf("%7s |", typeD3);
	printf("%13s |", typeC1);
	printf("%7s |\n", typeC2);

	divider(typeD2, typeD3, 2);

	//Body

	for (int i = 0; i < numvalues; i++)
	{
		printf("|%7.2f |", valueD1[i]);
		if (typeD2[0]) printf("%7.2f |", valueD2[i]);
		if (typeD3[0]) printf("%7.2f |", valueD3[i]);
		printf("%13.2f |", valueC1[i]);
		printf("%7.2f |\n", valueC2[i]);

		divider(typeD2, typeD3, 0);
	}

	//Mean, SD, end
	divider(typeD2, typeD3, 3);

	*/

}

void graphical(int type, float* valueD1, float* valueD2, float* valueD3, float* valueC1, float* valueC2, 
	int numvalues, float SDC1, float SDC2, float meanC1, float meanC2)

{
	char c1_2D[] = "Perimeter";
	char c2_2D[] = "Area";
	char c1_3D[] = "Surface Area";
	char c2_3D[] = "Volume";
	char typeC1[13];
	char typeC2[7];

	char length[] = "Length";
	char width[] = "Width";
	char height[] = "Height";
	char base[] = "Base";
	char radius[] = "Radius";

	char typeD1[7] = "";
	char typeD2[7] = "";
	char typeD3[7] = "";



	switch (type)
	{
	case 11: //2D rectangle
		printf("2D Rectangle\n");
		strcpy(typeD1, length);
		strcpy(typeD2, width);
		break;

	case 21: //2D Square
		printf("2D Square\n");
		strcpy(typeD1, length);
		break;

	case 31: //2D circle
		printf("2D Circle\n");
		strcpy(typeD1, radius);
		break;

	case 41: //2D right angle triangle
		printf("2D Triangle\n");
		strcpy(typeD1, base);
		strcpy(typeD2, height);
		break;

	case 12: //3D cude
		printf("3D Cube\n");
		strcpy(typeD1, length);
		break;

	case 22: //3D block
		printf("3D Block\n");
		strcpy(typeD1, length);
		strcpy(typeD2, width);
		strcpy(typeD3, height);
		break;

	case 32: //3D cylinder
		printf("3D Cylinder\n");
		strcpy(typeD1, radius);
		strcpy(typeD2, height);
		break;

	case 42: //3D sphere
		printf("3D Sphere\n");
		strcpy(typeD1, radius);
		break;

	case 52: //3D cone
		printf("3D Cone\n");
		strcpy(typeD1, radius);
		strcpy(typeD2, height);
		break;

	default:
		printf("Error: none of type matches pre programmed types\n");
		break;

	}


	if (type % 10 == 1)
	{
		// 2D
		strcpy(typeC1, c1_2D);
		strcpy(typeC2, c2_2D);
	}

	else
	{
		//3D
		strcpy(typeC1, c1_3D);
		strcpy(typeC2, c2_3D);
	}



	printf("\n==============\n");
	printf("Histogram Plot\n");
	printf("==============\n");


	printf("%s:\n", typeC1);
	drawGraph(valueC1, numvalues);
	printf("\n\n");


	printf("%s:\n", typeC2);
	drawGraph(valueC2, numvalues);
	printf("\n\n");

	printf("\n==============\n");
	printf("     Table\n");
	printf("==============\n");

	drawTable(typeD1, typeD2, typeD3, typeC1, typeC2, valueD1, valueD2, valueD3, valueC1, valueC2, numvalues, SDC1, SDC2, meanC1, meanC2);
}

