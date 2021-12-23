#pragma once
#include <initializer_list>

template <class T>
class Vector
{
private:
	T* data;
	int m_size;
	int m_capacity;

	T* allocate();

	void destroy();
public:
	Vector();
	Vector(const Vector&);
	Vector(const std::initializer_list<T>&);
	~Vector();

	void push(const T&);
	void deleteByIndex(int);
	void sort(int (*comp)(const T&, const T&), int, int);
	void reserve(int);
	void reverse();

	int size() const;
	int capacity() const;
	int indexOf(const T&) const;
	int indexOf(const T&, int (*comp)(const T&, const T&)) const;
	int operator()(const T&, int (*comp)(const T&, const T&)) const;

	T& at(int);
	T& operator[](int);
	const T& operator[](int) const;
	Vector<T>& operator=(const Vector<T>&);
};

template<class T>
inline T* Vector<T>::allocate()
{
	return new T[m_capacity];
}

template<class T>
inline void Vector<T>::destroy()
{
	if (data)
	{
		delete[] data;
	}
}

template<class T>
inline Vector<T>::Vector()
	:m_size(0), m_capacity(0), data(nullptr)
{
}

template<class T>
inline Vector<T>::Vector(const Vector& src)
	: m_size(src.m_size), m_capacity(src.m_size)
{
	this->data = this->allocate();
	for (int i = 0; i < m_size; i++)
	{
		this->data[i] = src.data[i];
	}
}

template<class T>
Vector<T>::Vector(const std::initializer_list<T>& list)
{
	m_size = list.size();
	m_capacity = m_size;
	data = allocate();
	int i = 0;
	for (auto& element : list)
	{
		data[i++] = element;
	}
}

template<class T>
inline Vector<T>::~Vector()
{
	destroy();
}

template<class T>
inline void Vector<T>::push(const T& element)
{
	if (m_capacity <= m_size)
	{
		reserve(m_capacity + m_capacity / 2 + 1);
	}
	data[m_size++] = element;
}

template<class T>
inline void Vector<T>::deleteByIndex(int index)
{
	if (index >= 0 && index < m_size)
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
inline void Vector<T>::sort(int(*comp)(const T&, const T&), int left, int right)
{
	if (m_size <= 0) return;
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
inline void Vector<T>::reserve(int new_capacity)
{
	if (new_capacity < 0)
		throw "Bad capacity";
	if (new_capacity < m_size)
	{
		m_size = new_capacity;
	}
	else if (new_capacity > 0)
	{
		m_capacity = new_capacity;
		T* temp_data = allocate();
		if (data)
		{
			for (int i = 0; i < m_size; i++)
			{
				temp_data[i] = data[i];
			}
		}
		destroy();
		data = temp_data;
	}
}

template<class T>
inline void Vector<T>::reverse()
{
	int i = 0;
	int j = m_size - 1;
	while (i < j)
	{
		T temp = data[i];
		data[i] = data[j];
		data[j] = temp;
		i++;
		j--;
	}
}

template<class T>
inline int Vector<T>::size() const
{
	return m_size;
}

template<class T>
inline int Vector<T>::capacity() const
{
	return m_capacity;
}

template<class T>
inline int Vector<T>::indexOf(const T& src) const
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
inline int Vector<T>::indexOf(const T& src, int (*comp)(const T&, const T&)) const
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
inline int Vector<T>::operator()(const T& src, int(*comp)(const T&, const T&)) const
{
	return indexOf(src, comp);
}

template<class T>
inline T& Vector<T>::at(int index)
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
inline T& Vector<T>::operator[](int index)
{
	return data[index];
}

template<class T>
inline const T& Vector<T>::operator[](int index) const
{
	return data[index];
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& src)
{
	destroy();
	m_size = src.m_size;
	m_capacity = src.m_size;
	data = allocate();
	for (int i = 0; i < src.m_size; i++)
	{
		data[i] = src.data[i];
	}
	return *this;
}
