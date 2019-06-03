#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;


template <class T>
class ListClass
{
public:
	ListClass(); // constructor
	~ListClass(); // destructor
	void push_back(T); // add a node to the tail of the list
	void push_front(T); // add a node to the head of the list
	void pop_back(); // delete the last node
	void pop_front(); // delete the first node
	void insert(size_t, T); // add a node by index (insert before a node that was previously available at this index)
	T at(size_t); // get a data from the node by index
	void remove(size_t);// delete a node by index
	size_t get_size(); // get size of the list
	void clear(); // delete all nodes from the list
	void set(size_t, T); // replacing a data in the node by index with the passed data
	bool isEmpty(); // check for empty list


	friend ostream& operator<< (ostream& output_stream, ListClass<T> &list)// output operator overloading
	{
		for (int counter = 0; counter < list.size; counter++)
			cout << list.at(counter) << " ";

		return output_stream;
	}

	class Node
	{
	public:

		Node(T data1, Node * next1 = nullptr, Node * prev1 = nullptr) //constructor
		{
			data = data1;
			next = next1;
			prev = prev1;
		};
		~Node(); // destructor

		friend ListClass; // used for data access from ListClass
	private:
		Node* next; // pointer to the next node
		Node* prev; // pointer to the previous node
		T data; // data in the node
	};

private:


	Node * head; // pointer to the head of the list
	Node * tail; // pointer to the tail of the list
	size_t size; // size of the list


};


template<class T>
ListClass<T>::ListClass()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template<class T>
ListClass<T>::~ListClass()
{
	clear();
}

template<class T>
ListClass<T>::Node::~Node() {}

template <class T>
void ListClass<T>::push_back(T newData)
{
	if (isEmpty())
	{
		head = new Node(newData); // create the first node in the list
		tail = head; // set the tail pointer to this node
	}
	else
	{
		tail->next = new Node(newData); // create a node on the tail of the list
		tail->next->prev = tail; // set the pevious pointer for this node
		tail = tail->next; // set the tail pointer to this node
	}
	size++; // increase size
}

template <class T>
void ListClass<T>::push_front(T newData)
{
	if (isEmpty()) // if the list is empty
	{
		head = new Node(newData); // create the first node in the list
		tail = head; // set the tail pointer to this node
	}
	else
	{
		head = new Node(newData, head); // add a new node that next node is the head and set on it the pointer on the beginning of the list
		head->next->prev = head;
	}

	size++; // increase size
}

template<class T>
void ListClass<T>::pop_back()
{
	if (isEmpty()) // if the list is empty
	{
		throw logic_error("The list is empty");
	}

	if (size == 1) // if the list consists of only one node
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node * current = head; // moving to the second to the tail
		while (current->next != tail)
			current = current->next;
		current->next = nullptr; // zero the pointer to the next node
		delete tail; // delete the tail node
		tail = current; // set the pointer of the tail on this node
	}
	size--; // decrease size
}

template<class T>
void ListClass<T>::pop_front()
{
	if (isEmpty()) // if the list is empty
	{
		throw logic_error("The list is empty");
	}
	if (size == 1) // if the list consists of only one node
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node* current = head;
		head = current->next; // set the pointer of the head on the second node
		head->prev = nullptr; // zero the pointer to the first node
		delete current; // delete the ex head node
	}
	size--; // decrease size
}

template<class T>
void ListClass<T>::insert(size_t index, T newData)
{
	if (index > size || index < 0) // if index is invalid
		throw invalid_argument("Index is greater than list size or less than zero");
	else
	{
		size_t counter = 0; // counter
		Node * previous; // pointer to the previous node to insert

		if (index == 0) // if index is zero
		{
			previous = new Node(newData, head); // insert the first node and set a pointer to the head of the list
			if (head != nullptr)
				head->prev = previous;
			head = previous;
		}
		else
		{
			previous = head;
			while (counter != index - 1) // move to the node before required for an insert
			{
				previous = previous->next; // moving
				counter++;
			}
			previous->next = new Node(newData, previous->next, previous); // insert a new node and link pointers to it
			if (index == size) // if the index is equal to the size
			{
				tail = previous->next; // place a pointer to the tail of the list on a new node
			}
		}
		size++; // increase size
	}
}

template<class T>
void ListClass<T>::remove(size_t index)
{
	if (index >= size || index < 0) // if index is invalid
		throw invalid_argument("Index is greater than list size or less than zero");
	else
	{
		size_t counter = 0; // counter
		Node * current = head;
		if (index == 0) // if index is zero
		{
			head = head->next; // move the pointer of the head
			delete current; // delete the ex head node
			head->prev = nullptr;
		}
		else
		{
			while (counter != index) // move to the node required for a remove
			{
				current = current->next; // moving
				counter++;
			}
			current->prev->next = current->next; // link previous node to the next one
			if (size == index + 1) // if index is 1 less than size
			{
				tail = current->prev; // move the pointer of the tail of the list to the previous node

			}
			else
			{
				current->next->prev = current->prev;
			}


			delete current; // delete node

		}
		size--; // decrease size
	}
}


template<class T>
size_t ListClass<T>::get_size()
{
	return size;
}
template <class T>
void ListClass<T>::clear()
{
	Node * temp; // supporting pointer to the next node from the deleting node

	while (head != nullptr) // until the entire list is deleted
	{
		temp = head->next; // movement
		delete head; // delete previous node
		head = temp; // set the pointer to the head of the list
	}
	tail = nullptr; // zero the pointer of the tail of the list
	size = 0; // zero the size of the list
}

template<class T>
bool ListClass<T>::isEmpty()
{
	if (head == nullptr && tail == nullptr && size == 0)
		return true;
	else
		return false;
}

template<class T>
T ListClass<T>::at(size_t index)
{
	if (index >= size || index < 0) // if index is invalid
		throw invalid_argument("Index is greater than list size or less than zero");
	else
	{
		size_t counter = 0; // counter
		Node * current = head;
		while (counter != index) // move to the required node 
		{
			current = current->next; // moving
			counter++;
		}
		return current->data; // data output	
	}
}

template<class T>
void ListClass<T>::set(size_t index, T newData) {
	if (index >= size || index < 0) // if index is invalid
		throw invalid_argument("Index is greater than list size or less than zero");
	else
	{
		size_t counter = 0; // counter
		Node * current = head;
		while (counter != index) // move to the required node 
		{
			current = current->next; // moving
			counter++;
		}
		current->data = newData; // put the data to the required node
	}
}

