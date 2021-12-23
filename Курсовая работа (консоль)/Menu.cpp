#include "Menu.h"

Menu::Menu(Vector<String> options, int gap, char choosing_char, char starting_char)
	: gap(gap), choosing_char(choosing_char), starting_char(starting_char),
	curr_option(0), options(options)
{

}


int Menu::chooseOption()
{
	COORD start_pos = getConsoleCursorPosition();
	int number_of_options = options.size();


	for (int i = 0; i < number_of_options; i++)
	{
		std::cout << starting_char << options.at(i);
		moveConsoleCursor(start_pos.X, gap, 0, 1);
	}

	moveConsoleCursor(start_pos.X, start_pos.Y + curr_option * gap, 0, 0);
	printColorText(String(choosing_char) + options.at(curr_option), BLACK | (LIGHT_GRAY << 4));

	while (true)
	{
		char c = _getch();
		if (c == 13)
		{
			break;
		}
		else if (c == -32 || c == 0)
		{
			c = _getch();
			moveConsoleCursor(start_pos.X, start_pos.Y + curr_option * gap, 0, 0);
			std::cout << starting_char << options.at(curr_option);
			if (c == 80) //Стрелка вниз
				(*this)++;
			else if (c == 72) //Стрелка вверх
				(*this)--;
			moveConsoleCursor(start_pos.X, start_pos.Y + curr_option * gap, 0, 0);
			printColorText(String(choosing_char) + options.at(curr_option), BLACK | (LIGHT_GRAY << 4));
		}
	}
	return curr_option;
}


String& Menu::at(int index)
{
	return options.at(index);
}

void Menu::operator++(int)
{
	(curr_option < options.size() - 1) ? (curr_option++) : (curr_option = 0);
}

void Menu::operator--(int)
{
	(curr_option > 0) ? (curr_option--) : (curr_option = options.size() - 1);
}

bool isAPasswordChar(char c)
{
	if (c < 0)
	{
		c = _getch();
		return false;
	}
	return (isalnum(c) || strchr("!@#$%&-_", c));
}

bool isALoginChar(char c)
{
	if (c < 0)
	{
		c = _getch();
		return false;
	}
	return (isalnum(c) || strchr("@#$&_", c));
}

bool isANameChar(char c)
{
	return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= 'а' && c <= 'я' || c >= 'А' && c <= 'Я' || c == '-');
}

COORD getConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition;
}

COORD getCenterdCoords(int line_length, int number_of_lines)
{
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsole, &screen_buffer_info);
	COORD pos = screen_buffer_info.dwMaximumWindowSize;
	pos.X = (pos.X - line_length) / 2;
	pos.Y = (pos.Y - number_of_lines) / 2;
	return pos;
}

void moveConsoleCursor(const short x, const short y, bool move_or_set_x, bool move_or_set_y)
{
	COORD pos = getConsoleCursorPosition();
	pos.X = (move_or_set_x ? pos.X + x : x);
	pos.Y = (move_or_set_y ? pos.Y + y : y);
	SetConsoleCursorPosition(hConsole, pos);
}

void printColorText(const String& text, WORD color, WORD next_color)
{
	SetConsoleTextAttribute(hConsole, color);
	std::cout << text;
	SetConsoleTextAttribute(hConsole, next_color);
}

bool printVerificationMessage(String question, bool answer_need, String answer_true, String answer_false)
{
	system("cls");
	COORD pos = getCenterdCoords(question.size(), 2);
	short pos_X_true = pos.X + (question.size() - answer_true.size());
	short pos_X_false = pos.X;

	SetConsoleCursorPosition(hConsole, { pos.X, pos.Y });
	std::cout << question;
	if (!answer_need)
	{
		char c = _getch();
		return true;
	}
	Menu menu({answer_true, answer_false});
	return !menu.chooseOption();
}
