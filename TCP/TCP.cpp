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
tuple<vector<uint8_t>, int> busqueda_kmp(vector<wstring>);
tuple<vector<uint8_t>, int> kmp(const wstring, const wstring);
tuple<vector<uint8_t>, int> kmp_B(const wstring&, const wstring&);

constexpr bool DEBUG = true;

void string_getter(wstring& T, wstring& P) {
	while (true) {
		consola::CenterPrint(L"Ingrese string T");
		T = consola::GetString();
		if (DEBUG) { consola::printLn(T); }
		consola::CenterPrint(L"Ingrese string P");
		P = consola::GetString();
		if (DEBUG) { consola::printLn(P); }
		if (T.size() > P.size()) { return; }
		consola::cls();
		CenterPrint(L"El valor ingresado es incorrecto", consola::RED, consola::bYELLOW);
		consola::Wait();
	}
}

tuple<vector<uint8_t>, int> busqueda_a_fuerza_bruta_Saliendo(vector<wstring> vStrings) {
	int contador = 0;
	vector<uint8_t> indices{};
	auto texto = vStrings.at(0);
	auto patron = vStrings.at(1);
	for (int i = 0; i <= texto.size() - patron.size(); i++) {
		int j;
		for (j = 0; j < patron.size(); j++) {
			contador++;
			if (texto.at(i + j) != patron.at(j))
				break;
		}
		if (j == patron.size()) {
			indices.push_back(i);
			return make_tuple(indices, contador);
		}
	}
}

tuple<vector<uint8_t>, int> busqueda_a_fuerza_bruta_Sin_Salir(vector<wstring> vStrings) {
	int contador = 0;
	vector<uint8_t> indices{};
	auto texto = vStrings.at(0);
	auto patron = vStrings.at(1);
	for (int i = 0; i <= texto.size() - patron.size(); i++) {
		int j;
		for (j = 0; j < patron.size(); j++) {
			contador++;
			if (texto.at(i + j) != patron.at(j))
				break;
		}
		if (j == patron.size()) { indices.push_back(i); }
	}
	return make_tuple(indices, contador);
}

tuple<vector<uint8_t>, int> Menu_busqueda_a_fuerza_bruta(vector<wstring> vStrings) {
	//tuple<vector<uint8_t>, int> Regreso;
	Menus::Menu<vector<wstring>, tuple<vector<uint8_t>, int>> brut_menu;
	brut_menu.SetTitle(L"Cual de los dos estilos de fuerza bruta desea");
	brut_menu.add(1, L"Busqueda a fuerza bruta que sale a la primera", busqueda_a_fuerza_bruta_Saliendo, vStrings);
	brut_menu.add(2, L"Busqueda a fuerza bruta que busca todas las ocurrencias", busqueda_a_fuerza_bruta_Sin_Salir, vStrings);
	brut_menu.add(0, L"Retroceder", Menu_principal, vStrings);
	brut_menu.print();
	return brut_menu.to_return();
}

tuple<vector<uint8_t>, int> Menu_principal(vector<wstring> vStrings) {
	//tuple<vector<uint8_t>, int> Regreso;
	Menus::Menu<vector<wstring>, tuple<vector<uint8_t>, int>> MainMenu;
	MainMenu.SetTitle(L"SELECCIONE EL METODO DE BUSQUEDA");
	MainMenu.add(1, L"A fuerza bruta", Menu_busqueda_a_fuerza_bruta, vStrings);
	MainMenu.add(2, L"Usando KMP", busqueda_kmp, vStrings);
	MainMenu.print();
	return MainMenu.to_return();
}

tuple<vector<uint8_t>, int> busqueda_kmp(vector<wstring> vStrings) {
	auto s1 = vStrings.at(0);
	auto s2 = vStrings.at(1);
	return kmp_B(s1, s2);
}

void kmp_table(wstring W, vector<int>& T) {
	int pos = 1, cnd = 0, comparation = 0;
	T.push_back(-1);
	while (pos < W.size()) {
		if (W.at(pos) == W.at(cnd)) {
			T.push_back(T.at(cnd));
			pos++;
			cnd++;
		}
		else {
			T.push_back(cnd);
			cnd = T.at(cnd);
			while (cnd >= 0 && W.at(pos) != W.at(cnd)) { cnd = T.at(cnd); }
			pos++;
			cnd++;
		}
	}
	//T.push_back(cnd);
}

tuple<vector<uint8_t>, int> kmp(const wstring S, const wstring W) {
	int m = 0, i = 0, comparation = 0;
	vector<uint8_t> indice{};
	vector<int> table;
	kmp_table(W, table);
	for (auto element : table) { cout << element << ", "; }
	while (m + 1 < S.size()) {
		comparation++;
		if (W.at(i) == S.at(m + i)) {
			i++;
			comparation++;
			if (i == W.size()) {
				indice.push_back(m);
				m = m + 1 - table.at(i);
				i = table.at(i);
			}
		}
		else {
			comparation++;
			if (table.at(i) > -1) {
				m = m + 1 - table.at(i);
				i = table.at(i);
			}
			else {
				m = m + i + 1;
				i = 0;
			}
		}
	}
	return make_tuple(indice, comparation);
}

tuple<vector<uint8_t>, int> kmp_B(const wstring& T, const wstring& P) {
	int comparation = 0;
	vector<uint8_t> indice{};
	if (P.empty()) return make_tuple(indice, comparation);

	vector<int> pi(P.size(), 0);
	for (int i = 1, k = 0; i < P.size(); ++i) {
		while (k && P[k] != P[i]) {
			k = pi[k - 1];
			comparation++;
		}
		if (P[k] == P[i]) ++k;
		pi[i] = k;
	}

	for (int i = 0, k = 0; i < T.size(); ++i) {
		while (k && P[k] != T[i]) {
			k = pi[k - 1];
			comparation++;
		}
		if (P[k] == T[i]) { ++k; }
		if (k == P.size()) {
			comparation++;
			indice.push_back(i - k + 1);
		}
	}

	return make_tuple(indice, comparation);
}

int main() {
	wstring T, P;
	consola::InitConsole();
	//Start code bellow
	//string_getter(T, P);
	T = L"AAAAAAAAAA";
	P = L"AAAAA";
	vector<wstring> Strings_T_P{T,P};
	consola::cls();
	do {
		auto Regreso = Menu_principal(Strings_T_P);
		auto Indices = get<0>(Regreso);
		auto Conteo = get<1>(Regreso);

		if (Indices.empty()) { consola::printLn(L"No se encontro el patron"); }
		else { for (auto a : Indices) { consola::printLn(L"Patron encontrado en el indice " + to_wstring(a)); } }
		consola::printLn(L"El numero de comparaciones hechas fue de: " + to_wstring(Conteo));
		consola::Wait();
	}
	while (true);
}
