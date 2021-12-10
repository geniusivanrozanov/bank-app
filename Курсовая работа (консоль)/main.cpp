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
	Stack<int> a;
	for (size_t i = 0; i < 10; i++)
	{
		a.push(i + 1);
	}
	a.popDown();
	a.popDown();
	a.popDown();
	a.push(777);
	a.print();
	return 0;
}