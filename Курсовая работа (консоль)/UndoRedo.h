#pragma once
#include "Stack.h"
#include "Array.h"

template<class T>
class Action
{
public:
	T element;
	bool flag;
	Action(T element, bool flag) : element(element), flag(flag) {}
	virtual void undo(Array<T>& data) = 0;
	virtual void redo(Array<T>& data) = 0;
	virtual ~Action() { if (flag) delete element; }
};

template<class T>
class Addition : public Action<T>
{
public:
	Addition(Array<T>& data, const T& element);
	virtual void undo(Array<T>& data) override;
	virtual void redo(Array<T>& data) override;
};

template<class T>
class Deletion : public Action<T>
{
public:
	Deletion(Array<T>& data, const T& element);
	virtual void undo(Array<T>& data) override;
	virtual void redo(Array<T>& data) override;
};

template<class T>
class Modification : public Deletion<T>, public Addition<T>
{
public:
	Modification(Array<T>& data, const T& old_element, const T& new_element);
	virtual void undo(Array<T>& data) override;
	virtual void redo(Array<T>& data) override;
};

template<class T>
inline Addition<T>::Addition(Array<T>& data, const T& element)
	: Action<T>(element, false)
{
	data.push(element);
}

template<class T>
inline void Addition<T>::undo(Array<T>& data)
{
	flag = true;
	data.deleteByIndex(data.indexOf(element));
}

template<class T>
inline void Addition<T>::redo(Array<T>& data)
{
	flag = false;
	data.push(element);
}

template<class T>
inline Deletion<T>::Deletion(Array<T>& data, const T& element)
	: Action<T>(element, true)
{
	data.deleteByIndex(data.indexOf(element));
}

template<class T>
inline void Deletion<T>::undo(Array<T>& data)
{
	flag = false;
	data.push(element);
}

template<class T>
inline void Deletion<T>::redo(Array<T>& data)
{
	flag = true;
	data.deleteByIndex(data.indexOf(element));
}

template<class T>
inline Modification<T>::Modification(Array<T>& data, const T& old_element, const T& new_element)
	: Deletion<T>(data, old_element), Addition<T>(data, new_element)
{
}

template<class T>
inline void Modification<T>::undo(Array<T>& data)
{
	Deletion<T>::undo(data);
	Addition<T>::undo(data);
}

template<class T>
inline void Modification<T>::redo(Array<T>& data)
{
	Deletion<T>::redo(data);
	Addition<T>::redo(data);
}
