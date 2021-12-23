#pragma once
#define NOMINMAX
#include <windows.h>
#include <conio.h>
#include "String.h"
#include "Array.h"

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum Colors {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_CYAN,
	DARK_RED,
	DARK_MAGENTA,
	DARK_YELLOW,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	LIGHT_YELLOW,
	WHITE
};

class Menu
{
private:
	int curr_option;
	int gap;
	char choosing_char;
	char starting_char;

	Vector<String> options;
public:
	int chooseOption(); //Выбор предлагаемой опции
	Menu(Vector<String> options = {}, int gap = 1, char choosing_char = '>', char starting_char = ' ');
	void setOptions(const Vector<String>& options) { this->options = options; }
	void addOption(const String& option) { this->options.push(option); }
	String& at(int index);
	void operator++(int);
	void operator--(int);
};

COORD getCenterdCoords(int, int); //Получение координат отцентрованного текста
COORD getConsoleCursorPosition(); //Получение координат каретки консоли
void printColorText(const String&, WORD = BLACK | (LIGHT_GRAY << 4), WORD = LIGHT_GRAY); //Выбод цветного текста
void moveConsoleCursor(const short, const short, bool = 1, bool = 1); //Перемещение/установка координат каретки консоли
bool isALoginChar(char); //Проверка на ввод символов для логина
bool isAPasswordChar(char); //Проверка на ввод символов для пароля
bool isANameChar(char); //Проверка на ввод символов для имени и фамилии
bool printVerificationMessage(String, bool = 1, String = "Да", String = "Нет"); //Вывод сообщения (подтверждения)
template <typename T> void correctInput(const char text[], T& num) //Ввод корректных данных
{
	T temp = num;
	while (true)
	{
		std::cout << text;
		std::cin >> temp;
		if (std::cin.get() == '\n')
		{
			num = temp;
			break;
		}
		else
		{
			std::cout << "Некорректный ввод!\n";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			break;
		}
	}
}
