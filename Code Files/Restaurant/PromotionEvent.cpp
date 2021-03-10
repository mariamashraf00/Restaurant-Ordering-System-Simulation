#include "PromotionEvent.h"
#include "Rest/Restaurant.h"

PromotionEvent::PromotionEvent(int eTime, int oID) :Event(eTime, oID)

{
}

void PromotionEvent::Execute(Restaurant* pRest)
{
	Order* pO = nullptr;

	pRest->DeleteFromNormalById(OrderID, pO); // if order is found in the normal waiting list it'll get promoted

	if (pO != nullptr)
	{
		pO->setMoney(pO->getMoney() + ExMoney);

		pO->setType(TYPE_VIP);

		pO->setAT(EventTime);

		pRest->setTotalN(pRest->getTotalN() - 1);

		pRest->setTotalV(pRest->getTotalV() + 1);

		pRest->AddtoVIPQueue(pO, pO->getpr());
	}
}


void PromotionEvent::setExmoney(int EM)
{

	ExMoney = EM > 0 ? EM : 0;

}


void PromotionEvent::ReadData(ifstream& Infile) // Reads Data For this Evenet (Called By Read In Restaurant Class)
{
	int Ts, ID, ExMony;

	Infile >> Ts >> ID >> ExMony;

	this->setEventTime(Ts);

	this->setOrderID(ID);

	this->setExmoney(ExMony);

}