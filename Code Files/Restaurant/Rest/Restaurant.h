#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_
#include "..\QueueP.h"
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "Order.h"
#include"..\List.h"
class Restaurant
{
private:
	GUI* pGUI;

	Queue<Event*> EventsQueue;	

	List<Order*> NormalList;

	Queue<Order*> VeganQueue; 
	
	QueueP <Order*> VIPQueue; 
	
	Queue<Order*> UrgentOrders;
	
	List<Order*> InService; 
	
	Queue<Order*> Finished; 
	
	int AP;  
	
	float InjProp;

	int VIP_W;

	List<Cook*> AvailableCooks; 

	Queue<Cook*> BusyCooks;  
	
	Queue<Cook*> Cooks_OnBreak;
	
	Queue <Cook*> Injured_Cook; 
	
	int NC=0;
	
	int VC=0;  
	
	int GC=0; 
	
	int TVIPCOOK; 
	
	int TNRMCOOK; 
	
	int TVGNCOOK;
	
	int TotalP = 0;
	
	int TotalN = 0;
	
	int TotalV = 0;
	
	int TotalG = 0;
	
	int URG_Orders = 0;
	
	int Inj_Cooks = 0;

	int SN = 0;

	int SG = 0;

	int SV = 0;
public:

	Restaurant();

	~Restaurant();
	
	void setnumcook(int V, int G, int N); 
	
	void setTotalN(int num);
	
	int getTotalN();
	
	void setTotalV(int num);
	
	int getTotalV();
	
	void setTotalG(int num);
	
	int getTotalG();
	
	void ExecuteEvents(int TimeStep);

	void RunSimulation();
	
	void FillDrawingList();

	void setCooks(int N, int V, int G, int BO, int BN_min,int BN_max, int BV_min, int BV_max, int BG_min,int BG_max, int SV_min,int SV_max, int SN_min,int SN_max, int SG_min,int SG_max, int RST);

	void AddtoNormalList(Order* pO);

	void RemovefromNormalList(Order* pO);

	void AddtoVeganQueue(Order* pO);

	void AddtoVIPQueue(Order* pO, int p);

	void setAP(int a);
	
	void setVIP_WT(int v);
	
	void setinjured_prop(float p);

	void DeleteFromNormalById(int id, Order*& pO);

	void AutoPromote(int currTS); 

	void AutoPromote_2(int currTS); 

	void ServeNOrder(int TS); 

	void ServeVOrder(int TS); 

	void ServeGOrder(int TS); 

	void GetCook(ORD_TYPE t,Cook * & pC); 

	void CheckOnOrders(int TS , float R ); 

	void CheckOnCooks(int TS);

	void Simulator(int mode);
	
	void Move_To_Urgent(int TS);

	void ServeURGOrder(int TS );

	void Check_injured_finshed(int Ts);

	void Save();

	void Read();

};


#endif