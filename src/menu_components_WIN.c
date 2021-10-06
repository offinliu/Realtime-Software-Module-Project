#include "../include/menu_components.h"

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
// #define QNX

void PrintMenuHeader() {
  printf("-------------------------------\n");
  printf("SHAPE DATABASE SEARCH ENGINE\n");
  printf("-------------------------------\n");
}
void PrintMenuOptions() {
  printf("MENU OPTIONS\n");
  printf("-------------------------------\n");
  printf("1. New Object\n");
  printf("2. Object Query\n");
  printf("3. Save Current Database\n");
  printf("4. Load a Database\n");
  printf("5. Exit Program\n");
  printf("-------------------------------\n\n");
}

void GetUserMenuOption(char* user_input_ptr) {
  PrintMenuOptions();
  printf("Hello user, what would you like to do today? (1/2/3/4/5)\nOption: ");
  scanf("%c", user_input_ptr);
  while (getchar() != '\n')
    ;  // clear buffer
}

void DataEntry(LinkedList* ll) {
  // printf("DataEntry() called. Functionality WIP\n");
  int t1 = 0;
  float d1, d2, d3;

  t1 = ObjectType();

  printf("Object Selected: ");
  ShapeChecker(t1,4);
  d1 = ShapeChecker(t1, 1);
  d2 = ShapeChecker(t1, 2);
  d3 = ShapeChecker(t1, 3);

  if (InsertNodeForMainLL(ll, 0, t1, d1, d2, d3) == 0)
    printf("data entry failed.");

  // can comment this out later on if we dont want!!
  printf("Current database contains the following: \n");
  PrintList(ll);
#ifdef QNX
  delay(1000);
#else
  sleep(1);
#endif
  printf("==========================================\n\n\n\n");
}

void DataQuery(LinkedList* ll) {
  // can comment this out later on if we dont want!!
  //printf("Current database contains the following: \n");
  //PrintList(ll);
  
	LinkedListEx extracted_list;
	extracted_list.head=NULL;
	extracted_list.tail=NULL;
	extracted_list.size=0;

	LinkedListEx validity_check;
	validity_check.head=NULL;
	validity_check.tail=NULL;
	validity_check.size=0;

  int t1;
  printf("Input t1\nInput: ");
  scanf("%d", &t1);
  getchar();  // clear buffer

  Extract(ll, &validity_check, t1, 1);
  if (validity_check.size) Display(t1, ll, &extracted_list);
  else printf("Item does not exist yet!\n");


#ifdef QNX
  delay(1000);
#else
  sleep(1);
#endif
  printf("==========================================\n\n\n\n");
}

void SaveRequest(LinkedList* ll) {
  char* filename = NULL;
  size_t len = 0;
  ssize_t line_size = 0;
  printf(
      "Enter your desired filename for this database (Hit enter to abort): ");
  line_size = getline(&filename, &len, stdin);
  // printf("You entered %s, which has %zu chars.\n", filename, line_size - 1);
  if (line_size == 1) {
    printf("Invalid filename entered. Aborting save...\n");
  } else {
    printf("This is what is being saved: \n");
    PrintList(ll);
    SaveCurrentDB(filename, ll);
  }
  free(filename);
}
// function to save linked list to a file
void SaveCurrentDB(char filepath[], LinkedList* ll) {
  ListNode* cached_node;

  FILE* file;
  file = fopen(filepath, "w");
  if (file == NULL) {
    printf("Couldn't write to file! Skipping save...\n");
    return;
  }

  // check if LinkedList is empty
  if (ll == NULL) {
    printf("Linked List is empty! Skipping save...\n");
    return;
  }

  // write LinkedList struct to file
  fwrite(ll, sizeof(LinkedList), 1, file);

  // write all the ListNodes of the linked list to the file
  cached_node = ll->head;
  while (cached_node != NULL) {
    if (fwrite(cached_node, sizeof(ListNode), 1, file) != 1) {
      printf("Error saving ListNode to file. \n");
      break;
    }
    cached_node = cached_node->next;
  }
  printf("Database stored in the file successfully!\n");
  fclose(file);
}

void LoadRequest(LinkedList* ll) {
  char* filename = NULL;
  size_t len = 0;
  ssize_t line_size = 0;
  char confirmation;
  printf(
      "Warning!! This will wipe out your current database. Do you wish to "
      "proceed? (Y/N)\n");
  scanf("%c", &confirmation);
  while (getchar() != '\n')
    ;  // clear buffer
  if (confirmation != 'y' && confirmation != 'Y') return;

  printf(
      "Enter the filename of the database you wish to load (Hit enter to "
      "abort): ");
  line_size = getline(&filename, &len, stdin);
  if (line_size == 1) {
    printf("Invalid filename entered. Aborting save...\n");
  } else {
    FreeMem(ll);
    ll = LoadDB(filename);
  }
  free(filename);
  // can comment this out later on if we dont want!!
  printf("Current database contains the following: \n");
  PrintList(ll);
  printf("==========================================\n\n\n\n");
}

// function to load linked list from a file
LinkedList* LoadDB(char filepath[]) {
  ListNode* cached_node = (ListNode*)malloc(sizeof(ListNode));
  LinkedList* loaded_db = (LinkedList*)malloc(sizeof(LinkedList));
  ListNode* head;  // points to the first node of the linked list in the file
  ListNode* tail;  // points to the last node of the linked list in the file
  tail = head = NULL;

  // initialise linked list
  loaded_db->head = NULL;
  loaded_db->tail = 0;
  loaded_db->size = 0;

  // try to open file
  FILE* file;
  file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Couldn't load database. Defaulting to an empty one.\n");
    return loaded_db;
  }

  // extract LinkedList struct
  if (!fread(loaded_db, sizeof(LinkedList), 1, file)) {
    printf("Couldn't load database. Defaulting to an empty one.\n");
    return loaded_db;
  }

  // reading nodes from the file
  // nodes are read in the same order as they were stored
  // we are using the data stored in the file to create a new linked list
  while (fread(cached_node, sizeof(ListNode), 1, file)) {
    if (head == NULL) {
      head = tail = (ListNode*)malloc(sizeof(ListNode));
    } else {
      tail->next = (ListNode*)malloc(sizeof(ListNode));
      tail = tail->next;
    }
    tail->type = cached_node->type;
    tail->d1, cached_node->d1;
    tail->d1, cached_node->d2;
    tail->d1, cached_node->d3;
    tail->d1, cached_node->c1;
    tail->d1, cached_node->c2;
    tail->next = NULL;
  }

  fclose(file);
  loaded_db->head = head;
  loaded_db->tail = tail;
  PrintList(loaded_db);
  return loaded_db;
}

int MainMenu(LinkedList* ll, const char* file_path) {
  PrintMenuHeader();
  while (1) {
    char user_option;
    GetUserMenuOption(&user_option);
    int error = 0;
    switch (user_option) {
      case '1':
        DataEntry(ll);
        break;
      case '2':
        DataQuery(ll);
        break;
      case '3':
        SaveRequest(ll);
        break;
      case '4':
        LoadRequest(ll);
        break;
      case '5':
        printf("Exiting program now. Goodbye!\n");
        return 0;
        break;
      default:
        printf("Invalid option! Please try again.\n");
        error = 1;
        break;
    }
    if (error == 0) break;
  }
  // everything went smoothly, we can return true here
  return 1;
}

int ShapeChecker(int type, int dimension)
{
  float input_dimension = 0;
	char length[] = "Length";
	char width[] = "Width";
	char height[] = "Height";
	char base[] = "Base";
	char radius[] = "Radius";

	char type_D1[7] = "";
	char type_D2[7] = "";
	char type_D3[7] = "";

	switch (type)
	{
	case 11: //2D rectangle
		if(dimension == 4) printf("2D Rectangle\n");
		strcpy(type_D1, length);
		strcpy(type_D2, width);
		break;

	case 21: //2D Square
		if(dimension == 4) printf("2D Square\n");
		strcpy(type_D1, length);
		break;

	case 31: //2D circle
		if(dimension == 4) printf("2D Circle\n");
		strcpy(type_D1, radius);
		break;

	case 41: //2D right angle triangle
		if(dimension == 4) printf("2D Triangle\n");
		strcpy(type_D1, base);
		strcpy(type_D2, height);
		break;

	case 12: //3D cude
		if(dimension == 4) printf("3D Cube\n");
		strcpy(type_D1, length);
		break;

	case 22: //3D block
		if(dimension == 4) printf("3D Block\n");
		strcpy(type_D1, length);
		strcpy(type_D2, width);
		strcpy(type_D3, height);
		break;

	case 32: //3D cylinder
		if(dimension == 4) printf("3D Cylinder\n");
		strcpy(type_D1, radius);
		strcpy(type_D2, height);
		break;

	case 42: //3D sphere
		if(dimension == 4) printf("3D Sphere\n");
		strcpy(type_D1, radius);
		break;

	case 52: //3D cone
		if(dimension == 4) printf("3D Cone\n");
		strcpy(type_D1, radius);
		strcpy(type_D2, height);
		break;

	default:
		printf("Error: none of type matches pre programmed types\n");
		break;

	}

  if((dimension == 1) && type_D1[0])
  {
    input_dimension = 1;
    return input_dimension;
  }

  if((dimension == 2) && type_D2[0])
  {
    input_dimension = 2;
    return input_dimension;
  }

  if((dimension == 3) && type_D3[0])
  {
    input_dimension = 3;
    return input_dimension;
  }



}

int ObjectType()
{

  int t1_1 = 0;
  int t1_2 = 0;
  int t1 = 0;

  while(1)
  {
    printf("Please select object type:\n");
    printf("1. 2D\n");
    printf("2. 3D\n");
    printf("Option: \n");
    scanf("%d", &t1_1);
    getchar();  // clear buffer
    if((t1_1 == 1) || (t1_1 == 2)) break;
    else printf("Please choose only 1 or 2!\n\n");
  }

  printf("\n\n");
  if(t1_1 == 1) //2D
  {
    while(1)
    {
      printf("Please select object shape for 2D:\n");
      printf("1. Rectangle\n");
      printf("2. Square\n");
      printf("3. Circle\n");
      printf("4. Triangle\n");
      printf("Option: \n");
      scanf("%d", &t1_2);
      getchar();  // clear buffer
      if((t1_2 == 1) || (t1_2 == 2) || (t1_2 == 3) || (t1_2 == 4) ) break;
      else printf("Please choose only 1, 2, 3 or 4!\n\n");
    }
  }


  else //2D
  {
    while(1)
    {
      printf("Please select object shape for 3D:\n");
      printf("1. Cube\n");
      printf("2. Block\n");
      printf("3. Cylinder\n");
      printf("4. Sphere\n");
      printf("5. Cone\n");
      printf("Option: \n");
      scanf("%d", &t1_2);
      getchar();  // clear buffer
      if((t1_2 == 1) || (t1_2 == 2) || (t1_2 == 3) || (t1_2 == 4) || (t1_2 == 5) ) break;
      else printf("Please choose only 1, 2, 3, 4 or 5!\n\n");
    }
  }


  t1 = t1_1 + t1_2*10;
  return t1;
}