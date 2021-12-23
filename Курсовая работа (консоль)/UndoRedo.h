#pragma once
#include "Actions.h"
#include "Array.h"

template<class T>
class UndoRedo
{
private:
	Vector<T>& data;
	Vector<Action<T>*> actions;
	int head;
	void destroyArray(int, int);
public:
	UndoRedo(Vector<T>&);
	~UndoRedo();

	void add(T);
	void del(T);
	void change(T, T);

	void undo();
	void redo();

	void clear();

	bool canUndo();
	bool canRedo();
};

template<class T>
inline void UndoRedo<T>::destroyArray(int begin, int end)
{
	for (int i = end - 1; i >= begin; i--)
	{
		delete actions[i];
		actions.deleteByIndex(i);
	}
}

template<class T>
inline UndoRedo<T>::UndoRedo(Vector<T>& data) 
	: data(data), head(-1)
{
}

template<class T>
inline UndoRedo<T>::~UndoRedo()
{
	clear();
}

template<class T>
inline void UndoRedo<T>::add(T element)
{
	destroyArray(++head, actions.size());
	Action<T>* temp = new Addition<T>(data, element);
	actions.push(temp);
}

template<class T>
inline void UndoRedo<T>::del(T element)
{
	destroyArray(++head, actions.size());
	Action<T>* temp = new Deletion<T>(data, element);
	actions.push(temp);
}

template<class T>
inline void UndoRedo<T>::change(T old_element, T new_element)
{
	destroyArray(++head, actions.size());
	Action<T>* temp = new Modification<T>(data, old_element, new_element);
	actions.push(temp);
}

template<class T>
inline void UndoRedo<T>::undo()
{
	if (canUndo())
	{
		actions[head--]->undo(data);
	}
}

template<class T>
inline void UndoRedo<T>::redo()
{
	if (canRedo())
	{
		actions[++head]->redo(data);
	}
}

template<class T>
inline void UndoRedo<T>::clear()
{
	destroyArray(0, actions.size());
	head = -1;
}

template<class T>
inline bool UndoRedo<T>::canUndo()
{
	return head >= 0;
}

template<class T>
inline bool UndoRedo<T>::canRedo()
{
	return head < actions.size() - 1;
}

