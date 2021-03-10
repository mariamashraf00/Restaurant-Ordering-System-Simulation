#ifndef __PROMOTION_EVENT_H_
#define __PROMOTION_EVENT_H_

#include "Events/Event.h"

#include < fstream> 
using namespace std;

class PromotionEvent : public Event
{
	int ExMoney;

public:
	PromotionEvent(int eTime=0, int oID=0);
	
	virtual void Execute(Restaurant* pRest);
	
	void setExmoney(int e);
	
	virtual void ReadData(ifstream& Infile);
};

#endif
