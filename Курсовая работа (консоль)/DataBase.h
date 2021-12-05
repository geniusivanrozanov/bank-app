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
};

template<class KEY, class VALUE>
inline DataBase<KEY, VALUE>::DataBase(const std::string& file)
	:FILE_NAME(file)
{
}

template<class KEY, class VALUE>
inline void DataBase<KEY, VALUE>::read()
{
	KEY t_key;
	VALUE t_value;
	std::ifstream fin(this->FILE_NAME, std::ios::in);
	if (fin.is_open())
	{
		fin.peek();
		while (!fin.eof())
		{
			fin >> t_key >> t_value;
			data.emplace(t_key, t_value);
		}
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
		auto it = data.begin();
		for (const auto last = --data.end(); it != last; it++)
		{
			fout << it->first << " " << it->second << std::endl;
		}
		fout << it->first << " " << it->second;
		fout.close();
	}
	else
	{
		std::cerr << "Failed to save file!\a" << std::endl;
	}
}
