/* 
MA4830 CA1 linklist template functions

done by: Liu Muyao

Last updated: 03/10/2021 
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
	int count[9]; // number of times each type has been keyed into the system
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

void calculate(LinkedList *ll, int index, int type, float d1, float d2, float d3, float *c1, float *c2);
LinkedListEx extract(LinkedList *ll, int t1, int selector);
void printList(LinkedList *ll);
void printListEx(LinkedListEx *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNodeForMainLL(LinkedList *ll, int index, int t1, float d1, float d2, float d3, float c1, float c2);
int removeNode(LinkedList *ll, int index);
int insertNodeEx(LinkedListEx *ll, int index, int value);
int freemem(LinkedList *ll);
int freememEx(LinkedListEx *ll);
float all_c1[] = {};
float all_c2[] = {};

int main()
{ //main() used to simulate input from main menu
	int t1, index, check;
	float d1, d2, d3, c1, c2;
	
	LinkedList mainlist;
	mainlist.head= NULL;
	mainlist.tail= 0;
	mainlist.size= 0;
	index = 0;
	check = 0;
	c1 = c2 = 10.1; // for testing purposes
	printf("Hello World!!\n");
	printf("Input t1 d1 d2 d3 in this order\nInput: ");
	scanf("%d %f %f %f", &t1, &d1, &d2, &d3);
	getchar(); //clear buffer
	calculate(&mainlist,index,t1,d1,d2,d3,&c1,&c2);
	check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
	if (check != 0)
		perror("insert fail.");
	t1++;
	calculate(&mainlist,index,t1,d1,d2,d3,&c1,&c2);
	check = insertNodeForMainLL(&mainlist, index, t1, d1, d2, d3, c1, c2);
	if (check != 0)
		perror("insert fail.");
	printList(&mainlist);
	printf("Exited Printing.\n");
	check = freemem(&mainlist);
	if(check !=0) printf("Memory free fail.");
	return (0);
}


void calculate(LinkedList *ll, int index, int type, float d1, float d2, float d3, float *c1, float *c2) //call by reference
{
	int t1, shape, total_c1, total_c2, type_index;
	float variance, old_mean_c1, old_mean_c2;
	if (type == 0 || d1 == 0)
	{
		perror("Initialising error in Calculation");
	}
	t1 = type%10;
	shape = type/10;
	// Calculate based on the type
    switch (type)
    {
        case 11 : //rectangle	
            printf("this is 11");
            *c1 = d1 * d2;
            *c2 = 2.0 * (d1 + d2);
			type_index = 0;
            printf("\n%f %f \n", *c1, *c2);
            break;
                   
        case 21 : //square	
            printf("this is 21");
            *c1 = pow(d1,2);
            *c2 = 4.0 * d1;
			type_index = 1;
            printf("\n%f %f\n", *c1, *c2);
            break;

        case 31 : //circle	
            printf("this is 31");
            *c1 = pi * d1 * d1;
            *c2 = 2 * pi * d1;
			type_index = 2;
            printf("\n%f %f\n", *c1, *c2);
            break;

		case 41: //2D right angle triangle
            printf("this is 41");
		    *c1 = 0.5*d1*d2;
		    *c2 = d1+d2+sqrt(d1*d1+d2*d2);
			type_index = 3;
            printf("\n%f %f\n", *c1, *c2);
		    break;

        case 12 : //cube	
            printf("this is 12");
            *c1 = pow(d1, 3);
            *c2 = 6.0 * pow(d1, 2);
			type_index = 4;
            printf("\n%f %f\n", *c1, *c2);
            break;

        case 22 : //blocks	
            printf("this is 22");
            *c1 = d1 * d2 * d3;
            *c2 = 2.0 * ( d1 *d2 + d1 * d3 + d2 * d3 );
			type_index = 5;
            printf("\n%f %f\n", *c1, *c2);
            break;

        case 32 : //cylinder	
            printf("this is 32");
            *c1 = pi * d1 * d1 * d2;
            *c2 = 2.0 * (pi * d1 * d1) + 2.0 * pi * d1 * d2;
			type_index = 6;
            printf("\n%f %f\n", *c1, *c2);
            break;

        case 42 : //sphere	
            printf("this is 42");
            *c1 = pi * pow(d1,3) * (4.0/3.0);
            *c2 = 4.0 * pi * d1 * d1;
			type_index = 7;
            printf("\n%f %f\n", *c1, *c2);
            break;

        case 52 : //cone	
            printf("this is 52");
            *c1 = pi * d1 * d1 * d2 * (1.0/3.0);
            *c2 =  pi * d1 * ( d1 + sqrt(d2 * d2 + d1 * d1 ));
			type_index = 8;
            printf("\n%f %f\n", *c1, *c2);
            break;

        default:
            printf("Error! type is not one of the options");
        
    }
	// calculate mean_c1 and sd_c1
	total_c1 = ll->mean_c1[type_index] * (ll->count[type_index]);
	total_c1 += *c1;
	old_mean_c1 = ll->mean_c1[type_index];
	ll->count[type_index] += 1;
	ll -> mean_c1[type_index] = total_c1 / (ll->count[type_index]);

	variance = (((ll->count[type_index]-2) * ll->SD_c1[type_index] + ((*c1 - ll->mean_c1[type_index]) * (*c1 - old_mean_c1))) / (ll->count[type_index] - 1));
	ll->SD_c1[type_index] = sqrt(variance);

	// calculate mean_c2 and sd_c2
	total_c2 = ll->mean_c2[type_index] * (ll->count[type_index]);
	total_c2 += *c2;
	old_mean_c2 = ll->mean_c2[type_index];
	ll->count[type_index] += 1;
	ll -> mean_c2[type_index] = total_c2 / (ll->count[type_index]);

	variance = (((ll->count[type_index]-2) * ll->SD_c2[type_index] + ((*c1 - ll->mean_c2[type_index]) * (*c1 - old_mean_c2))) / (ll->count[type_index] - 1));
	ll->SD_c2[type_index] = sqrt(variance);

}

// function to write linked list to a file
void save(char filename[], LinkedList *ll){
    
    struct _listnode* temp = ll;
    
    FILE* file;
    file = fopen (filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    
    // writing all the nodes of the linked list to the file
    while(temp!=NULL)
    {
        fwrite(temp, sizeof(struct _listnode), 1, file);
        temp = temp->next;
    }
    
    if(fwrite != 0)
    {
        printf("Linked List stored in the file successfully\n");
    }
       else
    {
           printf("Error While Writing\n");
    }
    
    fclose(file);
    
}

struct node* readLinkedList(char filename[])
{
    
    struct _listnode* temp = (struct _listnode *)malloc(sizeof(struct _listnode));
    struct _listnode* head; // points to the first node of the linked list in the file
    struct _listnode* last; // points to the last node of the linked list in the file
    last = head = NULL;
    
    FILE* file;
    file = fopen (filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    
    // reading nodes from the file
    // nodes are read in the same order as they were stored
    // we are using the data stored in the file to create a new linked list
    while(fread(temp, sizeof(struct _listnode), 1, file))
    {
        
        if(head==NULL)
        {
            head = last = (struct _listnode *)malloc(sizeof(struct _listnode));
        }
        else
        {
            last->next = (struct _listnode *)malloc(sizeof(struct _listnode));
            last = last->next;
        }
        last->type = temp->type;
        last->d1, temp->d1;
		last->d1, temp->d2;
		last->d1, temp->d3;
		last->d1, temp->c1;
		last->d1, temp->c2;
        last->next = NULL;
        
    }
    
    fclose(file);
    
    return head;
}

LinkedListEx extract(LinkedList *ll, int t1, int selector){ //ll is main linked list. t1 is type, 01 for 2D, 02 for 3D. selector is for d1---c2
	LinkedListEx *temp; // linkedlist of extracted data to be returned
	ListNode *mov; //cursor to move down the inserted ll
	int i; // for error catching in insertnodeEx.
	i=0;
	if (ll == NULL)
		return *temp;	

	mov=ll->head;
	while(mov->next!=NULL){
		if((t1/10 == 0 && mov->type%10 == t1%10) || mov->type == t1){
			switch (selector)
			{
			case 1: //extract d1
				i = insertNodeEx(temp, 0, mov->d1);
				break;
			case 2: //extract d2
				i = insertNodeEx(temp, 0, mov->d2);
				break;
			case 3: //extract d3
				if(t1%10!=2){
					printf("No thrid dimension in 2D shapes. Exiting function....");
					return *temp;
				}
				i = insertNodeEx(temp, 0, mov->d3);
				break;
			case 4: // extract c1
				i = insertNodeEx(temp, 0, mov->c1);
				break;
			case 5: //extract c2
				i = insertNodeEx(temp, 0, mov->c2);
				break;
			default:
				printf("Selector error. Exiting function....");
				return *temp;
			}
			if(i!=0){
				printf("Insert node error. Exiting function....");
				return *temp;
			}
		}
		mov=mov->next;
	}
	return *temp;

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
	if (ll == 0)
		return;
	cur = ll->head;

	if (cur == 0)
		printf("Empty");
	while (cur != 0)
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
