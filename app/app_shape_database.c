#include "menu_components.h"

int main(int argc, char* argv[]) {
  char* file_path;
  file_path = (char*)"test";
  LinkedList main_list;
  while (MainMenu(&main_list, file_path));
  
	if(freemem(&main_list) !=0) {
    printf("Warning: memory free failed.");
  }
  return 0;
}