#include "String.h"
#include <conio.h>

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

String::String(const char ch)
{
	m_size = 1;
	m_capacity = m_size + 1;
	this->str = allocate();
	str[0] = ch;
	str[1] = '\0';
}

String::String(size_t num, char ch)
{
	m_size = num;
	m_capacity = m_size + 1;
	str = allocate();
	for (size_t i = 0; i < m_size; i++)
	{
		str[i] = ch;
	}
	str[m_size] = '\0';
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

void String::update(bool hide_symbols, int max_size, bool(*isAllowed)(char))
{
	char c;
	int pos = size();
	while (true)
	{
		c = _getch();
		if (c == 13)
		{
			break;
		}
		else if (c == '\b')
		{
			if (pos <= 0)
				continue;
			//printColorText("\b \b", LIGHT_GRAY, BLACK | (LIGHT_GRAY << 4));
			std::cout << "\b \b";
			m_size--;
			str[m_size] = '\0';
			pos--;
		}
		else if (pos < max_size && isAllowed(c))
		{
			std::cout << (hide_symbols ? '*' : c);
			push(c);
			pos++;
		}
	}
}

void String::getline(std::istream& in)
{
	char n_str[80];
	in.getline(n_str, 80);
	*this = n_str;
}

String String::toLower()
{
	String temp(*this);
	for (size_t i = 0; i < m_size; i++)
	{
		lowercase(temp.at(i));
	}
	return temp;
}

String String::toUpper()
{
	String temp(*this);
	for (size_t i = 0; i < m_size; i++)
	{
		uppercase(temp.at(i));
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

const char* String::find(const String& src)
{
	return strstr(str, src.str);
}

int String::compare(const String& str1, const String& str2)
{
	int i = -1;
	do
	{
		i++;
		if (str1.str[i] - str2.str[i])
		{
			return str1.str[i] - str2.str[i];
		}
	} while (i < str1.size() && i < str2.size());
	return str1.size() - str2.size();
}

int String::compare(String* const& str1, String* const& str2)
{
	return strcmp(*str1, *str2);
}

String String::random(int salt_size)
{
	String salt;
	for (int i = 0; i < salt_size; i++)
	{
		int randomChar = rand() % (26 + 26 + 10);
		if (randomChar < 26)
			salt.push('a' + randomChar);
		else if (randomChar < 26 + 26)
			salt.push('A' + randomChar - 26);
		else
			salt.push('0' + randomChar - 26 - 26);
	}
	return salt;
}

String String::toString(int num)
{
	char str[9] = "";
	_itoa_s(num, str, 10);
	return str;
}

char& String::at(size_t index)
{
	return str[index];
}

char& String::operator[](const size_t index)
{
	return str[index];
}

const char String::operator[](size_t index) const
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

String::operator char* () const
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

void uppercase(char& c)
{
	if (c >= 'a' && c <= 'z' || c >= 'à' && c <= 'ÿ')
		c -= 32;
}

void lowercase(char& c)
{
	if (c >= 'A' && c <= 'Z' || c >= 'À' && c <= 'ß')
		c += 32;
}