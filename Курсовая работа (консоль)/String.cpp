#include "String.h"

char* String::allocate()
{
	return new char[m_capacity];
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
