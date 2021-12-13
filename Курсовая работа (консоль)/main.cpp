#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "DataBase.h"
#include "Array.h"
#include "String.h"
#include "Stack.h"

int comp(const int& a, const int& b)
{
	return a - b;
}

String generateSalt(int salt_size)
{
	String salt;
	//salt.reserve(salt_size);
	for (int i = 0; i < salt_size; i++)
	{
		int randomChar = rand() % (26 + 26 + 10);
		if (randomChar < 26)
			salt.push('a' + randomChar);
		else if (randomChar < 26 + 26)
			salt.push('A' + randomChar - 26);
		else
			salt.push('0' + randomChar - 26 - 26);
	}
	return salt;
}

int main()
{
	DataBase<String> db("temp.txt");
	//db.read();
	for (size_t i = 0; i < 3; i++)
	{
		db.add(new String(generateSalt(5)));
	}
	std::cout << db << std::endl << std::endl;


	db.undo();
	std::cout << db << std::endl << std::endl;

	db.undo();
	std::cout << db << std::endl << std::endl;

	db.undo();
	std::cout << db << std::endl << std::endl;

	db.undo();
	std::cout << db << std::endl << std::endl;

	db.redo();
	std::cout << db << std::endl << std::endl;

	db.redo();
	std::cout << db << std::endl << std::endl;
	return 0;
}