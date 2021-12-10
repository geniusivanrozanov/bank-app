#pragma once
#include <cstring>

class String
{
private:
	char* str;
	size_t m_size;
	size_t m_capacity;

	char* allocate();
	char* reallocate();

	void destroy();
public:
	String();
	String(const String&);
	String(const char*);
	~String();

	size_t size() const;
	size_t capacity() const;

	void push(const char);
};

