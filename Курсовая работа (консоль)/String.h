#pragma once
#include <iostream>
#include <cstring>

class String
{
private:
	char* str;
	size_t m_size;
	size_t m_capacity;

	char* allocate();
	char* reallocate();
	char* reallocate(size_t);

	void destroy();
public:
	String();
	String(const String&);
	String(const char*);
	~String();

	size_t size() const;
	size_t capacity() const;

	void push(const char);

	String& operator+=(const String&);
	String& operator=(const String&);

	friend const String operator+(const String&, const String&);
	friend std::istream& operator>>(std::istream&, String&);
	friend std::ostream& operator<<(std::ostream&, const String&);
};

