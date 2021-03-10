#include "CancellationEvent.h"
#include "Rest/Restaurant.h"

CancellationEvent::CancellationEvent(int eTime, int oID) :Event(eTime, oID)
{

}

void CancellationEvent::Execute(Restaurant* pRest)
{
	Order* pO = nullptr;
	
	pRest->DeleteFromNormalById(OrderID, pO); // Delete the Order by its ID from Normal Wait List if found

	if (pO != nullptr)
	{
		pRest->setTotalN(pRest->getTotalN() - 1);
		delete pO;
	}
}


void CancellationEvent::ReadData(ifstream& Infile)  // Reads Data For this Evenet (Called By Read In Restaurant Class)
{
	int TS, ID;
	
	Infile >> TS >> ID;
	
	this->setEventTime(TS);
	
	this->setOrderID(ID);
}
