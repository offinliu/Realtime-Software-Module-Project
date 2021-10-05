#ifndef MENU_COMPONENTS
#define MENU_COMPONENTS

#include "linked_list_struct.h"

int MainMenu(LinkedList *ll, const char* file_path);
void PrintMenuHeader();
void PrintMenuOptions();
void GetUserMenuOption(char* user_input_ptr);

void DataQuery();
void DataEntry();
void SaveCurrentDB();
void LoadDB(char* filepath[]);
#endif /* MENU_COMPONENTS */
