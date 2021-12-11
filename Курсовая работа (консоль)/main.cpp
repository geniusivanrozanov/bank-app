#include <iostream>
#include <fstream>
#include <string>
#include "DataBase.h"
#include "Array.h"
#include "String.h"
#include "Stack.h"

int comp(const int& a, const int& b)
{
	return a - b;
}

int main()
{
	DataBase<String> db("temp.txt");
	db.read();
	std::cout << db << std::endl;
	db.write();
	return 0;
}