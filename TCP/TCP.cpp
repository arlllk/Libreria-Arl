// TCP.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include "Arley.hpp"

using namespace std;

/* El siguiente programa lo que hara será es almacenar un char, determinara 
 *
 */

void opcion1()
{
	consola::printLn(L"Exito con la opcion 1");
	consola::Wait();
	return;
}

void opcion2()
{
	consola::printLn(L"Exito con la opcion 2");
	consola::Wait();
	return;
}

void opcion3()
{
	consola::printLn(L"Exito con la opcion 3");
	consola::Wait();
	return;
}

void MenuModAdd(vector<tuple<uint8_t, wstring, function<void()>>> &Menu, uint8_t number, wstring Widestring, function<void()> funcionX)
{
	Menu.push_back(make_tuple(number, Widestring, funcionX));
}

void printModMenu(vector<tuple<uint8_t, wstring, function<void()>>> &Menu)
{
	for (Menus::MENU_t V : Menu)
	{
		printLn(L"N." + to_wstring(get<0>(V)) + L"\t" + get<1>(V), consola::ForColor::WHITE, consola::BackColor::bBLACK);
	}
}

void solucionModular() {
	typedef tuple<uint8_t, wstring, function<void()>> MENU_t;
	typedef vector<MENU_t> MENU_v;
	MENU_v men;
	MenuModAdd(men,1, L"Opcion 1", opcion1);
	MenuModAdd(men,2, L"Opcion 2", opcion2);
	MenuModAdd(men,3, L"Opcion 3", opcion3);
	printModMenu(men);
	
}

void solucionOOP() {
	using namespace Menus;
	Menu MenuOOP;
	MenuOOP.SetTitle(L"Seleccion en Orientado a objetos");
	MenuOOP.add(1, L"Opcion 1", opcion1);
	MenuOOP.add(2, L"Opcion 2", opcion2);
	MenuOOP.add(3, L"Opcion 3", opcion3);

}

int main()
{
	consola::InitConsole();
	Menus::Menu Menu;
	Menu.SetTitle(L"Que tipo de programa quiere ejecutar");
	Menu.add(1, L"Por programacion Modular y estructurada", solucionModular);
	Menu.add(2, L"Por programacion via OPP", solucionOOP);
	Menu.print();
	consola::Wait();
	return 0;
}