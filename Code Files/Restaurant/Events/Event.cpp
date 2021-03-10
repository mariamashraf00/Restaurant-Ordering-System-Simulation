#include "Event.h"


Event::Event(int eTime, int ordID)
{
	EventTime = eTime;
	
	OrderID	= ordID;
}


int Event::getEventTime()
{
	return EventTime;
}

int Event::getOrderID()
{
	return OrderID;
}



void Event::setEventTime(int t)
{

	EventTime = t > 0 ? t : 0;


}

void Event::setOrderID(int id)
{

	OrderID = id > 0 ? id : 0;

}

Event::~Event()
{

}



