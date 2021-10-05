#include "menu_components.h"

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
  printf("3. Exit Program\n");
  printf("-------------------------------\n\n");
}

void GetUserMenuOption(char* user_input_ptr) {
  PrintMenuOptions();
  printf("Hello user, what would you like to do today? (1/2/3)\nOption: ");
  scanf("%c", user_input_ptr);
  while (getchar() != '\n')
    ;
}

void DataEntry(LinkedList* ll) {
  // printf("DataEntry() called. Functionality WIP\n");
  int t1;
  float d1, d2, d3;
  printf("Input t1 d1 d2 d3 in this order\nInput: ");
  scanf("%d %f %f %f", &t1, &d1, &d2, &d3);
  getchar();  // clear buffer
  if (InsertNodeForMainLL(ll, 0, t1, d1, d2, d3) == 0)
    printf("data entry failed.");

  PrintList(ll);  // can comment this out later on!!
#ifdef QNX
  delay(1000);
#else
  sleep(1);
#endif
  printf("==========================================\n\n\n\n");
}

void DataQuery(LinkedList* ll) {
  printf("DataQuery() called. Functionality WIP\n");
#ifdef QNX
  delay(1000);
#else
  sleep(1);
#endif
  printf("==========================================\n\n\n\n");
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
  printf("Linked List stored in the file successfully\n");
  fclose(file);
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
        return 1;
      case '2':
        DataQuery(ll);
        return 1;
      case '3':
        printf("Exiting program now. Goodbye!\n");
        return 0;
      default:
        printf("Invalid option! Please try again.\n");
        error = 1;
        break;
    }
    if (error == 0) break;
  }
}