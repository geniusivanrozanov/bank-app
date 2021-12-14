#pragma once

template<class T>
class Identifier
{
private:
	static int id;
public:
	static void setMaxId(int);
	static int getFreeId();
};

template<class T>
int Identifier<T>::id = 0;

template<class T>
void Identifier<T>::setMaxId(int new_id)
{
	id = new_id + 1;
}

template<class T>
int Identifier<T>::getFreeId()
{
	return id++;
}
