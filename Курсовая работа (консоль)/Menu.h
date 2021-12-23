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
	int chooseOption(); //����� ������������ �����
	Menu(Vector<String> options = {}, int gap = 1, char choosing_char = '>', char starting_char = ' ');
	void setOptions(const Vector<String>& options) { this->options = options; }
	void addOption(const String& option) { this->options.push(option); }
	String& at(int index);
	void operator++(int);
	void operator--(int);
};

COORD getCenterdCoords(int, int); //��������� ��������� ��������������� ������
COORD getConsoleCursorPosition(); //��������� ��������� ������� �������
void printColorText(const String&, WORD = BLACK | (LIGHT_GRAY << 4), WORD = LIGHT_GRAY); //����� �������� ������
void moveConsoleCursor(const short, const short, bool = 1, bool = 1); //�����������/��������� ��������� ������� �������
bool isALoginChar(char); //�������� �� ���� �������� ��� ������
bool isAPasswordChar(char); //�������� �� ���� �������� ��� ������
bool isANameChar(char); //�������� �� ���� �������� ��� ����� � �������
bool printVerificationMessage(String, bool = 1, String = "��", String = "���"); //����� ��������� (�������������)
template <typename T> void correctInput(const char text[], T& num) //���� ���������� ������
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
			std::cout << "������������ ����!\n";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			break;
		}
	}
}
