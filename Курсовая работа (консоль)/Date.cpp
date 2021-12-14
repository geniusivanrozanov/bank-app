#include "Date.h"

const int Date::daysInMon[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

Date::Date()
	: year(0), month(0), day(0)
{
	time_t t = time(nullptr);
	std::tm tm = *std::localtime(&t);
	year = tm.tm_year + 1900;
	month = tm.tm_mon + 1;
	day = tm.tm_mday;
}

Date::Date(unsigned int year, unsigned int month, unsigned int day)
	: year(year), month(month), day(day)
{
}

unsigned int Date::getYear()
{
	return year;
}

unsigned int Date::getMonth()
{
	return month;
}

unsigned int Date::getDay()
{
	return day;
}

int Date::operator-(const Date& dt)
{
	int res = 0;
	res += day - dt.day;
	res += daysInMon[month - dt.month];
	res += (year - dt.year) + (year - dt.year) / 4;
	return res;
}

std::ostream& operator<<(std::ostream& out, const Date& dt)
{
	out << dt.day << "-" << dt.month << "-" << dt.year;
	return out;
}

std::istream& operator>>(std::istream& in, Date& dt)
{
	in >> dt.day;
	in.get();
	in >> dt.month;
	in.get();
	in >> dt.year;
	return in;
}
