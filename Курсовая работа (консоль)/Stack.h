#pragma once

template<class T>
class Node
{
private:
	T value;
	Node<T>* next;
	Node<T>* prev;
public:
	template<class T>
	friend class Stack;
};

/*
				<-Moving DOWN->
	+---+			+---+			+---+		* <- head
	| * |	 UP		|   |	 UP		|   |
	+---+			+---+			+---+
	|   |			| * |			|   |
	+---+			+---+			+---+
	|   |			|   |			| * |
	+---+			+---+			+---+
	|   |	DOWN	|   |	DOWN	|   |
	+---+			+---+			+---+
				<-Moving UP->
	+---+			+---+			+---+
	|   |	 UP		|   |	 UP		| * |
	+---+			+---+			+---+
	|   |			| * |			|   |
	+---+			+---+			+---+
	| * |			|   |			|   |
	+---+			+---+			+---+
	|   |	DOWN	|   |	DOWN	|   |
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

};

template<class T>
inline void Stack<T>::destroyToDown()
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
inline void Stack<T>::destroyToUp()
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
