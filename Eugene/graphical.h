#include <stdio.h>
#include <string.h>

void divider(char* typeD2, char* typeD3, int type);
void drawGraph(float* values, int numvalues);
void drawTable(char* typeD1, char* typeD2, char* typeD3, char* typeC1, char* typeC2, float* valueD1, float* valueD2,
	float* valueD3, float* valueC1, float* valueC2, int numvalues, float SDC1, float SDC2, float meanC1, float meanC2);
void graphical(int type, float* valueD1, float* valueD2, float* valueD3, float* valueC1, float* valueC2,
	int numvalues, float SDC1, float SDC2, float meanC1, float meanC2);


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
	int maxval = 0;
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

