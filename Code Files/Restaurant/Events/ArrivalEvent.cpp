#include "ArrivalEvent.h"

#include "..\Rest\Restaurant.h"

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType) :Event(eTime, oID)
{
	OrdType = oType;
}

void ArrivalEvent::settype(ORD_TYPE T)
{

	OrdType = T;
}

void ArrivalEvent::setmoney(int M)
{
	OrdMoney = M > 0 ? M : 0;

}

void ArrivalEvent::setsize(int S)
{
	OrderSize = S > 0 ? S : 0;

}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	Order* pO = new Order(OrderID, OrdType, OrderSize, OrdMoney, EventTime); // Creat Order Object

	switch (OrdType)  // Check for type to know which list or queue to add it to
	{
	case TYPE_NRM:
	{
		pRest->AddtoNormalList(pO);

		pRest->setTotalN(pRest->getTotalN() + 1); // Increase the count of normal orders for output file

		break;
	}
	case TYPE_VGAN:
	{
		pRest->AddtoVeganQueue(pO);

		pRest->setTotalG(pRest->getTotalG() + 1); // Increase the count of Vegan orders for output file

		break;
	}

	case TYPE_VIP:
	{
		pRest->AddtoVIPQueue(pO, pO->getpr()); // getpr() calculates priority for VIP only

		pRest->setTotalV(pRest->getTotalV() + 1); // Increase the count of VIP orders for output file

		break;
	}

	}

}


void ArrivalEvent::ReadData(ifstream& Infile)  // Reads Data For this Evenet (Called By Read In Restaurant Class)
{

	char T;

	int TS, ID, Size, Money;

	Infile >> T >> TS >> ID >> Size >> Money;

	this->setmoney(Money);

	this->setOrderID(ID);

	this->setEventTime(TS);

	this->setsize(Size);

	switch (T)
	{

	case ('N'):
	{
		this->settype(TYPE_NRM);

		break;
	}
	case ('V'):
	{
		this->settype(TYPE_VIP);

		break;
	}
	case ('G'):
	{
		this->settype(TYPE_VGAN);
		
		break;
	}
	}
}