#include <stdio.h>
#include <stdlib.h>
#include "graphical.h"

void main()
{	
	system("clear");
	int type;
	int scaleC1 = 1;
	int scaleC2 = 1;

	/*
	printf("-----2D-----\n");
	printf("11 Rectangle\n");
	printf("21 Square\n");
	printf("31 Circle\n");
	printf("41 Triangle\n");
	printf("-----3D-----\n");
	printf("12 Cube\n");
	printf("22 Blocks\n");
	printf("32 Cylinder\n");
	printf("42 Sphere\n");
	printf("52 Cone\n\n");

	
	printf("Input type\nInput: ");
	scanf("%d", &type);
	printf("\n\n");
	printf("Input scale for C1\nInput: ");
	scanf("%d", &scaleC1);
	printf("\n\n");
	printf("Input scale for C2\nInput: ");
	scanf("%d", &scaleC2);
	printf("\n\n");
	
	graphical(type, scaleC1, scaleC2);
	*/

	///*
	printf("Input type\nInput: ");
	scanf("%d", &type);
	printf("\n\n");

	graphical(type, 10, 10);
	//*/

}