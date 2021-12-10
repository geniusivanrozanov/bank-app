#pragma once
#include <iostream>

template<class T>
class Node
{
private:
	T value;
	Node<T>* next;
	Node<T>* prev;
public:
	Node(Node<T>* next = nullptr, Node<T>* prev = nullptr)
		: next(next), prev(prev)
	{}
	template<class T>
	friend class Stack;
};

/*
		Main direction from UP to DOWN
				<-Moving DOWN->
	+---+			+---+			+---+		* <- head
	| * |	 UP		|   |	 UP		|   |
	+---+			+---+			+---+
	|   |			| * |			|   |
	+---+			+---+			+---+
	|   |			|   |			| * |
	+---+			+---+			+---+
	|   |	DOWN		|   |	DOWN		|   |
	+---+			+---+			+---+
				<-Moving UP->
	+---+			+---+			+---+
	|   |	 UP		|   |	 UP		| * |
	+---+			+---+			+---+
	|   |			| * |			|   |
	+---+			+---+			+---+
	| * |			|   |			|   |
	+---+			+---+			+---+
	|   |	DOWN		|   |	DOWN		|   |
	+---+			+---+			+---+
*/

template<class T>
class Stack
{
private:
	Node<T>* head;

	void destroyToDown();
	void destroyToUp();
public:
	Stack();
	~Stack();

	void push(T);

	T popUp();
	T popDown();
	T peek();
};

template<class T>
inline void Stack<T>::destroyToUp()
{
	Node<T>* prev = head->prev;
	Node<T>* temp;
	head->prev = nullptr;
	while (prev != nullptr)
	{
		temp = prev->prev;
		delete prev;
		prev = temp;
	}
}

template<class T>
inline void Stack<T>::destroyToDown()
{
	Node<T>* next = head->next;
	Node<T>* temp;
	head->next = nullptr;
	while (next != nullptr)
	{
		temp = next->next;
		delete next;
		next = temp;
	}
}

template<class T>
inline Stack<T>::Stack()
	: head(nullptr)
{
}

template<class T>
inline Stack<T>::~Stack()
{
	if (head)
	{
		destroyToDown();
		destroyToUp();
		delete head;
	}
}

template<class T>
inline void Stack<T>::push(T element)
{
	Node<T>* temp = new Node<T>(head);
	temp->value = element;
	if (head)
	{
		destroyToUp();
		head->prev = temp;
	}
	head = temp;
}

template<class T>
inline T Stack<T>::popUp()
{
	if (head && head->prev)
	{
		head = head->prev;
	}
	return head->next->value;
}

template<class T>
inline T Stack<T>::popDown()
{
	if (head && head->next)
	{
		head = head->next;
	}
	return head->prev->value;
}

template<class T>
inline T Stack<T>::peek()
{
	return head->value;
}
