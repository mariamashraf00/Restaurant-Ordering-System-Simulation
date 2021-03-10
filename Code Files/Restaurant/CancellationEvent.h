#ifndef __CANCELLATION_EVENT_H_
#define __CANCELLATION_EVENT_H_

#include "Events/Event.h"

#include < fstream> 
using namespace std;

class CancellationEvent : public Event
{

public:

	CancellationEvent(int eTime=0, int oID=0);

	virtual void Execute(Restaurant* pRest);

	virtual void ReadData(ifstream& Infile);


};

#endif
