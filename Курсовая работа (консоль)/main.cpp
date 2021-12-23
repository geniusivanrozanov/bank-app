#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "Form.h"
#include "DataBase.h"
#include "Array.h"
#include "String.h"
#include "Stack.h"
#include "Account.h"
#include "Identifier.h"
#include "Date.h"
#include "Menu.h"
#include "Table.h"

DataBase<Account> accounts("files/accounts.txt");
DataBase<BankAccount> bank_accounts("files/bank_accounts.txt");

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, 0);
	accounts.read();
	bank_accounts.read();
	MainForm form;
	form.init();
	accounts.write();
	bank_accounts.write();
	return 0;
}