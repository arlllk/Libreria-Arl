// TCP.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include "Arley.hpp"
#include <random>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void mostrar_datos(vector<double> v)
{
	for (auto r : v)
	{
		consola::printLn(to_wstring(r));
	}
}

void busqueda_secuencial(tuple<vector<double>,double> Get)
{
	auto v = get<0>(Get);
	auto d = get<1>(Get);
	auto NoEsEncontrado = true;
	for (auto a : v)
	{
		if (a == d)
		{
			NoEsEncontrado = false;
			consola::printLn(L"El numero a buscar " + to_wstring(d) + L" a sido encontrado");
		}
	}
	if (NoEsEncontrado)
	{
		consola::printLn(L"El numero no ha sido encontrado");
	}
}


[[deprecated("Use std::sort is much better")]]
void quickSort(vector<double> &Vec, int left, int right) {
	int i = left, j = right;
	int pivot = Vec.at((left + right) / 2);

	/* partition */
	while (i <= j) {
		while (Vec.at(i) < pivot)
			i++;
		while (Vec.at(j) > pivot)
			j--;
		if (i <= j) {
			int tmp = Vec.at(i);
			Vec.at(i) = Vec.at(j);
			Vec.at(j) = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		quickSort(Vec, left, j);
	if (i < right)
		quickSort(Vec, i, right);
}

void busqueda_binaria_iterativa(const tuple<vector<double>, double> Get)
{
	auto v = get<0>(Get);
	auto dato = get<1>(Get);
	sort(v.begin(), v.end());
	size_t Inferior = 0, Superior = v.size() - 1;
	auto EsEncontrado = false;
	int c = 0;
	while (Inferior < Superior) {
		int mitad = (Inferior + Superior) / 2;
		if (v.at(mitad) == dato)
		{
			EsEncontrado = true;
			break;
		}
		else {
			c++;
		}
		if (v.at(mitad) > dato) {
			Superior = mitad;
			mitad = (Inferior + Superior) / 2;
		}
		if (v.at(mitad) < dato) {
			Inferior = mitad;
			mitad = (Inferior + Superior) / 2;
		}
	}
	if (EsEncontrado)
	{
		consola::printLn(L"Entonces el numero" +to_wstring(dato)+L" ha sido encontrado");
	}
	else {
		consola::printLn(L"El numero no ha sido contrado");
	}
}

int BusquedaBinariaRecursiva(vector <double> list, int izq, int der, double val) {
	int Medio = (izq + der) / 2;
	if (izq > der) {
		consola::printLn(L"No se encontro el numero buscado");
	}
	if (list.at(Medio) == val) {
		consola::printLn(L"Entonces el numero" + to_wstring(val) + L" ha sido encontrado en: " + to_wstring(Medio));
	}
	if (list.at(Medio) < val) {
		return BusquedaBinariaRecursiva(list, Medio + 1, der, val);
	}
	return BusquedaBinariaRecursiva(list, izq, Medio-1, val);
}

void BBR(tuple<vector<double>, double> Get) {
	auto v = get<0>(Get);
	auto Valor = get<1>(Get);
	BusquedaBinariaRecursiva(v, 0, v.size() - 1, Valor);
}


void searchalorithm(vector<double> VectorToSort) {
	Menus::Menu<tuple<vector<double>, double>> SortSelector;
	auto Number = consola::getType<double>(L"Ingresar el numero a buscar");
	auto send = make_tuple(VectorToSort, Number);
	SortSelector.SetTitle(L"Seleccionar el tipo de algoritmo de busqueda");
	SortSelector.add(1, L"Busqueda Secuencial", busqueda_secuencial, send);
	SortSelector.add(2, L"Busqueda Binaria Itinerativa", busqueda_binaria_iterativa, send);
	SortSelector.add(3, L"Busqueda Binaria Recursiva", BBR, send);
	SortSelector.print();
	consola::Wait();
}

void exitOp(vector<double> R)
{
	R.at(0) = 0;
}

int main()
{
	vector<double> Vec, F{1,1};
	consola::InitConsole();
	const auto a = consola::getType<int>(L"Ingrese cantidad de numeros aleatorios a generar");
	Vec.resize(a);
	auto LI = consola::getType<int>(L"Ingrese limite inferior");
	auto LS = consola::getType<int>(L"Ingrese limite superior");
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed1);
	for (auto &a1 : Vec) {
		a1 = LI + (generator() % (LS - LI));
	}
	consola::cls();
	HI:
	do
	{
		Menus::Menu<vector<double>> men1;
		men1.SetTitle(L"BIENVENIDO AL MENU DE ORDENAMIENTO");
		men1.add(1, L"MOSTRAR ELEMENTOS ALEATORIOS GENERADOS", mostrar_datos, Vec);
		men1.add(2, L"METODO DE BUSQUEDA", searchalorithm, Vec);
		men1.add(3, L"Salir", exitOp, F);
		men1.print();
		consola::Wait();
	} while (F.at(0));
}
