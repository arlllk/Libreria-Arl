//
// Created by arllk on 9/15/2017.
//

#ifndef CONSOLE_CONSOLE_HPP
#define CONSOLE_CONSOLE_HPP


#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif //UNICODE


#define NOMINMAX //Disable Max an Min in MSC
#include <Windows.h>
#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <cstdint>
#include <type_traits>



	HWND consol;
	HANDLE cons_out, cons_in;
	CONSOLE_SCREEN_BUFFER_INFO csbi_info;
	enum foreground_color {
		black = 0,
		darkblue = FOREGROUND_BLUE,
		darkgreen = FOREGROUND_GREEN,
		darkcyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
		darkred = FOREGROUND_RED,
		darkmagenta = FOREGROUND_RED | FOREGROUND_BLUE,
		darkyellow = FOREGROUND_RED | FOREGROUND_GREEN,
		darkgray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		gray = FOREGROUND_INTENSITY,
		blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		cyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		red = FOREGROUND_INTENSITY | FOREGROUND_RED,
		magenta = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		white = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
	enum background_color {
		b_black = 0,
		b_darkblue = BACKGROUND_BLUE,
		b_darkgreen = BACKGROUND_GREEN,
		b_darkcyan = BACKGROUND_GREEN | BACKGROUND_BLUE,
		b_darkred = BACKGROUND_RED,
		b_darkmagenta = BACKGROUND_RED | BACKGROUND_BLUE,
		b_darkyellow = BACKGROUND_RED | BACKGROUND_GREEN,
		b_darkgray = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		b_gray = BACKGROUND_INTENSITY,
		b_blue = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		b_green = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		b_cyan = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
		b_red = BACKGROUND_INTENSITY | BACKGROUND_RED,
		b_magenta = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		b_yellow = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		b_white = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	};

	bool set_unicode();

	bool print(const std::wstring, const WORD col = white, const WORD b_col = b_black);

	bool print_ln(const std::wstring str = L"\n", const WORD col = white, const WORD b_col = b_black);

	bool print_ln(std::string str = "\n", WORD col = white, WORD b_col = b_black);

	bool set_title(const std::wstring);

	void clear_screen(const WORD col = white, const WORD b_col = b_black);

	void go_to_coord(const short, const short);

	void wait();

	void init_console();

	bool color_line(const WORD, const WORD);

	std::wstring get_string();

	bool print_center(const std::wstring, const WORD col = white, const WORD b_col = b_black,
	                  const bool colorization = true);

	bool print_right(const std::wstring, const WORD col = white, const WORD b_col = b_black,
		const bool colorization = true);

	inline void init_console()
	{
		set_unicode();
		cons_out = GetStdHandle(STD_OUTPUT_HANDLE);
		cons_in = GetStdHandle(STD_INPUT_HANDLE);
	}

	inline std::wstring get_string()
	{
		std::wstring regreso;
		const auto limiter = L'\n';
		std::getline(std::wcin,regreso,limiter);
		return regreso;
	}

	template< typename T>
	T get_type(const std::wstring pedido, const T min_val = std::numeric_limits<T>::lowest(), const T max_val = std::numeric_limits<T>::max(), const std::wstring error = L"El valor ingresado no es correcto") {
		auto fl = false; //Flag that is set to let the loop finish when the conditions are given
		std::wstring ingreso;
		while (true)
		{
			clear_screen();
			print_ln(pedido);
			ingreso = get_string(); //get string from user
			for (auto a : ingreso)
			{
				const auto check = static_cast<unsigned char>(a); 
				if (!(isdigit(check) || a == L'.' || a == L',')) //check if isn't a digit of point or comma
				{
					print_ln(error, red);
					print_ln(std::to_wstring(check) + std::wstring(L" No es un digito"), red);		//Now only a ugly one
					fl = true;
				}
			}
			if (fl) //if the previous check isn't passed this happen
			{
				wait();
				continue;
			}
			auto number = std::stold(ingreso); //convert the input to long double because is the biggest FIXME case unsigned
			if (number<min_val || number>max_val) //check if is in the bounds that is previously given
			{
				print_ln(error, red);
				print_ln(std::to_wstring(number) + std::wstring(L"Esta fuera del rango de ") + std::to_wstring(min_val) + std::wstring(L" A ") + std::to_wstring(max_val));
				fl = true;
			}
			if (fl)
			{
				wait();
				continue;
			}
			break;
		}
		return static_cast<T>(stold(ingreso)); //return a cast to T form loung double FIXME case unsigned
	}

	[[deprecated("replaced by getType, templatic code, better ")]]
	inline long double get_number(const std::wstring pedido, const std::wstring error = L"El valor ingresado no es correcto")
	{
		auto fl = false; //Flag that is set to let the loop finish when the conditions are given
		std::wstring ingreso;
		while (true)
		{
			clear_screen();
			print_ln(pedido);
			ingreso = get_string();
			for (auto a : ingreso)
			{
				if (!(isdigit(a) || (a == L'.')))
				{
					print_ln(error, red);
					print_ln(std::to_wstring(a) + std::wstring(L" No es un digito"), red);		//Now only a ugly one
					fl = true;
				}
			}
			if (fl)
			{
				continue;
			}
			break;
		}
		return std::stold(ingreso);
	}

	inline long double get_number_ranged(const std::wstring &pedido, const float min_val =std::numeric_limits<long double>::lowest(), const float max_val = std::numeric_limits<long double>::max(), const std::wstring error = L"El valor ingresado no es correcto")
	{
		auto fl = false; //Flag that is set to let the loop finish when the conditions are given
		std::wstring ingreso;
		while (true)
		{
			clear_screen();
			print_ln(pedido);
			ingreso = get_string();
			for (auto a : ingreso)
			{
				if (!(isdigit(a)))
				{
					print_ln(error, red);
					print_ln(a + std::wstring(L" No es un digito"), red);		//Now only a ugly one
					fl = true;
				}
			}
			const auto number = std::stof(ingreso);
			if (number<min_val || number>max_val)
			{
				print_ln(error, red);
				print_ln(std::to_wstring(number) + std::wstring(L"Esta fuera del rango de ") + std::to_wstring(min_val) + std::wstring(L" A ") + std::to_wstring(max_val));
				fl = true;
			}
			if (fl)
			{
				continue;
			}
			break;
		}
		return std::stold(ingreso);
	}

	inline bool set_unicode() {
		return SetConsoleOutputCP(CP_UTF8);
	}

	inline bool print_ln(std::string str, WORD col, WORD b_col)
	{
		const std::wstring w_str(str.begin(), str.end());
		return print_ln(w_str, col, b_col);
	}

	inline bool print_ln(const std::wstring str, const WORD col, const WORD b_col) {
		GetConsoleScreenBufferInfo(cons_out, &csbi_info);
		SetConsoleTextAttribute(cons_out, col | b_col);
		auto start = csbi_info.dwCursorPosition;
		DWORD nm = 0;
		//Start.X++;
		WriteConsoleW(cons_out, str.c_str(), static_cast<DWORD>(str.length()), &nm, nullptr);
		start.Y++;
		SetConsoleCursorPosition(cons_out, start);
		SetConsoleTextAttribute(cons_out, white | b_black);
		return str.length() == static_cast<size_t>(nm);
	}

	inline bool print(const std::wstring str, const WORD col, const WORD b_col) {
		GetConsoleScreenBufferInfo(cons_out, &csbi_info);
		SetConsoleTextAttribute(cons_out, col | b_col);
		DWORD nm = 0;
		WriteConsoleW(cons_out, str.c_str(), static_cast<DWORD>(str.length()), &nm, nullptr);
		return str.length() == static_cast<size_t>(nm);
	}
	inline bool print_center(const std::wstring str, const WORD col, const WORD b_col, const bool colorization) {
		GetConsoleScreenBufferInfo(cons_out, &csbi_info);
		SetConsoleTextAttribute(cons_out, col | b_col);
		auto position = csbi_info.dwCursorPosition;
		const auto con_size = csbi_info.dwSize;
		DWORD nm = 0;
		const auto str_size = str.size();
		position.X = con_size.X / 2 - static_cast<short>(str_size) / 2;
		SetConsoleCursorPosition(cons_out, position);
		WriteConsoleW(cons_out, str.c_str(), static_cast<DWORD>(str.length()), &nm, nullptr);
		if (colorization)
		{
			color_line(col, b_col);
		}
		position.Y++;
		position.X = 0;
		SetConsoleCursorPosition(cons_out, position);
		SetConsoleTextAttribute(cons_out, white | b_black);
		return str.length() == static_cast<size_t>(nm);
	}

	inline bool print_right(const std::wstring str, const WORD col, const WORD b_col,
		const bool colorization)
	{
		GetConsoleScreenBufferInfo(cons_out, &csbi_info);
		SetConsoleTextAttribute(cons_out, col | b_col);
		auto position = csbi_info.dwCursorPosition;
		const auto con_size = csbi_info.dwSize;
		DWORD nm = 0;
		const auto str_size = str.size();
		position.X = con_size.X - static_cast<short>(str_size);
		SetConsoleCursorPosition(cons_out, position);
		WriteConsoleW(cons_out, str.c_str(), static_cast<DWORD>(str.length()), &nm, nullptr);
		if (colorization)
		{
			color_line(col, b_col);
		}
		position.Y++;
		position.X = 0;
		SetConsoleCursorPosition(cons_out, position);
		SetConsoleTextAttribute(cons_out, white | b_black);
		return str.length() == static_cast<size_t>(nm);
	}

	inline bool color_line(const WORD col, const WORD b_col)
	{
		GetConsoleScreenBufferInfo(cons_out, &csbi_info);
		auto position = csbi_info.dwCursorPosition;
		position.X = 0;
		//auto ConSize = csbiInfo.dwSize;
		DWORD nm = 0;
		const DWORD dw_con_size = csbi_info.dwSize.X;
		//FillConsoleOutputCharacterW(ConsOut, L' ', dwConSize, position, &Nm);
		FillConsoleOutputAttribute(cons_out, col | b_col, dw_con_size, position, &nm);
		SetConsoleCursorPosition(cons_out, position);
		SetConsoleTextAttribute(cons_out, white | b_black);
		return dw_con_size == nm;
	}

	inline bool set_title(const std::wstring titulo) {
		return (SetConsoleTitleW(titulo.c_str()));
	}

	inline void clear_screen(const WORD col, const WORD b_col) {
		const COORD coord_screen = { 0, 0 };
		DWORD c_chars_written;
		GetConsoleScreenBufferInfo(cons_out, &csbi_info);
		const DWORD dw_con_size = csbi_info.dwSize.X * csbi_info.dwSize.Y;
		FillConsoleOutputCharacterW(cons_out, L' ', dw_con_size, coord_screen, &c_chars_written);
		GetConsoleScreenBufferInfo(cons_out, &csbi_info);
		FillConsoleOutputAttribute(cons_out, col | b_col, dw_con_size, coord_screen, &c_chars_written);
		SetConsoleCursorPosition(cons_out, coord_screen);
	}

	inline void go_to_coord(const short x, const short y) {
		COORD n; n.X = x; n.Y = y;
		SetConsoleCursorPosition(cons_out, n);
	}
	inline void wait() {
		std::wcin.ignore(std::numeric_limits<long long>::max(), '\n');
	}


#endif //CONSOLE_CONSOLE_HPP
