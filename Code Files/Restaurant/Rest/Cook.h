#pragma once
#include "..\Defs.h"
#include "Order.h"

#pragma once
class Cook
{
	int ID;
	
	ORD_TYPE type;
	
	Order* AssignedOrder;
	
	int BO; //Number of dishes before Break
	
	int B; // Break Duration 
	
	bool available; // Available or not
	
	int O; // Number of orders done so far
	
	float Speed; 
	
	int TS_Break; // Time step at which the order took a break
	
	bool inBreak; // In a break or not
	
	bool Inj;
	
	int Inj_TS;
	
	int RST_P;
	
	bool injured_before;

public:
	Cook();

	virtual ~Cook();

	////////////////////////////////////////Setters & Getters for data members //////////////////////////////////////////////////////////////////////
	void setType(ORD_TYPE t);

	ORD_TYPE getType(); 

	void setID(int id);

	int getID();

	void setOrder(Order* pO);

	Order* getOrder();

	void setSpeed(float S);

	float getSpeed();

	void setBO(int b);

	int getBO();

	void setB(int b);

	int getB();

	bool getAvailable();

	void setO(int o);

	int getO();

	void setTS(int TS);

	int getTS();


	void setInj_TS(int TS);

	int getInj_TS();

	void setInj(bool state);

	bool getInj();

	void setRST(int t);

	int getRST();

	void setInjuredB(bool status);

	bool getInjuredB();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool TakeBreak();  // To check wether the cook should take a break or not 

	bool EndBreak(int TS); // to check wether the cook should end his break or not

	bool getBreak(); // To know if the cook is in a break

	bool operator == (ORD_TYPE t);
};
