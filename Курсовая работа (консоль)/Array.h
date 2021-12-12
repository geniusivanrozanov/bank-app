#pragma once

template <class T>
class Array
{
private:
	T* data;
	int m_size;
	int m_capacity;

	static int max_size();

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

	T* operator()(const T&, int (*comp)(const T&, const T&));
	T* find(const T&, int (*comp)(const T&, const T&));

	T& operator[](int);
	const T& operator[](int) const;
};

template<class T>
inline int Array<T>::max_size()
{
	return std::numeric_limits<int>::max();
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
	}
}

template<class T>
inline void Array<T>::sort(int(*comp)(const T&, const T&), int left, int right)
{
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
inline T* Array<T>::operator()(const T& src, int(*comp)(const T&, const T&))
{
	return find(src, comp);
}

template<class T>
inline T* Array<T>::find(const T& src, int(*comp)(const T&, const T&))
{
	int index = m_size - 1;
	while (index >= 0)
	{
		if (comp(data[index], src) == 0)
		{
			break;
		}
		index--;
	}
	return (index >= 0 ? data + index : nullptr);
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
