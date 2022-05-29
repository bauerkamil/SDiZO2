#include <iostream>
#include "Headers/menus/Menu.h"

int main()
{
	std::cout << "Hello World!\n";
	Menu* menu = new Menu();
	delete menu;
	exit(0);
}