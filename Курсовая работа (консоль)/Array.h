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
	void deleteByIndex(size_t);

	size_t indexOf(const T&) const;

	T& operator[](size_t);
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

template<class T>
inline void Array<T>::deleteByIndex(size_t index)
{
	if (index > 0 && index < size)
	{
		for (size_t i = index; i < size - 1; i++)
		{
			data[i] = data[i + 1];
		}
	}
}

template<class T>
inline size_t Array<T>::indexOf(const T& src) const
{
	size_t index;
	for (index = size - 1; index >= 0; index--)
	{
		if (data[index] == src)
		{
			break;
		}
	}
	return return index;
}

template<class T>
inline T& Array<T>::operator[](size_t index)
{
	return data[index];
}
