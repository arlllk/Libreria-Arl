#pragma once
#if defined (_MSC_VER)
	#include "stdafx.h"
#endif
#include <Windows.h>
#include <string>
#include <functional>
#include <vector>
#include <iostream>

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

	bool print(std::wstring, WORD Col = WHITE, WORD bCol = bBLACK);

	bool printLn(std::wstring Str = L"\n", WORD col = WHITE, WORD bCol = bBLACK);

	bool SetTitle(std::wstring);

	void cls();

	void Goto(short, short);

	void Wait();

	void ReadLn(std::wstring);

	void InitConsole();

	bool ColorLine(WORD, WORD);

	std::wstring GetString();

	bool CenterPrint(std::wstring , WORD , WORD , bool);

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
		std::wcin.ignore(INT_MAX, '\n');
		return regreso;
	}

	inline bool SetUnicode() {
		return SetConsoleOutputCP(CP_UTF8);
	}

	inline bool printLn(std::wstring Str, WORD col, WORD bCol) {
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		SetConsoleTextAttribute(ConsOut, col | bCol);
		COORD Start = csbiInfo.dwCursorPosition;
		DWORD Nm = 0;
		//Start.X++;
		WriteConsoleW(ConsOut, Str.c_str(), static_cast<DWORD>(Str.length()), &Nm, nullptr);
		Start.Y++;
		SetConsoleCursorPosition(ConsOut, Start);
		return Str.length() == static_cast<size_t>(Nm);
	}

	inline bool print(std::wstring Str, WORD Col, WORD bCol) {
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		SetConsoleTextAttribute(ConsOut, Col | bCol);
		DWORD Nm = 0;
		WriteConsoleW(ConsOut, Str.c_str(), static_cast<DWORD>(Str.length()), &Nm, nullptr);
		return Str.length() == static_cast<size_t>(Nm);
	}
	inline bool CenterPrint(std::wstring Str, WORD Col, WORD bCol, bool colorization=true) {
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		SetConsoleTextAttribute(ConsOut, Col | bCol);
		COORD position = csbiInfo.dwCursorPosition;
		COORD ConSize = csbiInfo.dwSize;
		DWORD Nm = 0;
		size_t StrSize=Str.size();
		position.X = ConSize.X / 2 - (StrSize / 2);
		SetConsoleCursorPosition(ConsOut, position);
		WriteConsoleW(ConsOut, Str.c_str(), Str.length(), &Nm, nullptr);
		if (colorization)
		{
			ColorLine(Col, bCol);
		}
		position.Y++;
		SetConsoleCursorPosition(ConsOut, position);
		return Str.length() == static_cast<size_t>(Nm);
	}

	inline bool ColorLine(WORD Col, WORD bCol)
	{
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		COORD position = csbiInfo.dwCursorPosition;
		position.X = 0;
		COORD ConSize = csbiInfo.dwSize;
		DWORD Nm = 0;
		DWORD dwConSize = csbiInfo.dwSize.X;
		//FillConsoleOutputCharacterW(ConsOut, L' ', dwConSize, position, &Nm);
		FillConsoleOutputAttribute(ConsOut, Col | bCol, dwConSize, position, &Nm);
		SetConsoleCursorPosition(ConsOut, position);
		return dwConSize == Nm;
	}

	inline bool SetTitle(std::wstring Titulo) {
		return (SetConsoleTitleW(Titulo.c_str()));
	}

	inline void cls() {
		COORD coordScreen = { 0, 0 };
		DWORD cCharsWritten;
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		DWORD dwConSize = csbiInfo.dwSize.X * csbiInfo.dwSize.Y;
		FillConsoleOutputCharacterW(ConsOut, L' ', dwConSize, coordScreen, &cCharsWritten);
		GetConsoleScreenBufferInfo(ConsOut, &csbiInfo);
		FillConsoleOutputAttribute(ConsOut, csbiInfo.wAttributes, dwConSize, coordScreen, &cCharsWritten);
		SetConsoleCursorPosition(ConsOut, coordScreen);
	}

	inline void Goto(short X, short Y) {
		COORD N; N.X = X; N.Y = Y;
		SetConsoleCursorPosition(ConsOut, N);
	}
	inline void Wait() {
		std::wcin.ignore(INT_MAX, '\n');
		std::wcin.get();
	}
	
	
}

namespace Menus
{
	typedef std::tuple<uint8_t, std::wstring, std::function<void()>> MENU_t;
	typedef std::vector<MENU_t> MENU_v;
	class Menu : public std::vector<std::tuple<uint8_t, std::wstring, std::function<void(void)>>> {
	public:
		void add(uint8_t Number, std::wstring string, std::function<void(void)> functionX)
		{
			this->push_back(make_tuple(Number, string, functionX));
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
				std::wstring Tmp;
				bool Failbool = false;

				Tmp = consola::GetString();
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
		void SetTitle(std::wstring text) { Title = text + L":"; }
		void SetError(std::wstring text) { ErrorOut = text; }
		void SetInicioOption(std::wstring text) { InicioOp = text; }
		void SetSeparatorOption(std::wstring text) { SeparacionOp = text; }
		void SetConsoleTitleColor(int Col) { consoleTitleColor = Col; }
		void SetConsoleErrorColor(int Col) { consoleErrorColor = Col; }
		void SetConsoleOptionColor(int Col) { consoleOptionColor = Col; }
		void SetConsoleTitlebackgroundColor(int Col) { consoleTitleColorb = Col; }
		void SetConsoleErrorbackgroundColor(int Col) { consoleErrorColorb = Col; }
		void SetConsoleOptionbackgroundColor(int Col) { consoleErrorColorb = Col; }
		std::wstring GetTitle() { return Title; }
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
	class Pantalla: public Menu
	{
	public:
		void SetTitle(std::wstring text) { Title = text; }
		void print(bool center=false)
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
				}else{
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
							consola::CenterPrint(ErrorOut, consoleErrorColor, consoleErrorColorb );
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
