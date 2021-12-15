#pragma once
#pragma warning(disable : 4996)
#include <ctime>
#include <istream>

class Date
{
private:
	int year;
	int month;
	int day;
	static const int daysInMon[12];
public:
	Date();
	Date(int, int, int);
	int getYear();
	int getMonth();
	int getDay();
	Date operator-(const Date&);
	Date operator+(const Date&);
	operator int();
	friend std::ostream& operator<<(std::ostream&, const Date&);
	friend std::istream& operator>>(std::istream&, Date&);
};