// TCP.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include "Arley.hpp"

using namespace std;

/* El siguiente programa lo que hara será es almacenar un char, determinara 
 *
 */
int main()
{
	consola::InitConsole();
	auto r=consola::GetNumber(L"Ingrese un numero");
	consola::printLn(to_wstring(r));

	consola::Wait();
	return 0;
}