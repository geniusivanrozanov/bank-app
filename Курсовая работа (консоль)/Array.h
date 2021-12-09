#pragma once

template <class T>
class Array
{
private:
	T* data;
	size_t size;
	size_t capacity;

	T* allocate();
public:
	Array();
	Array(const Array&);
};

template<class T>
inline T* Array<T>::allocate()
{
	return new T[capacity];
}

template<class T>
inline Array<T>::Array()
	: size(0), capacity(0), data(nullptr)
{
}

template<class T>
inline Array<T>::Array(const Array& src)
{
	this->size = src.size;
	this->capacity = src.size;
	this->allocate();
	for (size_t i = 0; i < size; i++)
	{
		this->data[i] = src.data();
	}
}
