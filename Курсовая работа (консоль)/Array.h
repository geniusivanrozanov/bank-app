#pragma once

template <class T>
class Array
{
private:
	T* data;
	size_t size;
	size_t capacity;

	T* allocate();
	T* reallocate();

	void destroy();
public:
	Array();
	Array(const Array&);
	~Array();

	void push(T);
};

template<class T>
inline T* Array<T>::allocate()
{
	return new T[capacity];
}

template<class T>
inline void Array<T>::destroy()
{
	if (data)
	{
		delete[] data;
	}
}

template<class T>
inline T* Array<T>::reallocate()
{
	T* temp_data = allocate();
	if (data)
	{
		for (size_t i = 0; i < size; i++)
		{
			temp_data[i] = data[i];
		}
	}
	destroy();
	return temp_data;
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
	this->data = this->allocate();
	for (size_t i = 0; i < size; i++)
	{
		this->data[i] = src.data();
	}
}

template<class T>
inline Array<T>::~Array()
{
	destroy();
}

template<class T>
inline void Array<T>::push(T element)
{
	size++;
	if (capacity < size)
	{
		capacity = size * 1.5;
		data = reallocate();
	}
	data[size - 1] = element;
}
