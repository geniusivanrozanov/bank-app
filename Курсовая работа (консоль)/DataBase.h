#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "String.h"
#include "Array.h"
#include "UndoRedo.h"

template<class T>
class DataBase
{
private:
	Array<T*> data;
	UndoRedo<T*> undoredo;
	const String FILE_NAME;
public:
	DataBase(const String& file);
	~DataBase();

	void read();
	void write() const;
	void sort(int(*comp)(T *const &, T* const&));
	void add(T*);
	void del(T*);
	void change(T*, T*);
	void undo();
	void redo();

	int indexOf(T* const&, int(*comp)(T* const&, T* const&)) const;
	int size() const;

	T* at(int);

	template<class T>
	friend std::ostream& operator<< (std::ostream&, const DataBase<T>&);
	template<class T>
	friend std::istream& operator>> (std::istream&, DataBase<T>&);
};

template<class T>
inline DataBase<T>::DataBase(const String& file)
	: FILE_NAME(file), undoredo(data)
{
}

template<class T>
inline DataBase<T>::~DataBase()
{
	for (int i = 0; i < data.size(); i++)
	{
		delete data[i];
	}
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
		throw "Failed to open file!";
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
		throw "Failed to save file!";
	}
}

template<class T>
inline void DataBase<T>::sort(int(*comp)(T* const&, T* const&))
{
	data.sort(comp, 0, data.size() - 1);
}

template<class T>
inline void DataBase<T>::add(T* element)
{
	undoredo.add(element);
}

template<class T>
inline void DataBase<T>::del(T* element)
{
	undoredo.del(element);
}

template<class T>
inline void DataBase<T>::change(T* old_element, T* new_element)
{
	undoredo.change(old_element, new_element);
}

template<class T>
inline void DataBase<T>::undo()
{
	undoredo.undo();
}

template<class T>
inline void DataBase<T>::redo()
{
	undoredo.redo();
}

template<class T>
inline int DataBase<T>::indexOf(T* const& src, int(*comp)(T* const&, T* const&)) const
{
	return data.indexOf(src, comp);
}

template<class T>
inline int DataBase<T>::size() const
{
	return data.size();
}

template<class T>
inline T* DataBase<T>::at(int index)
{
	return data.at(index);
}

template<class T>
inline std::ostream& operator<<(std::ostream& out, const DataBase<T>& db)
{
	if (db.data.size())
	{
		int i;
		for (i = 0; i < db.data.size() - 1; i++)
		{
			out << *db.data[i] << std::endl;
		}
		out << *db.data[i];
	}
	return out;
}

template<class T>
inline std::istream& operator>>(std::istream& in, DataBase<T>& db)
{
	in.peek();
	while (!in.eof())
	{
		T* element = new T;
		in >> *element;
		db.data.push(element);
	}
	return in;
}

