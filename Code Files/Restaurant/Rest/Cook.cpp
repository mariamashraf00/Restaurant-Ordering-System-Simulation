#include "Cook.h"


Cook::Cook()
{
	this->AssignedOrder = nullptr;
	
	this->available = true;
	
	this->inBreak = false;
	
	this->Inj = false;
	
	O = 0;
	
	TS_Break = 0;
	
	this->injured_before = false;
}

Cook::~Cook()
{
}


ORD_TYPE Cook::getType()
{
	return this->type;
}


int Cook::getRST()
{
	return RST_P;  
}


void Cook::setType(ORD_TYPE t)
{
	this->type = t;
}


int Cook::getID()
{
	return ID;
}

void Cook::setID(int id)
{
	ID = (id > 0 && id < 101) ? id : 0; 
}


void Cook::setOrder(Order* pO)
{
	if (pO != nullptr)
	{
		this->AssignedOrder = pO;
	
		this->available = false;
		
		++O;
	}
	
	else this->AssignedOrder = nullptr;
}

Order* Cook::getOrder()
{
	return AssignedOrder;
}

void Cook::setSpeed(float S)
{
	Speed = S > 0 ? S : 0;

}

float Cook::getSpeed()
{
	return Speed;
}

void Cook::setBO(int b)
{
	BO = b > 0 ? b: 0;

}

int Cook::getBO()
{
	return BO;
}

void Cook::setB(int b)
{
	B = b > 0 ? b : 0;

}

int Cook::getB()
{
	return B;
}

bool Cook::getAvailable()
{
	return available;
}

void Cook::setO(int o)
{
	O = o > 0 ? o : 0;

}

int Cook::getO()
{
	return O;
}

bool Cook::TakeBreak()
{
	if (O >= BO)
	{
	
		this->available = false;
		
		this->inBreak = true;
		
		return true;
	}
	
	return false;
}

bool Cook::getBreak()
{
	return this->inBreak;
}
void Cook::setTS(int TS)
{
	TS_Break = TS > 0 ? TS : 0;

}

int Cook::getTS()
{
	return TS_Break;
}


bool Cook::EndBreak(int TS)
{
	if (TS - TS_Break >= B)
	{
		this->inBreak = false;
	
		this->available = true;
		
		this->O = 0;
		
		return true;
	}
	
	return false;
}



bool Cook::operator== (ORD_TYPE t)
{
	if (this->getType() == t)
	
		return true;
	
	else return false;
	
}



void Cook::setRST(int t)
{
	RST_P = t >= 0 ? t : 0;

}


void Cook::setInj(bool inj)
{
	Inj = inj; 
}
bool Cook::getInj()
{
	return Inj; 

}

void Cook::setInj_TS(int T)
{
	Inj_TS = T; 
}
int Cook::getInj_TS()
{
	return Inj_TS; 
}



void Cook::setInjuredB(bool status)
{

	injured_before = status;
}


bool Cook::getInjuredB()
{
	return injured_before;

}