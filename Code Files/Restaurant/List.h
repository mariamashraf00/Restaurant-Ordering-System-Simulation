#pragma once
#include "Generic_DS/Node.h"

template <typename T>
class List {

	Node<T>* Head;
	int count;
	Node<T>* getNodeAt(int position);

public:

	List();
	~List();
	bool isEmpty();

	int getcount();
	void GetEntry(int pos, T& entry);
	bool Remove(int pos, T& entry);
	void InsertBeg(const T& data);
	void InsertEnd(const T& data);
	bool RemoveBeg(T& entry);
	bool DeleteById(int id, T& entry); // Deletes Element By ID
	bool DeleteByType(ORD_TYPE t, T& entry);  // Deletes Element By Type
	T* toArray(int & count);
	List<T> GetElementsAbove(int CTS, int AP); // Another Idea for AutoPromotion

};

template <typename T>

List<T>::List()
{
	count = 0;
	Head = nullptr;
}

template <typename T>

void List<T>::InsertBeg(const T& data)
{
	Node<T>* R = new Node<T>(data);

	if (isEmpty())
	{
		Head = R;
		count++;
		return;
	}
	R->setNext(Head);
	Head = R;
	count++;
}

template <typename T>

void List<T>::InsertEnd(const T& data)
{

	Node<T>* R = new Node<T>(data);

	if (!Head)
	{
		Head = R;
		count++;
		return;
	}

	Node<T>* ptr = Head;
	while (ptr)
	{
		if (ptr->getNext() == nullptr)
		{
			ptr->setNext(R);
			R->setNext(nullptr);
			count++;
			return;
		}
		ptr = ptr->getNext();
	}
}


template <typename T>
bool List<T>::isEmpty()
{
	if (!Head)
	{
	return true;
	}
	else return false;
}
template <typename T>

int List<T>::getcount()
{
	return count;
}

template <typename T>

bool List<T>::RemoveBeg(T& entry)
{

	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = Head;
	entry = Head->getItem();
	Head = Head->getNext();

	if (nodeToDeletePtr->getNext()==nullptr)	 // Special case: one node in queue
		Head= nullptr;

	delete nodeToDeletePtr;

	count--;

	return true;
}

template <typename T>
Node<T>* List<T>::getNodeAt(int position)
{
	Node<T>* curPtr = Head;
	for (int i = 1; i <= position; i++)
		curPtr = curPtr->getNext();
	return curPtr;
}

template <typename T>
List<T>::~List()
{


}

template <typename T>

bool List<T>::Remove(int pos, T& entry)
{
	bool ableToRemove = (pos >= 1) && (pos <= count);
	if (ableToRemove)
	{
		Node<T>* curPtr = nullptr;
		if (pos == 1)
		{
			curPtr = Head;
			Head = Head->getNext();
		}
		else
		{
			Node<T>* prevPtr = getNodeAt(pos - 1);
			curPtr = prevPtr->getNext();

			prevPtr->setNext(curPtr->getNext());
		}
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;
		count--;
	}
	return ableToRemove;
}


template <typename T>
T* List<T>::toArray(int&count)

{
	count = 0;
	if (!Head)
		return nullptr;
	Node<T>* ptr = Head;
	while (ptr)
	{
		count++;
		ptr = ptr->getNext();
	}
	T* Arr = new T[count];
	ptr = Head;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = ptr->getItem();
		ptr = ptr->getNext();
	}
	return Arr;

}

template <typename T>
bool List<T>::DeleteById(int id, T& entry)
{
	if (!Head)
		return false;
	Node<T>* nodetodelete = nullptr;
	Node<T>* ptr = Head;

	if (*(Head->getItem()) == id)
	{
		nodetodelete = Head;
		entry = Head->getItem();
		Head = Head->getNext();
		delete nodetodelete;
		count--;
		return true;
	}
	if (Head != nullptr)
	{
		Node <T>* next = Head->getNext();
		while (ptr && next)
		{
			if (*(next->getItem()) == id)
			{
				nodetodelete = next;
				entry = next->getItem();
				ptr->setNext(next->getNext());
				delete nodetodelete;
				count--;
				return true;
			}
			ptr = ptr->getNext();
			if (ptr != nullptr)
				next = next->getNext();
		}
	}
	return false;
}

template <typename T>
List<T> List<T>::GetElementsAbove(int CTS, int AP)
{
	List<T> Returned;

	if (!Head)
		return Returned;
	Node<T>* nodetodelete = nullptr;
	Node<T>* ptr = Head;

	while ( Head && (-(*(Head->getItem()) - CTS ) >= AP))
	{
		nodetodelete = Head;
		Head = Head->getNext();
		Returned.InsertEnd(nodetodelete->getItem());
		delete nodetodelete;
		count--;
	}
	if (Head != nullptr)
	{
		Node <T>* next = Head->getNext();

		while (ptr && next)
		{
			while ((-(*(next->getItem()) - CTS) >= AP))
			{
				nodetodelete = next;
				ptr->setNext(next->getNext());
				Returned.InsertEnd(nodetodelete->getItem());
				delete nodetodelete;
				count--;
			}
			ptr = ptr->getNext();
			if (ptr != nullptr)
				next = next->getNext();
		}
	}
	return Returned;
}

template <typename T>
bool List<T>::DeleteByType(ORD_TYPE t, T& entry)
{
	if (!Head)
		return false;
	Node<T>* nodetodelete = nullptr;
	Node<T>* ptr = Head;

	if (*(Head->getItem()) == t)
	{
		nodetodelete = Head;
		entry = Head->getItem();
		Head = Head->getNext();
		delete nodetodelete;
		count--;
		return true;
	}
	if (Head != nullptr)
	{
		Node <T>* next = Head->getNext();
		while (ptr && next)
		{
			if (*(next->getItem()) == t)
			{
				nodetodelete = next;
				entry = next->getItem();
				ptr->setNext(next->getNext());
				delete nodetodelete;
				count--;
				return true;
			}
			ptr = ptr->getNext();
			if (ptr != nullptr)
				next = next->getNext();
		}
	}
	return false;
}

template <typename T>
void List<T>::GetEntry(int pos, T& entry)
{

	Node<T>* ptr = getNodeAt(pos);
	if (ptr)
		entry = ptr->getItem();
}
