// TCP.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include "Arley.hpp"
#include <chrono>
using namespace std;

void string_getter(wstring&, wstring&);
tuple<vector<uint8_t>, int> Menu_principal(vector<wstring>);
tuple<vector<uint8_t>, int> Menu_busqueda_a_fuerza_bruta(vector<wstring>);
tuple<vector<uint8_t>, int> busqueda_a_fuerza_bruta_Saliendo(vector<wstring>);
tuple<vector<uint8_t>, int> busqueda_a_fuerza_bruta_Sin_Salir(vector<wstring>);

void string_getter(wstring& T, wstring& P)
{
	while (true) {
		consola::CenterPrint(L"Ingrese string T");
		T = consola::GetString();
		consola::CenterPrint(L"Ingrese string P");
		P = consola::GetString();
		if(T.size()>P.size())
		{
			return;
		}
		consola::cls();
		CenterPrint(L"El valor ingresado es incorrecto", consola::RED, consola::bYELLOW);
		consola::Wait();
	}
}

tuple<vector<uint8_t>, int> busqueda_a_fuerza_bruta_Saliendo(vector<wstring> vStrings)
{
	int contador = 0;
	vector<uint8_t> indices{};
	auto texto = vStrings.at(0);
	auto patron = vStrings.at(1);
	for (int i = 0; i <= texto.size() - patron.size(); i++)
	{
		int j;
		for (j = 0; j < patron.size(); j++)
		{
			contador++;
			if (texto.at(i + j) != patron.at(j))
				break;
		}
		if (j == patron.size())
		{
			indices.push_back(i);
			return make_tuple(indices,contador);
		}
	}
}

tuple<vector<uint8_t>, int> busqueda_a_fuerza_bruta_Sin_Salir(vector<wstring> vStrings)
{
	int contador = 0;
	vector<uint8_t> indices{};
	auto texto = vStrings.at(0);
	auto patron = vStrings.at(1);
	for (int i = 0; i <= texto.size() - patron.size(); i++)
	{
		int j;
		for (j = 0; j < patron.size(); j++)
		{
			contador++;
			if (texto.at(i + j) != patron.at(j))
				break;
		}
		if (j == patron.size())
		{

			indices.push_back(i);
		}
	}
	return make_tuple(indices, contador);
}

tuple<vector<uint8_t>, int> Menu_busqueda_a_fuerza_bruta(vector<wstring> vStrings)
{
	//tuple<vector<uint8_t>, int> Regreso;
	Menus::Menu<vector<wstring>, tuple<vector<uint8_t>, int>> brut_menu;
	brut_menu.SetTitle(L"Cual de los dos estilos de fuerza bruta desea");
	brut_menu.add(1, L"Busqueda a fuerza bruta que sale a la primera", busqueda_a_fuerza_bruta_Saliendo, vStrings);
	brut_menu.add(2, L"Busqueda a fuerza bruta que busca todas las ocurrencias", busqueda_a_fuerza_bruta_Sin_Salir, vStrings);
	brut_menu.add(0, L"Retroceder", Menu_principal, vStrings);
	brut_menu.print();
	return brut_menu.to_return();
}

tuple<vector<uint8_t>, int> Menu_principal(vector<wstring> vStrings)
{
	//tuple<vector<uint8_t>, int> Regreso;
	Menus::Menu<vector<wstring>, tuple<vector<uint8_t>, int>> MainMenu;
	MainMenu.SetTitle(L"SELECCIONE EL METODO DE BUSQUEDA");
	MainMenu.add(1, L"A fuerza bruta", Menu_busqueda_a_fuerza_bruta, vStrings);
	MainMenu.print();
	return MainMenu.to_return();

}

int main()
{
	wstring T, P;
	consola::InitConsole();
	//Start code bellow
	string_getter(T, P);
	vector<wstring> Strings_T_P{T,P};
	consola::cls();
	auto Regreso = Menu_principal(Strings_T_P);
	auto Indices =get<0>(Regreso);
	auto Conteo = get<1>(Regreso);

	if (Indices.empty())
	{
		consola::printLn(L"No se encontro el patron");
	}else
	{
		for(auto a: Indices)
		{
			consola::printLn(L"Patron encontrado en el indice " + to_wstring(a));
		}
	}
	consola::printLn(L"El numero de comparaciones hechas fue de: " + to_wstring(Conteo));
	consola::Wait();
}
