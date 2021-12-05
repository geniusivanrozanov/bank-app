#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>

template<class KEY, class VALUE>
class DataBase
{
private:
	std::map<KEY, VALUE> data;
	const std::string FILE_NAME;
public:
	DataBase(const std::string& file);

	void read();
	void write() const;

	template<class KEY, class VALUE>
	friend std::ostream& operator<< (std::ostream&, const DataBase<KEY, VALUE>&);
	template<class KEY, class VALUE>
	friend std::istream& operator>> (std::istream&, DataBase<KEY, VALUE>&);
};

template<class KEY, class VALUE>
inline DataBase<KEY, VALUE>::DataBase(const std::string& file)
	:FILE_NAME(file)
{
}

template<class KEY, class VALUE>
inline void DataBase<KEY, VALUE>::read()
{
	std::ifstream fin(this->FILE_NAME, std::ios::in);
	if (fin.is_open())
	{
		fin >> *this;
		fin.close();
	}
	else
	{
		std::cerr << "Empty file!\a" << std::endl;
	}
}

template<class KEY, class VALUE>
inline void DataBase<KEY, VALUE>::write() const
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

template<class KEY, class VALUE>
inline std::ostream& operator<<(std::ostream& out, const DataBase<KEY, VALUE>& db)
{
	auto it = db.data.begin();
	for (const auto last = --db.data.end(); it != last; it++)
	{
		out << it->first << " " << it->second << std::endl;
	}
	out << it->first << " " << it->second;
	return out;
}

template<class KEY, class VALUE>
inline std::istream& operator>>(std::istream& in, DataBase<KEY, VALUE>& db)
{
	KEY t_key;
	VALUE t_value;
	in.peek();
	while (!in.eof())
	{
		in >> t_key >> t_value;
		db.data.emplace(t_key, t_value);
	}
	return in;
}
