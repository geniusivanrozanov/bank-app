#pragma once
#include <iostream>
#include <fstream>
#include "String.h"
#include "Array.h"
#include "UndoRedo.h"
#include "Account.h"
#include "Admin.h"
#include "Client.h"
#include "BankAccount.h"
#include "Deposit.h"
#include "Identifier.h"

template<class T>
class DataBase
{
private:
	Vector<T*> data;
	UndoRedo<T*> undoredo;
	const String FILE_NAME;
public:
	DataBase(const String& file);
	~DataBase();

	void read();
	void write() const;
	void sort(int(*comp)(T* const&, T* const&));
	void push(T*);
	void add(T*);
	void del(T*);
	void change(T*, T*);
	void undo();
	void redo();
	void reverse();

	void clearUndoRedo();

	bool canUndo();
	bool canRedo();

	int indexOf(T* const&, int(*comp)(T* const&, T* const&)) const;
	int size() const;
	template<class U>
	int indexOfByPatameter(const U&, int(*comp)(T* const&, const U&)) const;

	T* at(int);

	Vector<T*> findAll(T* const&, int(*comp)(T* const&, T* const&)) const;

	template<class T>
	friend std::ostream& operator<< (std::ostream&, const DataBase<T>&);
	template<class T>
	friend std::istream& operator>> (std::istream&, DataBase<T>&);
};

extern DataBase<Account> accounts;
extern DataBase<BankAccount> bank_accounts;

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
inline void DataBase<T>::push(T* element)
{
	data.push(element);
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
inline bool DataBase<T>::canUndo()
{
	return undoredo.canUndo();
}

template<class T>
inline bool DataBase<T>::canRedo()
{
	return undoredo.canRedo();
}

template<class T>
inline void DataBase<T>::clearUndoRedo()
{
	undoredo.clear();
}

template<class T>
inline void DataBase<T>::reverse()
{
	data.reverse();
}

template<class T>
inline int DataBase<T>::indexOf(T* const& src, int(*comp)(T* const&, T* const&)) const
{
	return data.indexOf(src, comp);
}

template<class T>
template<class U>
inline int DataBase<T>::indexOfByPatameter(const U& parameter, int(*comp)(T* const&, const U&)) const
{
	int index = data.size() - 1;
	while (index >= 0)
	{
		if (!comp(data[index], parameter))
		{
			break;
		}
		index--;
	}
	return index;
}

template<class T>
inline Vector<T*> DataBase<T>::findAll(T* const& src, int(*comp)(T* const&, T* const&)) const
{
	Vector<T*> res;
	int index = data.indexOf(src, comp);
	while (index >= 0)
	{
		if (!comp(src, data.at(index)))
		{
			res.push(data.data(index));
		}
		index--;
	}
	return res;
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

template<>
inline std::istream& operator>>(std::istream& in, DataBase<Account>& db)
{
	Account* element;
	in.peek();
	while (!in.eof())
	{
		int st;
		in >> st;
		if (st == Account::ADMIN)
			element = new Admin();
		else
			element = new Client(static_cast<Account::Status>(st));
		in >> *element;
		db.data.push(element);
	}
	if (db.size() > 0)
	{
		db.sort(Account::compareId);
		Identifier<Account>::setMaxId(db.at(db.size() - 1)->getId());
	}
	else
	{
		element = new Admin();
		element->setLogin("admin");
		element->setPassword("admin");
		element->setSurname("Админов");
		element->setName("Админ");
		element->setPatronymic("Админович");
		db.data.push(element);
	}
	return in;
}

template<>
inline std::istream& operator>>(std::istream& in, DataBase<BankAccount>& db)
{
	in.peek();
	while (!in.eof())
	{
		BankAccount* element;
		int type;
		in >> type;
		if (type == 0)
			element = new BankAccount;
		else
			element = new DepLoan(type);
		in >> *element;
		db.data.push(element);
	}
	if (db.size() > 0)
	{
		db.sort(BankAccount::compareId);
		Identifier<BankAccount>::setMaxId(db.at(db.size() - 1)->getId());
	}
	return in;
}