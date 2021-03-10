#include "Order.h"
#include <cmath>
Order::Order(int id, ORD_TYPE r_Type, int s, int m, int at)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999

	type = r_Type;

	status = WAIT;

	Size = s > 0 ? s : 0;

	this->setMoney(m);

	ArrTime = at > 0 ? at : 0;

	ServTime = 0;

	FinishTime = 0;

	WaitTime = 0;

	pr = 0;

	URG = false;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}

int Order::getSize()
{
	return Size;
}

int Order::getST()
{

	return ServTime;

}
void Order::setST(int st)
{

	ServTime = st;
}

int Order::getWT()
{

	return WaitTime;

}
void Order::setWT(int WT)
{

	WaitTime = WT;
}
int Order::getFT()
{

	return FinishTime;
}
void Order::setFT(int ft)
{

	FinishTime = ft;
}
int Order::getAT()
{

	return ArrTime;
}
ORD_TYPE Order::GetType() const
{
	return type;
}



void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order::setMoney(int m)
{

	Money = m > 0 ? m : 0;

}


void Order::setType(ORD_TYPE T)
{

	type = T;

}
int Order::getMoney()

{

	return Money;

}

bool Order::operator== (int id)
{
	if (this->GetID() == id)
	
		return true;
	
	else
		
		return false;
}

bool Order::operator == (ORD_STATUS s)
{
	if (this->getStatus() == s)
	
		return true;
	
	else
	
		return false;
}

int Order::operator- (int TS)
{

	return (this->getAT() - TS);

}

bool Order::operator== (ORD_TYPE t)
{

	if (this->GetType() == t)
		
		return true;
	
	else return false;

}

int Order::getpr()
{
	if (type == TYPE_VIP)
	
		pr = (1000*Money)/(Size*(pow(ArrTime,1.4)));
	
	else pr = 0;

	return pr;

}

void Order::setAT(int at)
{

	this->ArrTime = at;
}


void Order::setURG(bool U)
{
	URG = U;

}

bool Order::getURG()
{
	return URG;

}