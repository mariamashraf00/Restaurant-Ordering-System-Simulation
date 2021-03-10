#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_
#include "Event.h"
#include < fstream> 
using namespace std;

class ArrivalEvent : public Event
{
	ORD_TYPE OrdType;

	int OrdMoney;
	
	int OrderSize;

public:

	ArrivalEvent(int eTime=0, int oID=0, ORD_TYPE oType=TYPE_NRM);
	
	virtual void Execute(Restaurant* pRest);
	
	virtual void ReadData(ifstream& Infile);

	void settype(ORD_TYPE t);
	
	void setmoney(int M);
	
	void setsize(int S);



};

#endif