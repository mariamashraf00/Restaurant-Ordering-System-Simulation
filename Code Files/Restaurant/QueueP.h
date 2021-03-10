#ifndef __QUEUEP_H_
#define __QUEUEP_H_
#include "NodeP.h"

// PRIORITY QUEUE

template <typename T>
class QueueP
{
private:

	NodeP<T>* frontPtr;
	int count;
public:
	QueueP();
	bool isEmpty() const;
	void Insert(T& it, int pr);
	void InsertAss(T& it, int pr); 
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);
	int getcount();
	~QueueP();
};

template <typename T>
void QueueP<T>::Insert(T& it, int pr)
{
	NodeP<T>* newNodePtr = new NodeP<T>;
	newNodePtr->setItem(it);
	newNodePtr->setp(pr);
	if (frontPtr == nullptr || pr > frontPtr->getp())
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else {
		NodeP <T>* ptr = frontPtr;
		while (ptr->getNext() != nullptr && pr >= ptr->getNext()->getp())
			ptr = ptr->getNext();
		newNodePtr->setNext(ptr->getNext());
		ptr->setNext(newNodePtr);
	}
	count++;
}






template <typename T>
void QueueP<T>::InsertAss(T& it, int pr)
{
	NodeP<T>* newNodePtr = new NodeP<T>;
	newNodePtr->setItem(it);
	newNodePtr->setp(pr);
	if (frontPtr == nullptr || pr < frontPtr->getp())
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}

	else
	{
		if (pr == frontPtr->getp())
		{


			NodeP <T>* ptr = frontPtr;
			newNodePtr->setNext(ptr->getNext());
			frontPtr->setNext(newNodePtr);

		}
		else
		{
			NodeP <T>* ptr = frontPtr;
			while (ptr->getNext() != nullptr && pr >= ptr->getNext()->getp())
				ptr = ptr->getNext();
			newNodePtr->setNext(ptr->getNext());
			ptr->setNext(newNodePtr);
		}
	}

	count++;

}









template <typename T>
QueueP<T>::QueueP()
{
	frontPtr = nullptr;
	count = 0;
}

template <typename T>
bool QueueP<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}
template <typename T>
bool QueueP<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	NodeP<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();

	delete nodeToDeletePtr;
	count--;
	return true;

}
template <typename T>
bool QueueP<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;
	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
QueueP<T>::~QueueP()
{
}

template <typename T>
T* QueueP<T>::toArray(int& count)
{
	count = 0;
	if (!frontPtr)
		return nullptr;
	NodeP<T>* ptr = frontPtr;
	while (ptr)
	{
		count++;
		ptr = ptr->getNext();
	}
	T* Arr = new T[count];
	ptr = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = ptr->getItem();
		ptr = ptr->getNext();
	}
	return Arr;
}

template <typename T>
int QueueP<T>::getcount()
{
	return count;

}
#endif