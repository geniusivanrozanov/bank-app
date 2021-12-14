#pragma once
#pragma warning(disable : 4996)
#include <ctime>
#include <istream>

class Date
{
private:
	unsigned int year;
	unsigned int month;
	unsigned int day;
	static const int daysInMon[12];
public:
	Date();
	Date(unsigned int, unsigned int, unsigned int);
	unsigned int getYear();
	unsigned int getMonth();
	unsigned int getDay();
	int operator-(const Date&);
	friend std::ostream& operator<<(std::ostream&, const Date&);
	friend std::istream& operator>>(std::istream&, Date&);
};