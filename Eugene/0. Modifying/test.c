
#include <stdio.h>
#include <stdlib.h>
#include "graphical.h"	//Eugene header file


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
	
}

