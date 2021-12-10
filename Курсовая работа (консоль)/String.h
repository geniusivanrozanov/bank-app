#pragma once
#include <cstring>

class String
{
private:
	char* str;
	size_t m_size;
	size_t m_capacity;

	char* allocate();

public:
	String();
	String(const String&);
	String(const char*);
};

