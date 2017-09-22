#include <iostream>
#include "console.hpp"
#include "menu.hpp"

void add2(int& number)
{
	number += 2;
}

void printAr(int& number)
{
	std::cout << number;
	wait();
}

void exit_F(int& number ){
	number=1;
}

int main() {
	init_console();
	int number = 1;
	int exit = 0;
	menu<void> menu;
	menu.add(1, L"Add 2", std::bind(add2, std::ref(number)));
	menu.add(2, L"print", std::bind(printAr, std::ref(number)));
	menu.add(3,L"Exit", std::bind(exit_F,std::ref(exit)));
	while (exit == 0) {
		menu.exec();
	}
}