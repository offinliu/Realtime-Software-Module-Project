#include <stdio.h>
#include "menu_components.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
  char* filepath;
  filepath = (char*)"test";
  while (MainMenu(filepath));
  return 0;
}