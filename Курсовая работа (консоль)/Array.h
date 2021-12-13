#pragma once

template <class T>
class Array
{
private:
	T* data;
	int m_size;
	int m_capacity;

	T* allocate();
	T* reallocate();

	void destroy();
public:
	Array();
	Array(const Array&);
	~Array();

	void push(const T&);
	void deleteByIndex(int);
	void sort(int (*comp)(const T&, const T&), int, int);

	int size() const;
	int capacity() const;
	int indexOf(const T&) const;
	int indexOf(const T&, int (*comp)(const T&, const T&)) const;
	int operator()(const T&, int (*comp)(const T&, const T&)) const;

	T& at(int);
	T& operator[](int);
	const T& operator[](int) const;
};

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
	m_capacity = m_capacity + m_capacity / 2 + 1;
	if (m_capacity < 0)
	{
		m_capacity = std::numeric_limits<int>::max();
	}
	T* temp_data = allocate();
	if (data)
	{
		for (int i = 0; i < m_size; i++)
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
	for (int i = 0; i < m_size; i++)
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
inline void Array<T>::push(const T& element)
{
	if (m_capacity <= m_size)
	{
		data = reallocate();
	}
	data[m_size++] = element;
}

template<class T>
inline void Array<T>::deleteByIndex(int index)
{
	if (index > 0 && index < m_size)
	{
		for (int i = index; i < m_size - 1; i++)
		{
			data[i] = data[i + 1];
		}
		m_size--;
	}
	else
	{
		throw "Out of range";
	}
}

template<class T>
inline void Array<T>::sort(int(*comp)(const T&, const T&), int left, int right)
{
	if (left < 0 || right >= size())
	{
		throw "Out of range";
	}
	int i = left, j = right;
	T p = data[(i + j) / 2];

	while (i < j)
	{
		while (comp(data[i], p) < 0) i++;
		while (comp(data[j], p) > 0) j--;
		if (i < j)
		{
			T temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
		i++;
		j--;
	}

	if (j > left) sort(comp, left, j);
	if (i < right) sort(comp, i, right);
}

template<class T>
inline int Array<T>::size() const
{
	return m_size;
}

template<class T>
inline int Array<T>::capacity() const
{
	return m_capacity;
}

template<class T>
inline int Array<T>::indexOf(const T& src) const
{
	int index = m_size - 1;
	while (index >= 0)
	{
		if (data[index] == src)
		{
			break;
		}
		index--;
	}
	return index;
}

template<class T>
inline int Array<T>::indexOf(const T& src, int (*comp)(const T&, const T&)) const
{
	int index = m_size - 1;
	while (index >= 0)
	{
		if (!comp(data[index], src))
		{
			break;
		}
		index--;
	}
	return index;
}

template<class T>
inline int Array<T>::operator()(const T& src, int(*comp)(const T&, const T&)) const
{
	return indexOf(src, comp);
}

template<class T>
inline T& Array<T>::at(int index)
{
	if (index >= 0 && index < m_size)
	{
		return data[index];
	}
	else
	{
		throw "Out of range";
	}
}

template<class T>
inline T& Array<T>::operator[](int index)
{
	return data[index];
}

template<class T>
inline const T& Array<T>::operator[](int index) const
{
	return data[index];
}
