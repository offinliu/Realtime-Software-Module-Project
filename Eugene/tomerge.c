//Note: This code needs to be in the code with the linked list (muyao part) to work.


#include <stdio.h>
#include <stdlib.h>
#include "graphical.h"


void copyList(float* value, int numvalues, float* tempList);
void convertListEx(LinkedListEx* ll, int numvalues, float* tempList);
void display(int shape);

void main()
{
	
}


void display(int shape)
{	
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

