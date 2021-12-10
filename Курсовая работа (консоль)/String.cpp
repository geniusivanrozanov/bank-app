#include "String.h"

char* String::allocate()
{
	return new char[m_capacity];
}

char* String::reallocate()
{
	m_capacity = m_capacity * 1.5 + 1;
	char* temp_str = allocate();
	strcpy_s(temp_str, m_capacity * sizeof(char), str);
	destroy();
	return temp_str;
}

char* String::reallocate(size_t new_size)
{
	m_capacity = new_size;
	char* temp_str = allocate();
	strcpy_s(temp_str, m_capacity * sizeof(char), str);
	destroy();
	return temp_str;
}


void String::destroy()
{
	delete[] str;
}

String::String()
	: m_size(0), m_capacity(15)
{
	str = allocate();
	str[m_size] = '\0';
}

String::String(const String& src)
	: m_size(src.m_size), m_capacity(src.m_size + 1)
{
	this->str = this->allocate();
	strcpy_s(this->str, m_capacity * sizeof(char), src.str);
}

String::String(const char* src)
{
	m_size = strlen(src);
	m_capacity = m_size + 1;
	this->str = allocate();
	strcpy_s(this->str, m_capacity * sizeof(char), src);
}

String::~String()
{
	destroy();
}

size_t String::size() const
{
	return m_size;
}

size_t String::capacity() const
{
	return m_capacity;
}

void String::push(const char element)
{
	if (m_capacity <= m_size + 1)
	{
		str = reallocate();
	}
	str[m_size++] = element;
	str[m_size] = '\0';
}

String& String::operator+=(const String& src)
{
	m_size += src.m_size;
	if (m_capacity < m_size + 1)
	{
		str = reallocate(m_size + 1);
	}
	strcat_s(str, m_capacity * sizeof(char), src.str);
	return *this;
}

String& String::operator=(const String& src)
{
	m_size = src.m_size;
	m_capacity = m_size + 1;
	destroy();
	str = allocate();
	strcpy_s(str, m_capacity * sizeof(char), src.str);
	return *this;
}

const String operator+(const String& str1, const String& str2)
{
	String temp = str1;
	temp += str2;
	return temp;
}

std::istream& operator>>(std::istream& in, String& str)
{
	char temp;
	while (!(in.peek() == ' ' || in.peek() == '\t' || in.peek() == '\n' || in.eof()))
	{
		in >> temp;
		str.push(temp);
	}
	in.get();
	return in;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
	out << str.str;
	return out;
}
