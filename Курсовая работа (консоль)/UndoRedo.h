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
	Addition(Array<T>& data, T element);
	virtual void undo(Array<T>& data) override;
	virtual void redo(Array<T>& data) override;
};

template<class T>
class Deletion : public Action<T>
{
public:
	Deletion(Array<T>& data, T element);
	virtual void undo(Array<T>& data) override;
	virtual void redo(Array<T>& data) override;
};

template<class T>
class Modification : public Deletion<T>, public Addition<T>
{
public:
	Modification(Array<T>& data, T old_element, T new_element);
	virtual void undo(Array<T>& data) override;
	virtual void redo(Array<T>& data) override;
};

template<class T>
class UndoRedo
{
private:
	Array<T>& data;
	Stack<Action<T>*> actions;
public:
	UndoRedo(Array<T>&);
	void add(T);
	void del(T);
	void change(T, T);

	void undo();
	void redo();

	bool canUndo();
	bool canRedo();
};

template<class T>
inline UndoRedo<T>::UndoRedo(Array<T>& data) : data(data)
{
}

template<class T>
inline void UndoRedo<T>::add(T element)
{
	Action<T>* temp = new Addition<T>(data, element);
	actions.push(temp);
}

template<class T>
inline void UndoRedo<T>::del(T element)
{
	Action<T>* temp = new Deletion<T>(data, element);
	actions.push(temp);
}

template<class T>
inline void UndoRedo<T>::change(T old_element, T new_element)
{
	Action<T>* temp = new Modification<T>(data, old_element, new_element);
	actions.push(temp);
}

template<class T>
inline void UndoRedo<T>::undo()
{
	if (actions.canPopDown())
	{
		actions.popDown()->undo(data);
	}
}

template<class T>
inline void UndoRedo<T>::redo()
{
	if (actions.canPopUp())
	{
		actions.popUp()->redo(data);
	}
}

template<class T>
inline bool UndoRedo<T>::canUndo()
{
	return actions.canPopDown();
}

template<class T>
inline bool UndoRedo<T>::canRedo()
{
	return actions.canPopUp();
}

#pragma region

template<class T>
inline Addition<T>::Addition(Array<T>& data, T element)
	: Action<T>(element, false)
{
	data.push(element);
}

template<class T>
inline void Addition<T>::undo(Array<T>& data)
{
	this->flag = true;
	data.deleteByIndex(data.indexOf(this->element));
}

template<class T>
inline void Addition<T>::redo(Array<T>& data)
{
	this->flag = false;
	data.push(this->element);
}

template<class T>
inline Deletion<T>::Deletion(Array<T>& data, T element)
	: Action<T>(element, true)
{
	data.deleteByIndex(data.indexOf(element));
}

template<class T>
inline void Deletion<T>::undo(Array<T>& data)
{
	this->flag = false;
	data.push(this->element);
}

template<class T>
inline void Deletion<T>::redo(Array<T>& data)
{
	this->flag = true;
	data.deleteByIndex(data.indexOf(this->element));
}

template<class T>
inline Modification<T>::Modification(Array<T>& data, T old_element, T new_element)
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

#pragma endregion