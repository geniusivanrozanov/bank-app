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

	String toLower();
	String toUpper();

	String& operator+=(const String&);
	String& operator+=(const char);
	String& operator=(const String&);

	static int compare(const String&, const String&);

	bool operator==(const String&);
	bool operator==(const char*);

	friend const String operator+(const String&, const String&);
	friend std::istream& operator>>(std::istream&, String&);
	friend std::ostream& operator<<(std::ostream&, const String&);

	operator const char* () const;
};

