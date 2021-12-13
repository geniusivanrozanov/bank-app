#include "String.h"

char* String::allocate()
{
	return new char[m_capacity];
}

char* String::reallocate()
{
	m_capacity = m_capacity + m_capacity / 2 + 1;
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

String String::toLower()
{
	String temp;
	for (size_t i = 0; i < m_size; i++)
	{
		temp += tolower(str[i]);
	}
	return temp;
}

String String::toUpper()
{
	String temp;
	for (size_t i = 0; i < m_size; i++)
	{
		temp += toupper(str[i]);
	}
	return temp;
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

String& String::operator+=(const char ch)
{
	push(ch);
	return *this;
}

String& String::operator=(const String& src)
{
	if (this == &src)
	{
		return *this;
	}
	m_size = src.m_size;
	m_capacity = m_size + 1;
	destroy();
	str = allocate();
	strcpy_s(str, m_capacity * sizeof(char), src.str);
	return *this;
}

int String::compare(const String& str1, const String& str2)
{
	return strcmp(str1, str2);
}

int String::compare(String* const& str1, String* const& str2)
{
	return strcmp(*str1, *str2);
}

char& String::operator[](size_t index)
{
	return str[index];
}

char String::operator[](size_t index) const
{
	return str[index];
}

bool String::operator==(const String& src)
{
	return !compare(str, src.str);
}

bool String::operator==(const char* src)
{
	return !compare(str, src);
}

String::operator const char* () const
{
	return str;
}

const String operator+(const String& str1, const String& str2)
{
	String temp = str1;
	temp += str2;
	return temp;
}

std::istream& operator>>(std::istream& in, String& str)
{
	if (str.m_size)
	{
		str.m_size = 0;
	}
	char temp;
	while (in.peek() == ' ' || in.peek() == '\t' || in.peek() == '\n' || in.eof())
	{
		in.get();
	}
	while (!(in.peek() == ' ' || in.peek() == '\t' || in.peek() == '\n' || in.eof()))
	{
		in >> temp;
		str.push(temp);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
	out << str.str;
	return out;
}
