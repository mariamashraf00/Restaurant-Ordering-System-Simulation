#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;

	ORD_TYPE type;

	ORD_STATUS status;

	int Size;

	int Money;

	int ArrTime, ServTime, FinishTime, WaitTime;

	int pr;  // Priority is calculated if type is VIP only otherwise = 0

	bool URG;

public:

	Order(int ID, ORD_TYPE r_Type, int s, int m, int at);

	virtual ~Order();

	/////////////////////////////////////// Setters & Getters For Data Members //////////////////////////////////////////////////////////////
	int GetID();

	ORD_TYPE GetType() const;
	
	void setType(ORD_TYPE T);

	void setStatus(ORD_STATUS s);
	
	ORD_STATUS getStatus() const;

	void setMoney(int m);
	
	int getMoney();

	int getSize();

	int getAT();
	
	void setAT(int AT);

	int getWT();
	
	void setWT(int WT);

	int getST();
	
	void setST(int st);

	int getFT();
	
	void setFT(int ft);

	int getpr();
	
	void setURG(bool U);
	bool getURG();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Operator Overloading
	
	bool operator == (int id);
	
	bool operator == (ORD_STATUS s);
	
	int operator - (int TS);
	
	bool operator == (ORD_TYPE t);

};

#endif