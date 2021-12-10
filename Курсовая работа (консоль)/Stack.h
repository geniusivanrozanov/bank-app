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
	+---+			+---+			+---+			* <- head
	| * |			|   |			|   |
	+---+			+---+			+---+
	|   |			| * |			|   |
	+---+			+---+			+---+
	|   |			|   |			| * |
	+---+			+---+			+---+
	|   |			|   |			|   |
	+---+			+---+			+---+
				<-Moving UP->
	+---+			+---+			+---+
	|   |			|   |			| * |
	+---+			+---+			+---+
	|   |			| * |			|   |
	+---+			+---+			+---+
	| * |			|   |			|   |
	+---+			+---+			+---+
	|   |			|   |			|   |
	+---+			+---+			+---+
*/

template<class T>
class Stack
{
private:
	Node<T>* head;

};