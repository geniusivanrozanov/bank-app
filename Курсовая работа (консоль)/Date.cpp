#include "Date.h"

const int Date::daysInMon[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 30 };

Date::Date()
	: year(0), month(0), day(0)
{
	time_t t = time(nullptr);
	std::tm tm = *std::localtime(&t);
	year = tm.tm_year + 1900;
	month = tm.tm_mon + 1;
	day = tm.tm_mday;
}

Date::Date(int year, int month, int day)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

int Date::getYear()
{
	return year;
}

int Date::getMonth()
{
	return month;
}

int Date::getDay()
{
	return day;
}

Date Date::operator-(const Date& dt)
{
	return Date(year - dt.year, month - dt.month, day - dt.day);
}

Date::operator int()
{
	int res = 0;
	res += day + year * 365 + year / 4;
	for (int i = 0; i < month; i++) res += daysInMon[i];
	return res;
}

String Date::toString() const
{
	String date;
	date += String::toString(day);
	date += "-";
	date += String::toString(month);
	date += "-";
	date += String::toString(year);
	return date;
}

Date Date::operator+(const Date& dt)
{
	return Date(year + dt.year, month + dt.month, day + dt.day);
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
