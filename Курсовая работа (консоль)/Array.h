#pragma once

template <class T>
class Array
{
private:
	T* data;
	size_t m_size;
	size_t m_capacity;

	static size_t max_size();

	T* allocate();
	T* reallocate();

	void destroy();
public:
	Array();
	Array(const Array&);
	~Array();

	static size_t max_size();
	void push(T);
	void deleteByIndex(size_t);
	void sort(int (*comp)(const T&, const T&), size_t, size_t);

	size_t size() const;
	size_t capacity() const;
	size_t indexOf(const T&) const;

	T& operator[](size_t);
};

template<class T>
inline size_t Array<T>::max_size()
{
	return std::numeric_limits<size_t>::max();
}

template<class T>
inline T* Array<T>::allocate()
{
	return new T[m_capacity];
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
	if (m_capacity * 1.5 + 1 <= max_size())
	{
		m_capacity = m_capacity * 1.5 + 1;
	}
	else
	{
		m_capacity = max_size();
	}
	T* temp_data = allocate();
	if (data)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			temp_data[i] = data[i];
		}
	}
	destroy();
	return temp_data;
}

template<class T>
inline Array<T>::Array()
	:m_size(0), m_capacity(0), data(nullptr)
{
}

template<class T>
inline Array<T>::Array(const Array& src)
	: m_size(src.m_size), m_capacity(src.m_size)
{
	this->data = this->allocate();
	for (size_t i = 0; i < m_size; i++)
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
	if (m_capacity <= m_size)
	{
		data = reallocate();
	}
	data[m_size++] = element;
}

template<class T>
inline void Array<T>::deleteByIndex(size_t index)
{
	if (index > 0 && index < m_size)
	{
		for (size_t i = index; i <m_size - 1; i++)
		{
			data[i] = data[i + 1];
		}
	}
}

template<class T>
inline void Array<T>::sort(int(*comp)(const T&, const T&), size_t left, size_t right)
{
	size_t i = left, j = right;
	T p = data[(i + j) / 2];

	while (i < j)
	{
		while (comp(data[i], p) < 0) i++;
		while (comp(data[j], p) > 0) j--;
		if (i <= j)
		{
			T temp = data[i];
			data[i] = data[j];
			data[j] = temp;
			i++;
			j--;
		}
	}

	if (j > left) sort(comp, left, j);
	if (i < right) sort(comp, i, right);
}

template<class T>
inline size_t Array<T>::size() const
{
	return m_size;
}

template<class T>
inline size_t Array<T>::capacity() const
{
	return m_capacity;
}

template<class T>
inline size_t Array<T>::indexOf(const T& src) const
{
	size_t index;
	for (index = m_size- 1; index >= 0; index--)
	{
		if (data[index] == src)
		{
			break;
		}
	}
	return index;
}

template<class T>
inline T& Array<T>::operator[](size_t index)
{
	return data[index];
}
