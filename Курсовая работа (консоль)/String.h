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
	String(const char);
	String(size_t, char);
	~String();

	size_t size() const;
	size_t capacity() const;

	void push(const char);
	void update(bool hide_symbols, int max_size, bool(*isAllowed)(char));
	void getline(std::istream& in);

	String toLower();
	String toUpper();

	String& operator+=(const String&);
	String& operator+=(const char);
	String& operator=(const String&);

	const char* find(const String&);
	static int compare(const String&, const String&);
	static int compare(String *const&, String* const&);
	static String random(int);
	static String toString(int);

	char& at(size_t);
	char& operator[](const size_t);
	const char operator[](size_t) const;

	bool operator==(const String&);
	bool operator==(const char*);

	friend const String operator+(const String&, const String&);
	friend std::istream& operator>>(std::istream&, String&);
	friend std::ostream& operator<<(std::ostream&, const String&);

	operator const char* () const;
	operator char* () const;
};

void uppercase(char&);
void lowercase(char&);