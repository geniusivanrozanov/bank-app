#pragma once
#include "Array.h"
#include "String.h"
#include "Menu.h"
#include <iostream>
class Table
{
private:
	const Vector<String> headers;
	Vector<Vector<String>> rows;
	Vector<int> column_widths;
	String outer_delimiter;
	String inner_delimiter;
	String makeRow(const Vector<String>&) const;
	String makeDelimiter(char);
public:
		Table(const Vector<String>& headers);
		void print() const;
		void addRow(const Vector<String>&);
		void clear();
		int chooseRow() const;
		int size();
};

