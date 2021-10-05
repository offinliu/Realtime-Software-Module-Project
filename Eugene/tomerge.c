//Note: This code needs to be in the code with the linked list (muyao part) to work.


#include <stdio.h>
#include <stdlib.h>
#include "graphical.h"


void copyList(float* value, int numvalues, float* tempList);
void convertListEx(LinkedListEx* ll, int numvalues, float* tempList);
void display(int shape, LinkedList *ll, LinkedListEx *ex);

void main()
{
	//example to call function
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
	//printf("Hello World!!\n");
	//printf("Input t1 d1 d2 d3 in this order\nInput: ");
	//scanf("%d %f %f %f", &t1, &d1, &d2, &d3);
	//getchar(); //clear buffer

	t1 = 11;
	d1 = 1;
	d2 = 2;
	d3 = 3;
	calculate(t1,d1,d2,d3,&c1,&c2);
	check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
	if (check != 0)
		perror("insert fail.");
	//t1+=10;


	// add data
	if(1)
	{
		for (int i = 0; i < 5; i++)
		{
			d1++;
			d2++;
			d3++;
			calculate(t1,d1,d2,d3,&c1,&c2);
			check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
			if (check != 0)
				perror("insert fail.");
		}

		for (int i = 0; i < 3; i++)
		{
			calculate(t1,d1,d2,d3,&c1,&c2);
			check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
			if (check != 0)
				perror("insert fail.");
		}
		
		t1+=10;
		for (int i = 0; i < 5; i++)
		{
			d1++;
			d2++;
			d3++;
			calculate(t1,d1,d2,d3,&c1,&c2);
			check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
			if (check != 0)
				perror("insert fail.");
		}


		for (int i = 0; i < 3; i++)
		{
			calculate(t1,d1,d2,d3,&c1,&c2);
			check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
			if (check != 0)
				perror("insert fail.");
		}
	}

	printList(&mainlist);
	
	
	
	

	display(11, &mainlist, &extractedlist);

	freememEx(&extractedlist);
	extractedlist.head=NULL;
	extractedlist.tail=NULL;
	extractedlist.size=0;

	display(21, &mainlist, &extractedlist);
	
	return 0;
}


void display(int shape, LinkedList *ll, LinkedListEx *ex)
{	
	/*
	LinkedListEx ex;
	ex.head=NULL;
	ex.tail=NULL;
	ex.size=0;
	*/
	
	//D1
	extract(ll, ex, shape, 1); 
	int numvalues = ex -> size;
	float tempList[numvalues];
	float valueD1[numvalues], valueD2[numvalues], valueD3[numvalues], valueC1[numvalues], valueC2[numvalues];

	convertListEx(ex, numvalues, tempList);
	copyList(valueD1, numvalues, tempList);
	
	
	//D2
	extract(ll, ex, shape, 2);
	convertListEx(ex, numvalues, tempList);
	copyList(valueD2, numvalues, tempList);

	//D3
	extract(ll, ex, shape, 3);
	convertListEx(ex, numvalues, tempList);
	copyList(valueD3, numvalues, tempList);

	//C1
	extract(ll, ex, shape, 4);
	convertListEx(ex, numvalues, tempList);
	copyList(valueC1, numvalues, tempList);

	//C2
	extract(ll, ex, shape, 5);
	convertListEx(ex, numvalues, tempList);
	copyList(valueC2, numvalues, tempList);

	//meanC1, SDC1, meanC2, SDC2, have not been extracted yet.

	float meanC1 = 123;
	float SDC1 = 321;
	float meanC2 = 123;
	float SDC2 = 321;


	graphical(21, valueD1, valueD2, valueD3, valueC1, valueC2, numvalues, SDC1, SDC2, meanC1, meanC2);

	/* 
	//for simulated data, uncomment this portion
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

