#ifndef ARLEY_ARLEY_HPP
#define ARLEY_ARLEY_HPP
#ifdef _MSC_VER
#pragma once
#include "stdafx.h"
#endif  // _MSC_VER

#define NOMINMAX //Disable Max an Min in MSC
#include <Windows.h>
#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <cstdint>
#include <type_traits>
#include <typeinfo>

#if (__cplusplus < 201402L)
//static_assert(false, "Se necesita usar el C++17 para este header");
#endif

/**
 * \brief Namespace para funciones usadas para consola de Windows
 */
namespace consola
{
	HWND Consol;
	HANDLE ConsOut, ConsIn;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	enum ForColor {
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
	enum BackColor {
		bBLACK = 0,
		bDARKBLUE = BACKGROUND_BLUE,
		bDARKGREEN = BACKGROUND_GREEN,
		bDARKCYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
		bDARKRED = BACKGROUND_RED,
		bDARKMAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
		bDARKYELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
		bDARKGRAY = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		bGRAY = BACKGROUND_INTENSITY,
		bBLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		bGREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		bCYAN = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
		bRED = BACKGROUND_INTENSITY | BACKGROUND_RED,
		bMAGENTA = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		bYELLOW = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		bWHITE = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	};

	bool SetUnicode();

	bool print(const std::wstring, const WORD Col = WHITE, const WORD bCol = bBLACK);

	bool printLn(const std::wstring Str = L"\n", const WORD col = WHITE, const WORD bCol = bBLACK);

	bool printLn(std::string Str = "\n", WORD col = WHITE, WORD bCol = bBLACK);

	bool SetTitle(const std::wstring);

	void cls(const WORD Col = WHITE, const  WORD bCol = bBLACK);

	void Goto(const short, const short);

	void Wait();

	void InitConsole();

	bool ColorLine(const WORD, const WORD);

	std::wstring GetString();

	bool CenterPrint(const std::wstring, const WORD, const WORD, const bool);

	inline void InitConsole()
	{
		SetUnicode();
		ConsOut = GetStdHandle(STD_OUTPUT_HANDLE);
		ConsIn = GetStdHandle(STD_INPUT_HANDLE);
	}

	inline std::wstring GetString()
	{
		std::wstring regreso;
		std::wcin >> regreso;
		std::wcin.ignore(std::numeric_limits<long long>::max(), '\n');
		return regreso;
	}

	template< typename T>
	T getType(const std::wstring Pedido, const T minVal = std::numeric_limits<T>::lowest(), const T maxVal = std::numeric_limits<T>::max(), const std::wstring Error = L"El valor ingresado no es correcto") {
		auto fl = false; //Flag that is set to let the loop finish when the conditions are given
		std::wstring Ingreso;
		while (true)
		{
			cls();
			printLn(Pedido);
			Ingreso = GetString();
			for (wchar_t a : Ingreso)
			{
				auto check = static_cast<unsigned char>(a);
				if (!(isdigit(check) || a == L'.' || a == L','))
				{
					printLn(Error, RED);
					printLn(std::to_wstring(check) + std::wstring(L" No es un digito"), RED);		//Now only a ugly one
					fl = true;
				}
			}
			if (fl)
			{
				Wait();
				continue;
			}
			auto Number = std::stof(Ingreso);
			if (Number<minVal || Number>maxVal)
			{
				printLn(Error, RED);
				printLn(std::to_wstring(Number) + std::wstring(L"Esta fuera del rango de ") + std::to_wstring(minVal) + std::wstring(L" A ") + std::to_wstring(maxVal));
				fl = true;
			}
			if (fl)
			{
				Wait();
				continue;
			}
			break;
		}
		return static_cast<T>(stold(Ingreso));
	}

	[[deprecated("replaced by getType, templatic code, better ")]]
	inline long double GetNumber(const std::wstring Pedido, const std::wstring Error = L"El valor ingresado no es correcto")
	{
		auto fl = false; //Flag that is set to let the loop finish when the conditions are given
		std::wstring Ingreso;
		while (true)
		{
			cls();
			printLn(Pedido);
			Ingreso = GetString();
			for (wchar_t a : Ingreso)
			{
				if (!(isdigit(a) || (a == L'.')))
				{
					printLn(Error, RED);
					printLn(std::to_wstring(a) + std::wstring(L" No es un digito"), RED);		//Now only a ugly one
					fl = true;
				}
			}
			if (fl)
			{
				continue;
			}
			break;
		}
		return std::stold(Ingreso);
	}

	inline float GetNumberRanged(const std::wstring Pedido, const float minVal = -FLT_MAX, const float maxVal = FLT_MAX, const std::wstring Error = L"El valor ingresado no es correcto")
	{
		auto fl = false; //Flag that is set to let the loop finish when the conditions are given
		std::wstring Ingreso;
		while (true)
		{
			cls();
			printLn(Pedido);
			Ingreso = GetString();
			for (auto a : Ingreso)
			{
				if (!(isdigit(a)))
				{
					printLn(Error, RED);
					printLn(a + std::wstring(L" No es un digito"), RED);		//Now only a ugly one
					fl = true;
				}
			}
			float Number = std::stof(Ingreso);
			if (Number<minVal || Number>maxVal)
			{
				printLn(Error, RED);
				printLn(std::to_wstring(Number) + std::wstring(L"Esta fuera del rango de ") + std::to_wstring(minVal) + std::wstring(L" A ") + std::to_wstring(maxVal));
				fl = true;
			}
			if (fl)
			{
				continue;
			}
			break;
		}
		return std::stof(Ingreso);
	}

	inline bool SetUnicode() {
		return SetConsoleOutputCP(CP_UTF8);
	}

	inline bool printLn(std::string Str, WORD col, WORD bCol)
	{
		std::wstring wStr(Str.begin(), Str.end());
		return printLn(wStr, col, bCol);
	}

	inline bool printLn(const std::wstring Str, const WORD col, const WORD bCol) {
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		SetConsoleTextAttribute(ConsOut, col | bCol);
		COORD Start = csbiInfo.dwCursorPosition;
		DWORD Nm = 0;
		//Start.X++;
		WriteConsoleW(ConsOut, Str.c_str(), static_cast<DWORD>(Str.length()), &Nm, nullptr);
		Start.Y++;
		SetConsoleCursorPosition(ConsOut, Start);
		SetConsoleTextAttribute(ConsOut, WHITE | bBLACK);
		return Str.length() == static_cast<size_t>(Nm);
	}

	inline bool print(const std::wstring Str, const WORD Col, const WORD bCol) {
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		SetConsoleTextAttribute(ConsOut, Col | bCol);
		DWORD Nm = 0;
		WriteConsoleW(ConsOut, Str.c_str(), static_cast<DWORD>(Str.length()), &Nm, nullptr);
		return Str.length() == static_cast<size_t>(Nm);
	}
	inline bool CenterPrint(const std::wstring Str, const WORD Col, const WORD bCol, const bool colorization = true) {
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		SetConsoleTextAttribute(ConsOut, Col | bCol);
		COORD position = csbiInfo.dwCursorPosition;
		COORD ConSize = csbiInfo.dwSize;
		DWORD Nm = 0;
		size_t StrSize = Str.size();
		position.X = ConSize.X / 2 - (StrSize / 2);
		SetConsoleCursorPosition(ConsOut, position);
		WriteConsoleW(ConsOut, Str.c_str(), Str.length(), &Nm, nullptr);
		if (colorization)
		{
			ColorLine(Col, bCol);
		}
		position.Y++;
		SetConsoleCursorPosition(ConsOut, position);
		SetConsoleTextAttribute(ConsOut, WHITE | bBLACK);
		return Str.length() == static_cast<size_t>(Nm);
	}

	inline bool ColorLine(const WORD Col, const WORD bCol)
	{
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		auto position = csbiInfo.dwCursorPosition;
		position.X = 0;
		//auto ConSize = csbiInfo.dwSize;
		DWORD Nm = 0;
		DWORD dwConSize = csbiInfo.dwSize.X;
		//FillConsoleOutputCharacterW(ConsOut, L' ', dwConSize, position, &Nm);
		FillConsoleOutputAttribute(ConsOut, Col | bCol, dwConSize, position, &Nm);
		SetConsoleCursorPosition(ConsOut, position);
		SetConsoleTextAttribute(ConsOut, WHITE | bBLACK);
		return dwConSize == Nm;
	}

	inline bool SetTitle(const std::wstring Titulo) {
		return (SetConsoleTitleW(Titulo.c_str()));
	}

	inline void cls(const WORD Col, const WORD bCol) {
		COORD coordScreen = { 0, 0 };
		DWORD cCharsWritten;
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		DWORD dwConSize = csbiInfo.dwSize.X * csbiInfo.dwSize.Y;
		FillConsoleOutputCharacterW(ConsOut, L' ', dwConSize, coordScreen, &cCharsWritten);
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		FillConsoleOutputAttribute(ConsOut, Col | bCol, dwConSize, coordScreen, &cCharsWritten);
		SetConsoleCursorPosition(ConsOut, coordScreen);
	}

	inline void Goto(const short X, const short Y) {
		COORD N; N.X = X; N.Y = Y;
		SetConsoleCursorPosition(ConsOut, N);
	}
	inline void Wait() {
		std::wcin.ignore(std::numeric_limits<long long>::max(), '\n');
		//getchar();
		//std::wcin.get();
	}
}



namespace Menus
{
	
	typedef std::tuple<uint8_t, std::wstring, std::function<void()>> MENU_t;
	typedef std::vector<MENU_t> MENU_v;

	template <typename... T>
	class MenuF
	{
		std::vector<std::tuple<T...>> S_VectorTupleContainter;
		std::wstring S_Title = L"Menu:";
		std::wstring S_ErrorOut = L"Valor incorrecto";
		std::wstring S_InicioOp = L"N.";
		std::wstring S_SeparacionOp = L"\t";
		DWORD S_consoleTitleColor = consola::ForColor::RED;
		DWORD S_consoleTitleColorb = consola::BackColor::bBLACK;
		DWORD S_consoleErrorColor = consola::ForColor::RED;
		DWORD S_consoleErrorColorb = consola::BackColor::bBLACK;
		DWORD S_consoleOptionColor = consola::ForColor::WHITE;
		DWORD S_consoleOptionColorb = consola::BackColor::bBLACK;
	public:
		void add(std::tuple<T...> Tuple)
		{
			S_VectorTupleContainter.push_back(Tuple);
		}
		void printOption()
		{
			consola::cls();
			consola::printLn(S_SeparacionOp + S_SeparacionOp + S_Title, S_consoleTitleColor, S_consoleTitleColorb);
			for (std::tuple<T...> r : S_VectorTupleContainter) {
				consola::printLn(S_InicioOp + std::to_wstring(std::get<0>(r)) + S_SeparacionOp + std::to_wstring(std::get<1>(r)), S_consoleOptionColor, S_consoleOptionColorb);
			}
		}
		bool IsValidNumber(const std::wstring stringToValidate)
		{
			for (auto a : stringToValidate)
			{
				if (!isdigit(a))
				{
					consola::printLn(S_ErrorOut, S_consoleErrorColor, S_consoleErrorColorb);
					consola::printLn(L"No es un numero correcto", S_consoleErrorColor, S_consoleErrorColorb);
					consola::Wait();
					return false;
				}
			}
			auto Op = stoi(stringToValidate);
			for (std::tuple<T...> r : S_VectorTupleContainter) {
				if (std::get<0>(r) == Op) {
					return true;
				}
			}
				consola::printLn(S_ErrorOut, S_consoleErrorColor, S_consoleErrorColorb);
				consola::Wait();
				return false;
		}
		uint8_t selector()
		{
			std::wstring ConsoleInput;
			do {
				printOption();
				ConsoleInput = consola::GetString();
			} while (IsValidNumber(ConsoleInput));
			return stoi(ConsoleInput);
		}
		void Selector_Screen()
		{
			for (std::tuple<T...> r : S_VectorTupleContainter) {
				for (int i = 0; i < std::tuple_size<decltype(r)>::value; i++)
				{
					if (std::is_same<std::tuple_element<i, r>::type, std::function>())
					{
						std::get<i>(r)();
					}
				}
				consola::printLn(L"ESTO ESTA MAL WE");
			}
		}
		void SetTitle(const std::wstring text) { S_Title = text + L":"; }
		void SetError(const std::wstring text) { S_ErrorOut = text; }
		void SetInicioOption(const std::wstring text) { S_InicioOp = text; }
		void SetSeparatorOption(const std::wstring text) { S_SeparacionOp = text; }
		void SetConsoleTitleColor(const int Col) { S_consoleTitleColor = Col; }
		void SetConsoleErrorColor(const int Col) { S_consoleErrorColor = Col; }
		void SetConsoleOptionColor(const int Col) { S_consoleOptionColor = Col; }
		void SetConsoleTitlebackgroundColor(const int Col) { S_consoleTitleColorb = Col; }
		void SetConsoleErrorbackgroundColor(const int Col) { S_consoleErrorColorb = Col; }
		void SetConsoleOptionbackgroundColor(const int Col) { S_consoleErrorColorb = Col; }
		std::wstring GetTitle() const { return S_Title; }
	};


	template <typename Argument_t=void, typename Return_t=void, typename Full_t=Return_t(Argument_t)>
	class Menu : protected std::vector<std::tuple<uint8_t, std::wstring, std::function<Full_t>, Argument_t>> {
	public: 
		typedef Argument_t Arg;
		void add(const uint8_t Number, const std::wstring string,const std::function<Full_t> functionX,const Argument_t Values)
		{
			this->push_back(make_tuple(Number, string, functionX, Values));
		}
		void print()
		{
			while (true)
			{
				consola::cls();
				consola::printLn(SeparacionOp + SeparacionOp + Title, consoleTitleColor, consoleTitleColorb);
				for (auto r : *this) {
					consola::printLn(InicioOp + std::to_wstring(std::get<0>(r)) + SeparacionOp + std::get<1>(r), consoleOptionColor, consoleOptionColorb);
				}
				auto Failbool = false;

				auto Tmp = consola::GetString();
				for (auto a : Tmp)
				{
					if (!isdigit(a))
					{
						consola::printLn(ErrorOut, consoleErrorColor, consoleErrorColorb);
						consola::printLn(L"No es un numero correcto", consoleErrorColor, consoleErrorColorb);
						consola::Wait();
						Failbool = true;
					}
				}
				if (Failbool)
				{
					continue;
				}
				auto Op = std::stoi(Tmp);
				auto correctOp = false;
				for (auto r : *this) {
					correctOp = false;
					if (std::get<0>(r) == Op) {
						consola::cls();
						auto R = std::get<2>(r);
						
						R(std::get<3>(r));
						correctOp = true;
						break;
					}
				}
				if (!correctOp) {
					consola::printLn(ErrorOut, consoleErrorColor, consoleErrorColorb);
					consola::Wait();
					continue;
				}
				break;
			}
		}
		void SetTitle(const std::wstring text) { Title = text + L":"; }
		void SetError(const std::wstring text) { ErrorOut = text; }
		void SetInicioOption(const std::wstring text) { InicioOp = text; }
		void SetSeparatorOption(const std::wstring text) { SeparacionOp = text; }
		void SetConsoleTitleColor(const int Col) { consoleTitleColor = Col; }
		void SetConsoleErrorColor(const int Col) { consoleErrorColor = Col; }
		void SetConsoleOptionColor(const int Col) { consoleOptionColor = Col; }
		void SetConsoleTitlebackgroundColor(const int Col) { consoleTitleColorb = Col; }
		void SetConsoleErrorbackgroundColor(const int Col) { consoleErrorColorb = Col; }
		void SetConsoleOptionbackgroundColor(const int Col) { consoleErrorColorb = Col; }
		std::wstring GetTitle() const { return Title; }
	protected:
		
		std::wstring Title = L"Menu:";
		std::wstring ErrorOut = L"Valor incorrecto";
		std::wstring InicioOp = L"N.";
		std::wstring SeparacionOp = L"\t";
		DWORD consoleTitleColor = consola::ForColor::RED;
		DWORD consoleTitleColorb = consola::BackColor::bBLACK;
		DWORD consoleErrorColor = consola::ForColor::RED;
		DWORD consoleErrorColorb = consola::BackColor::bBLACK;
		DWORD consoleOptionColor = consola::ForColor::WHITE;
		DWORD consoleOptionColorb = consola::BackColor::bBLACK;
	};

	template <typename T>
	class Pantalla : protected Menu<T>
	{
	public:
		void SetTitle(const std::wstring text) { Title = text; }
		void print(const bool center = false)
		{
			while (true)
			{
				consola::cls();
				consola::CenterPrint(Title, consoleTitleColor, consoleTitleColorb);
				{
					GetConsoleScreenBufferInfo(consola::ConsOut, &consola::csbiInfo);
					COORD Start = consola::csbiInfo.dwCursorPosition;
					consola::Goto(0, Start.Y + 2);
				}
				if (center) {
					for (auto r : *this) {
						consola::CenterPrint(InicioOp + std::to_wstring(std::get<0>(r)) + SeparacionOp + std::get<1>(r), consoleOptionColor, consoleOptionColorb);
					}
				}
				else {
					for (auto r : *this) {
						consola::printLn(InicioOp + std::to_wstring(std::get<0>(r)) + SeparacionOp + std::get<1>(r), consoleOptionColor, consoleOptionColorb);
					}
				}
				std::wstring Tmp;
				bool Failbool = false;

				Tmp = consola::GetString();
				if (center)
				{
					for (auto a : Tmp)
					{
						if (!isdigit(a))
						{
							consola::CenterPrint(ErrorOut, consoleErrorColor, consoleErrorColorb);
							consola::CenterPrint(L"No es un numero correcto", consoleErrorColor, consoleErrorColorb);
							consola::Wait();
							Failbool = true;
						}
					}
				}
				else {
					for (auto a : Tmp)
					{
						if (!isdigit(a))
						{
							consola::printLn(ErrorOut, consoleErrorColor, consoleErrorColorb);
							consola::printLn(L"No es un numero correcto", consoleErrorColor, consoleErrorColorb);
							consola::Wait();
							Failbool = true;
						}
					}
				}
				if (Failbool)
				{
					continue;
				}
				int Op = stoi(Tmp);
				bool correctOp = false;
				for (auto r : *this) {
					correctOp = false;
					if (std::get<0>(r) == Op) {
						consola::cls();
						std::get<2>(r)();
						correctOp = true;
						break;
					}
				}
				if (!correctOp) {
					consola::printLn(ErrorOut, consoleErrorColor, consoleErrorColorb);
					consola::Wait();
					continue;
				}
				break;
			}
		}
	private:
		DWORD consoleTitleColor = consola::ForColor::DARKRED;
		DWORD consoleTitleColorb = consola::BackColor::bYELLOW;
		DWORD ConsoleBackgroundColor = consola::BackColor::bBLUE;
		DWORD consoleErrorColor = consola::ForColor::WHITE;
		DWORD consoleErrorColorb = consola::BackColor::bRED;
	};
}

#endif //ARLEY_ARLEY_HPP