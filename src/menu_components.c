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

void DataEntry() {
  printf("DataEntry() called. Functionality WIP\n");
  #ifdef QNX
  delay(1000);
  #else
  sleep(1);
  #endif
  printf("==========================================\n\n\n\n");
}

void DataQuery() {
  printf("DataQuery() called. Functionality WIP\n");
  #ifdef QNX
  delay(1000);
  #else
  sleep(1);
  #endif
  printf("==========================================\n\n\n\n");
}

int MainMenu(LinkedList *ll, const char* file_path) {
  PrintMenuHeader();
  while (1) {
    char user_option;
    GetUserMenuOption(&user_option);
    int error = 0;
    switch (user_option) {
      case '1':
        DataEntry();
        break;
      case '2':
        DataQuery();
        break;
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