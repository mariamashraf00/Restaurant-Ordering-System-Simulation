#ifndef __NODEP_H_
#define __NODEP_H_

template < typename T>
class NodeP
{
protected:
	T item;
	NodeP<T>* next;
	int p;  // PRIORITY

public:
	NodeP();

	NodeP(const T& r_Item);	//passing by const ref.

	NodeP(const T& r_Item, NodeP<T>* nextNodePtr);

	void setItem(const T& r_Item);

	void setNext(NodeP<T>* nextNodePtr);

	T getItem() const;

	NodeP<T>* getNext() const;

	void setp(int pr);

	int getp();

}; // end Node


template < typename T>
NodeP<T>::NodeP()
{
	next = nullptr;
}

template < typename T>
NodeP<T>::NodeP(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
NodeP<T>::NodeP(const T& r_Item, NodeP<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void NodeP<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void NodeP<T>::setNext(NodeP<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
void NodeP<T>::setp(int pr)
{
	p = pr;
}
template < typename T>
int NodeP<T>::getp()
{
	return p;
}

template < typename T>
T NodeP<T>::getItem() const
{
	return item;
}

template < typename T>
NodeP<T>* NodeP<T>::getNext() const
{
	return next;
}

#endif
