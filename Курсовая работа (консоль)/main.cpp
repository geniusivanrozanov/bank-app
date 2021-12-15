#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "DataBase.h"
#include "Array.h"
#include "String.h"
#include "Stack.h"
#include "Account.h"
#include "Identifier.h"
#include "Date.h"

int comp(const int& a, const int& b)
{
	return a - b;
}

int main()
{
	Date t, tt;
	std::cin >> tt;
	std::cout << int(t - tt) << std::endl;
	/*DataBase<Account> accounts("files/accounts.txt");
	accounts.read();
	std::cout << Identifier<Account>::getFreeId() << std::endl;
	std::cout << Identifier<Account>::getFreeId() << std::endl;
	std::cout << Identifier<Account>::getFreeId() << std::endl;
	std::cout << Identifier<Account>::getFreeId() << std::endl;
	accounts.write();*/
	/*DataBase<String> t("temp.txt");
	t.read();*/
	//std::cout << BANK << std::endl;
	return 0;
}