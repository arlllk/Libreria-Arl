//
// Created by arllk on 9/15/2017.
//

#ifndef CONSOLE_MENU_HPP
#define CONSOLE_MENU_HPP

#include "console.hpp"
#include <map>

template <typename ReturnVal>
class menu
{
public:
	menu()
	{
		size_ = 0;
	}

	/**
	 * \brief Add option to the menu
	 * \param number Number of option to be printed
	 * \param string Words to be Written
	 * \param function_x The fucntion send by std::bind
	 * \examples 
	 * menu.add(1,L"Words to be written",std::bind(function_to_pass, std::ref(value_to_pass)));
	 * menu.add(2,L"Words to be written", std::bind(function_to_pass, std::cref(const_value_to_pass)));
	 */
	void add(uint32_t number, std::wstring string, std::function<ReturnVal()> function_x)
	{
		m_number.push_back(number);
		m_string.push_back(string);
		m_function.push_back(function_x);
		size_++;

	}
	void print()
	{
		if (m_number.size()!=m_string.size()||m_number.size()!=m_function.size())
		{
			print_ln(L"VECTOR SIZE ERROR");
			wait();
			return;
		}
		print_center(m_title_, static_cast<const WORD>(m_console_title_color_),
			static_cast<const WORD>(m_console_title_colorb_));
		for(int i=0;i<size_;i++)
		{
			print_ln(m_inicio_op_ + std::to_wstring(m_number.at(i)) + m_separacion_op_ + m_string.at(i), static_cast<WORD>(m_console_option_color_), static_cast<WORD>(m_console_option_colorb_));
		}
	}
	ReturnVal exec()
	{
		while (true)
		{
			clear_screen();
			print();
			auto failbool = false;
			auto string_get = get_string();
			if (string_get == L"") //check and bypass if is pressed enter 
			{
				continue;
			}
			for (auto &a : string_get)
			{
				if (!isdigit(a)) //check if the input is a digit
				{
					print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					print_ln(m_incorrect_number_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					wait();
					failbool = true;
				}
			}
			if (failbool)
			{
				continue;
			}
			failbool = false;
			auto selector_value = std::stoi(string_get); //convert from text to int
			unsigned int place =0;
			
			for (int i=0; i<size_; i++)
			{
				if (selector_value == m_number.at(i))
				{
					place = i;
					failbool = true;
				}

			}
			if (!failbool)//if selected value isn't find
			{
				print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
					static_cast<const WORD>(m_console_error_colorb_));
				wait();
				continue;
			}
			clear_screen();
			auto funct = m_function.at(place);
			return funct();
		}
	}


private:
	size_t size_;
	std::vector<uint32_t> m_number;
	std::vector<std::wstring> m_string;
	std::vector <std::function<ReturnVal()>> m_function;

	std::wstring m_title_ = L"Menu:";
	std::wstring m_error_out_ = L"Valor incorrecto";
	std::wstring m_inicio_op_ = L"N.";
	std::wstring m_separacion_op_ = L"\t";
	std::wstring m_incorrect_number_ = L"No es un numero correcto";
	DWORD m_console_title_color_ = red;
	DWORD m_console_title_colorb_ = b_black;
	DWORD m_console_error_color_ = red;
	DWORD m_console_error_colorb_ = b_black;
	DWORD m_console_option_color_ = white;
	DWORD m_console_option_colorb_ = b_black;
};

//VOID ESPECIAZLIATION
template <>
class menu<void>
{
public:
	menu()
	{
		size_ = 0;
	}

	/**
	* \brief Add option to the menu, this one is return type void
	* \param number the number of option to be printed
	* \param string Words to be Written
	* \param function_x The function send by std::bind
	* \examples
	* menu.add(1,L"Words to be written",std::bind(function_to_pass, std::ref(value_to_pass)));
	* menu.add(2,L"Words to be written", std::bind(function_to_pass, std::cref(const_value_to_pass)));
	*/
	void add(uint32_t number, std::wstring string, std::function<void()> function_x)
	{
		m_number.push_back(number);
		m_string.push_back(string);
		m_function.push_back(function_x);
		size_++;

	}
	void print()
	{
		if (m_number.size() != m_string.size() || m_number.size() != m_function.size())
		{
			print_ln(L"VECTOR SIZE ERROR");
			wait();
			return;
		}
		print_center(m_title_, static_cast<const WORD>(m_console_title_color_),
			static_cast<const WORD>(m_console_title_colorb_));
		for (int i = 0; i<size_; i++)
		{
			print_ln(m_inicio_op_ + std::to_wstring(m_number.at(i)) + m_separacion_op_ + m_string.at(i), static_cast<WORD>(m_console_option_color_), static_cast<WORD>(m_console_option_colorb_));
		}
	}
	void exec()
	{
		while (true)
		{
			clear_screen();
			print();
			auto failbool = false;
			auto string_get = get_string();
			if (string_get == L"") //check and bypass if is pressed enter 
			{
				continue;
			}
			for (auto &a : string_get)
			{
				if (!isdigit(a)) //check if the input is a digit
				{
					print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					print_ln(m_incorrect_number_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					wait();
					failbool = true;
				}
			}
			if (failbool)
			{
				continue;
			}
			failbool = false;
			auto selector_value = std::stoi(string_get); //convert from text to int
			unsigned int place = 0;

			for (int i = 0; i<size_; i++)
			{
				if (selector_value == m_number.at(i))
				{
					place = i;
					failbool = true;
				}

			}
			if (!failbool)//if selected value isn't find
			{
				print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
					static_cast<const WORD>(m_console_error_colorb_));
				wait();
				continue;
			}
			clear_screen();
			auto funct = m_function.at(place);
			return funct();
		}
	}


private:
	size_t size_;
	std::vector<uint32_t> m_number;
	std::vector<std::wstring> m_string;
	std::vector <std::function<void()>> m_function;

	std::wstring m_title_ = L"Menu:";
	std::wstring m_error_out_ = L"Valor incorrecto";
	std::wstring m_inicio_op_ = L"N.";
	std::wstring m_separacion_op_ = L"\t";
	std::wstring m_incorrect_number_ = L"No es un numero correcto";
	DWORD m_console_title_color_ = red;
	DWORD m_console_title_colorb_ = b_black;
	DWORD m_console_error_color_ = red;
	DWORD m_console_error_colorb_ = b_black;
	DWORD m_console_option_color_ = white;
	DWORD m_console_option_colorb_ = b_black;
};




//List of functions that continue to improve to be this new great function MFGA, Nice to see how the iterations
//became this one
/*
template <typename Argument_t, typename Return_t>
class menu2 : protected std::map<uint8_t, std::tuple<std::wstring, std::function<Return_t(Argument_t)>, Argument_t>> {
public:
	typedef Argument_t arg;  
	void add(uint8_t number, std::wstring string, std::function<Return_t(Argument_t)> function_x, Argument_t& values)
	{
		this->try_emplace(number,std::make_tuple(string,function_x,&values)); //insert if is possible the values
	}
	void print()
	{
		print_center(m_title_, static_cast<const WORD>(m_console_title_color_),
			static_cast<const WORD>(m_console_title_colorb_));
		for (auto &r : *this) {
			print_ln(m_inicio_op_ + std::to_wstring(r.first) + m_separacion_op_ + std::get<0>(r.second), static_cast<WORD>(m_console_option_color_), static_cast<WORD>(m_console_option_colorb_));
		}
	}
	//Execute and ask for an input
	void exec()
	{
		while (true)
		{
			clear_screen();
			print();
			auto failbool = false;
			auto string_get = get_string();
			if (string_get == L"") //check and bypass if is pressed enter 
			{
				continue;
			}
			for (auto &a : string_get)
			{
				if (!isdigit(a)) //check if the input is a digit
				{
					print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					print_ln(m_incorrect_number_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					wait();
					failbool = true;
				}
			}
			if (failbool)
			{
				continue;
			}

			auto selector_value = std::stoi(string_get); //convert from text to int

			auto search = this->find(selector_value); //iterator that checks for value
			if (search != this->end()) { //if is find
				clear_screen();
				auto function_val = std::get<1>(search->second);
				//auto result_of_invoke = std::invoke(function_val, std::get<2>(search->second));//This is gonna make some problems in the future HOW?
				auto result_of_invoke = function_val(std::get<2>(search->second));
				m_to_return_ = result_of_invoke;
				break;
			}
			//if isn't find you go to here
			print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
				static_cast<const WORD>(m_console_error_colorb_));
			wait();

		}

	}
	Return_t getReturn()
	{
		return m_to_return_;
	}

private:
	Return_t m_to_return_;
	std::wstring m_title_ = L"Menu:";
	std::wstring m_error_out_ = L"Valor incorrecto";
	std::wstring m_inicio_op_ = L"N.";
	std::wstring m_separacion_op_ = L"\t";
	std::wstring m_incorrect_number_ = L"No es un numero correcto";
	DWORD m_console_title_color_ = red;
	DWORD m_console_title_colorb_ = b_black;
	DWORD m_console_error_color_ = red;
	DWORD m_console_error_colorb_ = b_black;
	DWORD m_console_option_color_ = white;
	DWORD m_console_option_colorb_ = b_black;

};


//FULL VOID ESPECIALIZATION
template <>
class menu2<void,void> : protected std::map<uint8_t, std::tuple<std::wstring, std::function<void(void)>>> {
public:
	void add(uint8_t number, std::wstring string, std::function<void(void)> function_x)
	{
		this->try_emplace(number, std::make_tuple(string, function_x));
	}
	void print()
	{
		print_center(m_title_, static_cast<const WORD>(m_console_title_color_),
			static_cast<const WORD>(m_console_title_colorb_));
		for (auto &r : *this) {
			print_ln(m_inicio_op_ + std::to_wstring(r.first) + m_separacion_op_ + std::get<0>(r.second), static_cast<WORD>(m_console_option_color_), static_cast<WORD>(m_console_option_colorb_));
		}
	}

	void exec()
	{
		while (true)
		{
			clear_screen();
			print();
			auto failbool = false;
			auto string_get = get_string();
			if (string_get == L"")  //check and bypass if is pressed enter 
			{
				continue;
			}
			for (auto &a : string_get) //check if the input is a digit
			{
				if (!isdigit(a))
				{
					print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					print_ln(m_incorrect_number_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					wait();
					failbool = true;
				}
			}
			if (failbool)
			{
				continue;
			}

			const auto selector_value = std::stoi(string_get); //convert from text to int

			auto search = this->find(selector_value); // iterator that checks for value
			if (search != this->end()) {
				clear_screen();
				auto function_val = std::get<1>(search->second);
				std::invoke(function_val);//different because no input or output
				break;
			}
			//this is only used if value isn't find
			print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
				static_cast<const WORD>(m_console_error_colorb_));
			wait();

		}

	}

private:
	//no return value because void return
	std::wstring m_title_ = L"Menu:";
	std::wstring m_error_out_ = L"Valor incorrecto";
	std::wstring m_inicio_op_ = L"N.";
	std::wstring m_separacion_op_ = L"\t";
	std::wstring m_incorrect_number_ = L"No es un numero correcto";
	DWORD m_console_title_color_ = red;
	DWORD m_console_title_colorb_ = b_black;
	DWORD m_console_error_color_ = red;
	DWORD m_console_error_colorb_ = b_black;
	DWORD m_console_option_color_ = white;
	DWORD m_console_option_colorb_ = b_black;

};


//PARTIAL VOID ARGUMENT SPECIALIZATION
template <typename Return_t>
class menu2<void, Return_t> : protected std::map<uint8_t, std::tuple<std::wstring, std::function<Return_t(void)>>> {
public:
	void add(uint8_t number, std::wstring string, std::function<Return_t(void)> function_x)
	{
		this->try_emplace(number, std::make_tuple(string, function_x));
	}
	void print()
	{
		print_center(m_title_, static_cast<const WORD>(m_console_title_color_),
		             static_cast<const WORD>(m_console_title_colorb_));
		for (auto &r : *this) {
			print_ln(m_inicio_op_ + std::to_wstring(r.first) + m_separacion_op_ + std::get<0>(r.second), static_cast<WORD>(m_console_option_color_), static_cast<WORD>(m_console_option_colorb_));
		}
	}

	void exec()
	{
		while (true)
		{
			clear_screen();
			print();
			auto failbool = false;
			auto string_get = get_string();
			if (string_get == L"")  //check and bypass if is pressed enter
			{
				continue;
			}
			for (auto &a : string_get) //check if the input is a digit
			{
				if (!isdigit(a))
				{
					print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
					         static_cast<const WORD>(m_console_error_colorb_));
					print_ln(m_incorrect_number_, static_cast<const WORD>(m_console_error_color_),
					         static_cast<const WORD>(m_console_error_colorb_));
					wait();
					failbool = true;
				}
			}
			if (failbool)
			{
				continue;
			}

			auto selector_value = std::stoi(string_get); //convert from text to int

			auto search = this->find(selector_value); // iterator that checks for value
			if (search != this->end()) {
				clear_screen();
				auto function_val = std::get<1>(search->second);
				auto result_of_invoke = std::invoke(function_val, std::get<2>(search->second));//This is gonna make some problems in the future HOW?
				m_to_return_ = result_of_invoke;
			}
			//this is only used if value isn't find
			print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
			         static_cast<const WORD>(m_console_error_colorb_));
			wait();

		}

	}

private:
	Return_t m_to_return_;
	std::wstring m_title_ = L"Menu:";
	std::wstring m_error_out_ = L"Valor incorrecto";
	std::wstring m_inicio_op_ = L"N.";
	std::wstring m_separacion_op_ = L"\t";
	std::wstring m_incorrect_number_ = L"No es un numero correcto";
	DWORD m_console_title_color_ = red;
	DWORD m_console_title_colorb_ = b_black;
	DWORD m_console_error_color_ = red;
	DWORD m_console_error_colorb_ = b_black;
	DWORD m_console_option_color_ = white;
	DWORD m_console_option_colorb_ = b_black;

};


//PARTIAL VOID RETURN SPECIALIZATION
template <typename Argument_t>
class menu2<Argument_t,void> : protected std::map<uint8_t, std::tuple<std::wstring, std::function<void(Argument_t)>>> {
public:
	void add(uint8_t number, std::wstring string, std::function<void(Argument_t)> function_x, Argument_t values)
	{
		this->try_emplace(number, std::make_tuple(string, function_x, values)); //inserta si se puede los valores al map
	}
	void print()
	{
		print_center(m_title_, static_cast<const WORD>(m_console_title_color_),
		             static_cast<const WORD>(m_console_title_colorb_));
		for (auto &r : *this) {
			print_ln(m_inicio_op_ + std::to_wstring(r.first) + m_separacion_op_ + std::get<0>(r.second), static_cast<WORD>(m_console_option_color_), static_cast<WORD>(m_console_option_colorb_));
		}
	}

	void exec()
	{
		while (true)
		{
			clear_screen();
			print();
			auto failbool = false;
			auto string_get = get_string();
			if (string_get == L"")  //check and bypass if is pressed enter
			{
				continue;
			}
			for (auto &a : string_get) //check if the input is a digit
			{
				if (!isdigit(a))
				{
					print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
					         static_cast<const WORD>(m_console_error_colorb_));
					print_ln(L"No es un numero correcto", static_cast<const WORD>(m_console_error_color_),
					         static_cast<const WORD>(m_console_error_colorb_));
					wait();
					failbool = true;
				}
			}
			if (failbool)
			{
				continue;
			}

			auto selector_value = std::stoi(string_get); //convert from text to int

			auto search = this->find(selector_value); // iterator that checks for value
			if (search != this->end()) {
				clear_screen();
				auto arg= search->second;
				auto function_val = std::get<1>(arg);
				std::invoke(function_val, std::get<2>(arg));
				break;
			}
			//this is only used if value isn't find
			print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
			         static_cast<const WORD>(m_console_error_colorb_));
			wait();

		}

	}

private:
	//no return value because void return
	std::wstring m_title_ = L"Menu:";
	std::wstring m_error_out_ = L"Valor incorrecto";
	std::wstring m_inicio_op_ = L"N.";
	std::wstring m_separacion_op_ = L"\t";
	DWORD m_console_title_color_ = red;
	DWORD m_console_title_colorb_ = b_black;
	DWORD m_console_error_color_ = red;
	DWORD m_console_error_colorb_ = b_black;
	DWORD m_console_option_color_ = white;
	DWORD m_console_option_colorb_ = b_black;

};


//PARTIAL VOID RETURN POINTER SPECIALIZATION FIXME
template <typename Argument_t>
class menu2<Argument_t*, void> : protected std::map<uint8_t, std::tuple<std::wstring, std::function<void(Argument_t)>, Argument_t>>{
public:
	void add(uint8_t number, std::wstring string, std::function<void(Argument_t)> function_x, Argument_t values)
	{
		this->try_emplace(number, std::make_tuple(string, function_x, values)); //inserta si se puede los valores al map
	}
	void print()
	{
		print_center(m_title_, static_cast<const WORD>(m_console_title_color_),
			static_cast<const WORD>(m_console_title_colorb_));
		for (auto &r : *this) {
			print_ln(m_inicio_op_ + std::to_wstring(r.first) + m_separacion_op_ + std::get<0>(r.second), static_cast<WORD>(m_console_option_color_), static_cast<WORD>(m_console_option_colorb_));
		}
	}

	void exec()
	{
		while (true)
		{
			clear_screen();
			print();
			auto failbool = false;
			auto string_get = get_string();
			if (string_get == L"")  //check and bypass if is pressed enter
			{
				continue;
			}
			for (auto &a : string_get) //check if the input is a digit
			{
				if (!isdigit(a))
				{
					print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					print_ln(L"No es un numero correcto", static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					wait();
					failbool = true;
				}
			}
			if (failbool)
			{
				continue;
			}

			auto selector_value = std::stoi(string_get); //convert from text to int

			auto search = this->find(selector_value); // iterator that checks for value
			if (search != this->end()) {
				clear_screen();
				auto arg = search->second;
				auto function_val = std::get<1>(arg);
				std::invoke(function_val, std::get<2>(arg));
				break;
			}
			//this is only used if value isn't find
			print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
				static_cast<const WORD>(m_console_error_colorb_));
			wait();

		}

	}

private:
	//no return value because void return
	std::wstring m_title_ = L"Menu:";
	std::wstring m_error_out_ = L"Valor incorrecto";
	std::wstring m_inicio_op_ = L"N.";
	std::wstring m_separacion_op_ = L"\t";
	DWORD m_console_title_color_ = red;
	DWORD m_console_title_colorb_ = b_black;
	DWORD m_console_error_color_ = red;
	DWORD m_console_error_colorb_ = b_black;
	DWORD m_console_option_color_ = white;
	DWORD m_console_option_colorb_ = b_black;

};


//DEPRECATED USE
template <typename Argument_t=void, typename Return_t=void>[[deprecated("Only used in case of break")]]
class menu1: protected std::vector<std::tuple<uint8_t, std::wstring, std::function<Return_t(Argument_t)>, Argument_t>>  {
public:
	typedef Argument_t arg;
	void add(const uint8_t number, const std::wstring& string,const std::function<Return_t(Argument_t)>& function_x,const Argument_t& values)
	{
		this->push_back(make_tuple(number, string, function_x, values));

	}

	void pr1_nt(){
		print_ln(m_separacion_op_ + m_separacion_op_ + m_title_, static_cast<const WORD>(m_console_title_color_),
		        static_cast<const WORD>(m_console_title_colorb_));
		for (auto &r : *this) {
			print_ln(m_inicio_op_ + std::to_wstring(std::get<0>(r)) + m_separacion_op_ + std::get<1>(r), static_cast<WORD>(m_console_option_color_), static_cast<WORD>(m_console_option_colorb_));
		}
	}
	void print()
	{
		while (true){
			clear_screen();
			pr1_nt();
			auto failbool = false;
			auto string_get = get_string();
			if (string_get==L"")
			{
				continue;
			}
			for (auto &a : string_get)
			{
				if (!isdigit(a))
				{
					print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
					        static_cast<const WORD>(m_console_error_colorb_));
					print_ln(L"No es un numero correcto", static_cast<const WORD>(m_console_error_color_),
					        static_cast<const WORD>(m_console_error_colorb_));
					wait();
					failbool = true;
				}
			}
			if (failbool)
			{
				continue;
			}
			auto selector_value = std::stoi(string_get);
			auto is_right_selector = false;
			for (auto& tupple : *this) {
				is_right_selector = false;
				if (std::get<0>(tupple) == selector_value) {
					clear_screen();
					auto function_val = std::get<2>(tupple);
					auto result_of_invoke =std::invoke(function_val,std::get<3>(tupple));//This is gonna make some problems in the future HOW?

					m_to_return_ = result_of_invoke;
					is_right_selector = true;
					break;
				}
			}
			if (!is_right_selector) {
				print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
				        static_cast<const WORD>(m_console_error_colorb_));
				wait();
				continue;
			}
			break;
		}
	}
	void set_title(const std::wstring& text) { m_title_ = text + L":"; }
	void set_error(const std::wstring& text) { m_error_out_ = text; }
	void set_inicio_option(const std::wstring& text) { m_inicio_op_ = text; }
	void set_separator_option(const std::wstring& text) { m_separacion_op_ = text; }
	void set_console_title_color(const int& color) { m_console_title_color_ = static_cast<DWORD>(color); }
	void set_console_error_color(const int &color) { m_console_error_color_ = static_cast<DWORD>(color); }
	void set_console_option_color(const int &color) { m_console_option_color_ = static_cast<DWORD>(color); }
	void set_console_titlebackground_color(const int& color) { m_console_title_colorb_ = static_cast<DWORD>(color); }
	void set_console_errorbackground_color(const int& color) { m_console_error_colorb_ = static_cast<DWORD>(color); }
	void set_console_optionbackground_color(const int& color) { m_console_error_colorb_ = static_cast<DWORD>(color); }
	std::wstring get_title() const { return m_title_; }
	Return_t to_return() const
	{
		return m_to_return_;
	}
protected:
	Return_t m_to_return_;
	std::wstring m_title_ = L"Menu:";
	std::wstring m_error_out_ = L"Valor incorrecto";
	std::wstring m_inicio_op_ = L"N.";
	std::wstring m_separacion_op_ = L"\t";
	DWORD m_console_title_color_ =red;
	DWORD m_console_title_colorb_ = b_black;
	DWORD m_console_error_color_ = red;
	DWORD m_console_error_colorb_ = b_black;
	DWORD m_console_option_color_ = white;
	DWORD m_console_option_colorb_ = b_black;
};



//DEPRECATED USE
template <typename Argument_t>
class menu1<Argument_t, void> : protected std::vector<std::tuple<uint8_t, std::wstring, std::function<void(Argument_t)>, Argument_t*>> {
public:
	typedef Argument_t arg;
	void add(const uint8_t number, const std::wstring string, const std::function<void(Argument_t)> function_x, Argument_t values)
	{
		this->push_back(make_tuple(number, string, function_x, values));

	}

	void pr1_nt() {
		print_ln(m_separacion_op_ + m_separacion_op_ + m_title_, static_cast<const WORD>(m_console_title_color_),
			static_cast<const WORD>(m_console_title_colorb_));
		for (auto &r : *this) {
			print_ln(m_inicio_op_ + std::to_wstring(std::get<0>(r)) + m_separacion_op_ + std::get<1>(r), static_cast<WORD>(m_console_option_color_), static_cast<WORD>(m_console_option_colorb_));
		}
	}
	void print()
	{
		while (true) {
			clear_screen();
			pr1_nt();
			auto failbool = false;
			auto string_get = get_string();
			if (string_get == L"")
			{
				continue;
			}
			for (auto &a : string_get)
			{
				if (!isdigit(a))
				{
					print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					print_ln(L"No es un numero correcto", static_cast<const WORD>(m_console_error_color_),
						static_cast<const WORD>(m_console_error_colorb_));
					wait();
					failbool = true;
				}
			}
			if (failbool)
			{
				continue;
			}
			auto selector_value = std::stoi(string_get);
			auto is_right_selector = false;
			for (auto& tupple : *this) {
				is_right_selector = false;
				if (std::get<0>(tupple) == selector_value) {
					clear_screen();
					auto function_val = std::get<2>(tupple);
					std::invoke(function_val, std::get<3>(tupple));//This is gonna make some problems in the future HOW?
					is_right_selector = true;
					break;
				}
			}
			if (!is_right_selector) {
				print_ln(m_error_out_, static_cast<const WORD>(m_console_error_color_),
					static_cast<const WORD>(m_console_error_colorb_));
				wait();
				continue;
			}
			break;
		}
	}
	void set_title(const std::wstring& text) { m_title_ = text + L":"; }
	void set_error(const std::wstring& text) { m_error_out_ = text; }
	void set_inicio_option(const std::wstring& text) { m_inicio_op_ = text; }
	void set_separator_option(const std::wstring& text) { m_separacion_op_ = text; }
	void set_console_title_color(const int& color) { m_console_title_color_ = static_cast<DWORD>(color); }
	void set_console_error_color(const int &color) { m_console_error_color_ = static_cast<DWORD>(color); }
	void set_console_option_color(const int &color) { m_console_option_color_ = static_cast<DWORD>(color); }
	void set_console_titlebackground_color(const int& color) { m_console_title_colorb_ = static_cast<DWORD>(color); }
	void set_console_errorbackground_color(const int& color) { m_console_error_colorb_ = static_cast<DWORD>(color); }
	void set_console_optionbackground_color(const int& color) { m_console_error_colorb_ = static_cast<DWORD>(color); }
	std::wstring get_title() const { return m_title_; }

protected:
	std::wstring m_title_ = L"Menu:";
	std::wstring m_error_out_ = L"Valor incorrecto";
	std::wstring m_inicio_op_ = L"N.";
	std::wstring m_separacion_op_ = L"\t";
	DWORD m_console_title_color_ = red;
	DWORD m_console_title_colorb_ = b_black;
	DWORD m_console_error_color_ = red;
	DWORD m_console_error_colorb_ = b_black;
	DWORD m_console_option_color_ = white;
	DWORD m_console_option_colorb_ = b_black;
};
*/ 
#endif //CONSOLE_MENU_HPP

