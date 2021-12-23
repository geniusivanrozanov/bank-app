#pragma once
#include "Array.h"

template<class T>
class Action
{
protected:
	T element;
	bool flag;
public:
	Action(T element, bool flag) : element(element), flag(flag) {}
	virtual void undo(Vector<T>& data) = 0;
	virtual void redo(Vector<T>& data) = 0;
	virtual ~Action() { if (flag) delete element; }
};

template<class T>
class Addition : public Action<T>
{
public:
	Addition(Vector<T>& data, T element);
	virtual void undo(Vector<T>& data) override;
	virtual void redo(Vector<T>& data) override;
};

template<class T>
class Deletion : public Action<T>
{
public:
	Deletion(Vector<T>& data, T element);
	virtual void undo(Vector<T>& data) override;
	virtual void redo(Vector<T>& data) override;
};

template<class T>
class Modification : public Action<T>
{
protected:
	T old_element;
public:
	Modification(Vector<T>& data, T old_element, T new_element);
	virtual void undo(Vector<T>& data) override;
	virtual void redo(Vector<T>& data) override;
	~Modification();
};

#pragma region

template<class T>
inline Addition<T>::Addition(Vector<T>& data, T element)
	: Action<T>(element, false)
{
	data.push(element);
}

template<class T>
inline void Addition<T>::undo(Vector<T>& data)
{
	this->flag = true;
	data.deleteByIndex(data.indexOf(this->element));
}

template<class T>
inline void Addition<T>::redo(Vector<T>& data)
{
	this->flag = false;
	data.push(this->element);
}

template<class T>
inline Deletion<T>::Deletion(Vector<T>& data, T element)
	: Action<T>(element, true)
{
	data.deleteByIndex(data.indexOf(element));
}

template<class T>
inline void Deletion<T>::undo(Vector<T>& data)
{
	this->flag = false;
	data.push(this->element);
}

template<class T>
inline void Deletion<T>::redo(Vector<T>& data)
{
	this->flag = true;
	data.deleteByIndex(data.indexOf(this->element));
}

template<class T>
inline Modification<T>::Modification(Vector<T>& data, T old_element, T new_element)
	: Action<T>(new_element, false), old_element(old_element)
{
	data.push(this->element);
	data.deleteByIndex(data.indexOf(old_element));
}

template<class T>
inline void Modification<T>::undo(Vector<T>& data)
{
	this->flag = true;
	data.deleteByIndex(data.indexOf(this->element));
	data.push(old_element);
}

template<class T>
inline void Modification<T>::redo(Vector<T>& data)
{
	this->flag = false;
	data.push(this->element);
	data.deleteByIndex(data.indexOf(old_element));
}

template<class T>
inline Modification<T>::~Modification()
{
	if (!this->flag)
	{
		delete old_element;
	}
}

#pragma endregion