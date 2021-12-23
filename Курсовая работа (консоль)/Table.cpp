#include "Table.h"

String Table::makeRow(const Vector<String>& row) const
{
	String new_row;
	for (int i = 0; i < row.size(); i++)
	{
		new_row += '|';
		new_row += String(column_widths[i] - row[i].size(), ' ');
		new_row += row[i];
	}
	new_row += '|';
	return new_row;
}

String Table::makeDelimiter(char ch)
{
	String delimiter;
	delimiter += ' ';
	for (int i = 0; i < column_widths.size(); i++)
	{
		delimiter += String(column_widths[i], char(151));
		if (i != column_widths.size() - 1)
			delimiter += ch;
	}
	delimiter += ' ';
	return delimiter;
}

void Table::print() const
{
	std::cout << outer_delimiter << std::endl;
	std::cout << makeRow(headers) << std::endl;
	for (int i = 0; i < rows.size(); i++)
	{
		std::cout << inner_delimiter << std::endl;
		std::cout << makeRow(rows[i]) << std::endl;
	}
	std::cout << outer_delimiter << std::endl;
}

void Table::addRow(const Vector<String>& row)
{
	if (row.size() != headers.size())
		throw "Bad row!";
	rows.push(row);
	for (int i = 0; i < column_widths.size(); i++)
		if (row[i].size() > column_widths[i])
			column_widths[i] = row[i].size();
	inner_delimiter = makeDelimiter('+');
	outer_delimiter = makeDelimiter(' ');
}

Table::Table(const Vector<String>& headers)
	: headers(headers)
{
	for (int i = 0; i < headers.size(); i++)
		column_widths.push(headers[i].size());
	inner_delimiter = makeDelimiter('+');
	outer_delimiter = makeDelimiter(' ');
}

void Table::clear()
{
	rows.reserve(0);
	for (int i = 0; i < headers.size(); i++)
	{
		column_widths[i] = headers[i].size();
	}
}

int Table::size()
{
	return rows.size();
}

int Table::chooseRow() const
{
	Menu menu({}, 2, '\0', '\0');
	for (int i = 0; i < rows.size(); i++)
		menu.addOption(makeRow(rows[i]));
	COORD pos = getConsoleCursorPosition();
	print();
	moveConsoleCursor(pos.X, pos.Y + 3, 0, 0);
	return menu.chooseOption();
}
