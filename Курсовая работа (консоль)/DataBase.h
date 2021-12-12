#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "String.h"
#include "Array.h"

template<class T>
class DataBase
{
private:
	Array<T> data;
	const String FILE_NAME;
public:
	DataBase(const String& file);

	void read();
	void write() const;

	T* find(const T& src, int(*comp)(const T&, const T&));
	
	T& operator[](size_t);
	template<class T>
	friend std::ostream& operator<< (std::ostream&, const DataBase<T>&);
	template<class T>
	friend std::istream& operator>> (std::istream&, DataBase<T>&);
};

template<class T>
inline DataBase<T>::DataBase(const String& file)
	: FILE_NAME(file)
{
}

template<class T>
inline void DataBase<T>::read()
{
	std::ifstream fin(this->FILE_NAME, std::ios::in);
	if (fin.is_open())
	{
		fin >> *this;
		fin.close();
	}
	else
	{
		std::cerr << "Failed to open file!\a" << std::endl;
	}
}

template<class T>
inline void DataBase<T>::write() const
{
	std::ofstream fout(this->FILE_NAME, std::ios::out);
	if (fout.is_open())
	{
		fout << *this;
		fout.close();
	}
	else
	{
		std::cerr << "Failed to save file!\a" << std::endl;
	}
}

template<class T>
inline T* DataBase<T>::find(const T& src, int(*comp)(const T&, const T&))
{
	return data.find(src, comp);
}

template<class T>
inline T& DataBase<T>::operator[](size_t index)
{
	return data[index];
}

template<class T>
inline std::ostream& operator<<(std::ostream& out, const DataBase<T>& db)
{
	size_t i;
	if (db.data.size())
	{
		for (i = 0; i < db.data.size() - 1; i++)
		{
			out << db.data[i] << std::endl;
		}
		out << db.data[i];
	}
	return out;
}

template<class T>
inline std::istream& operator>>(std::istream& in, DataBase<T>& db)
{
	T element;
	in.peek();
	while (!in.eof())
	{
		in >> element;
		db.data.push(element);
	}
	return in;
}
