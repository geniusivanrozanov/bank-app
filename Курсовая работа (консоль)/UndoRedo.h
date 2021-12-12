#pragma once
#include "Stack.h"
#include "Array.h"

template<class T>
class Action
{
public:
	virtual void undo(Array<T>& data) = 0;
	virtual void redo(Array<T>& data) = 0;
};
