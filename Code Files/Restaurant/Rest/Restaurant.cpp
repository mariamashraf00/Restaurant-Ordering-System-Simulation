#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\CancellationEvent.h"
#include "..\PromotionEvent.h"
using namespace std;

Restaurant::Restaurant()
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;

	PROG_MODE mode = pGUI->getGUIMode();

	switch (mode)

	{

	case MODE_INTR:

		Simulator(mode);

		break;

	case MODE_STEP:

		Simulator(mode);

		break;

	case MODE_SLNT:

		Simulator(mode);

		break;

	};

}

void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;

	while (EventsQueue.peekFront(pE))	//as long as there are more events

	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep

			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue

		delete pE;		//deallocate event object from memory
	}

}

Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}

void Restaurant::FillDrawingList()
{
	Order* pOrd;
	Cook* pC;
	int size = 0;

	Cook** Normal = AvailableCooks.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pC = Normal[i];
		pGUI->AddToDrawingList(pC);
	}
	Order** UOrders = UrgentOrders.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pOrd = UOrders[i];
		pGUI->AddToDrawingList(pOrd);
	}
	Order** VOrders = VIPQueue.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pOrd = VOrders[i];
		pGUI->AddToDrawingList(pOrd);
	}
	Order** GOrders = VeganQueue.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pOrd = GOrders[i];
		pGUI->AddToDrawingList(pOrd);
	}
	Order** NOrders = NormalList.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pOrd = NOrders[i];
		pGUI->AddToDrawingList(pOrd);
	}
	Order** Service = InService.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pOrd = Service[i];

		pGUI->AddToDrawingList(pOrd);
	}

	Order** Done = Finished.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pOrd = Done[i];

		pGUI->AddToDrawingList(pOrd);
	}
}

void Restaurant::Simulator(int mode)
{
	Read();
	if (mode == 0)
	{
		pGUI->PrintMessage(BLACK, true, "Click to update screen");
		pGUI->waitForClick();
	}
	Order* pO;
	int CurrentTimeStep = 1;
	float R_injured;  // random no for injured cook 
	while (!EventsQueue.isEmpty() || !InService.isEmpty() || !NormalList.isEmpty() || !VeganQueue.isEmpty() || !UrgentOrders.isEmpty())
	{
		if (mode != 2)
			pGUI->PrintMessage(BLACK, true, "TS:" + to_string(CurrentTimeStep) + " (Blue: VIP, Red: Normal, Green: Vegan, Orange: Urgent)");
		float A = rand() % 15;
		R_injured = float(A / 10);

		ExecuteEvents(CurrentTimeStep);

		CheckOnOrders(CurrentTimeStep, R_injured);

		CheckOnCooks(CurrentTimeStep);

		Check_injured_finshed(CurrentTimeStep);

		ServeVOrder(CurrentTimeStep);

		ServeGOrder(CurrentTimeStep);

		ServeNOrder(CurrentTimeStep);

		Move_To_Urgent(CurrentTimeStep);

		ServeURGOrder(CurrentTimeStep);

		AutoPromote(CurrentTimeStep);

		if (mode != 2)
		{
			pGUI->PrintMessage(BLUE, false, "Waiting Orders: Normal: " + to_string(NormalList.getcount()) + ", Vegan: " + to_string(VeganQueue.getcount()) + ", VIP: " + to_string(VIPQueue.getcount()) + "          Available Cooks: Normal: " + to_string(NC) + ", Vegan: " + to_string(GC) + ", VIP: " + to_string(VC));

			pGUI->PrintMessage(DARKRED, false, "Served Orders: Normal:" + to_string(SN) + +", Vegan:" + to_string(SG) + ", VIP:" + to_string(SV));

			FillDrawingList();

			pGUI->UpdateInterface();
		}
		CurrentTimeStep++;

		if (mode == 0)
			pGUI->waitForClick();
		if (mode == 1)
			Sleep(1000);
		if (mode != 2)
			pGUI->ResetDrawingList();
	}
	pGUI->PrintMessage(BLACK, true, "Simulation ended");
	Save();
	pGUI->waitForClick();
}




void Restaurant::AddtoVIPQueue(Order* pO, int p)
{
	VIPQueue.Insert(pO, p);
}

void Restaurant::AddtoNormalList(Order* pO)
{
	NormalList.InsertEnd(pO);
}

void Restaurant::RemovefromNormalList(Order* pO)
{
	NormalList.RemoveBeg(pO);
}

void Restaurant::AddtoVeganQueue(Order* pO)
{
	VeganQueue.enqueue(pO);
}


void Restaurant::Read()
{
	Order* pOrd;
	Event* pEv;
	pGUI->PrintMessage(BLACK, true, "Enter File Name to Read Data From");
	string filename = pGUI->GetString();
	ifstream InFile;
	InFile.open(filename + ".txt");
	while (!InFile.is_open())
	{
		pGUI->PrintMessage(BLACK, true, "File Doesn't Exist...Enter Another Name");
		filename = pGUI->GetString();
		InFile.open(filename + ".txt");
	}
	int N, G, V;
	int SN_min, SN_max;
	int SG_min, SG_max;
	int SV_min, SV_max;
	int BO;
	int BN_min, BN_max;
	int BG_min, BG_max;
	int BV_min, BV_max;
	int RstPrd;
	int AutoP, VIP_WT, M;
	char event_type;
	float InjProp;
	InFile >> N >> G >> V >> SN_min >> SN_max >> SG_min >> SG_max >> SV_min >> SV_max >> BO >> BN_min >> BN_max >> BG_min >> BG_max >> BV_min >> BV_max;
	InFile >> InjProp >> RstPrd >> AutoP >> VIP_WT >> M;
	setAP(AutoP);
	setVIP_WT(VIP_WT);
	setinjured_prop(InjProp);
	setnumcook(V, G, N);
	setCooks(N, V, G, BO, BN_min, BN_max, BV_min, BV_max, BG_min, BG_max, SV_min, SV_max, SN_min, SN_max, SG_min, SG_max, RstPrd);

	for (int i = 0; i < M; i++)
	{
		InFile >> event_type;
		switch (event_type)
		{
		case ('R'):
		{
			pEv = new ArrivalEvent;
			pEv->ReadData(InFile);
			EventsQueue.enqueue(pEv);
			break;
		}
		case ('X'):
		{
			pEv = new CancellationEvent;
			pEv->ReadData(InFile);
			EventsQueue.enqueue(pEv);
			break;
		}
		case ('P'):
		{
			pEv = new PromotionEvent;
			pEv->ReadData(InFile);
			EventsQueue.enqueue(pEv);
			break;
		}
		}
	}
}



void Restaurant::setnumcook(int V, int G, int N)
{
	TVIPCOOK = V;
	TVGNCOOK = G;
	TNRMCOOK = N;
}

void Restaurant::setCooks(int N, int V, int G, int BO, int BN_min, int BN_max, int BV_min, int BV_max, int BG_min, int BG_max, int SV_min, int SV_max, int SN_min, int SN_max, int SG_min, int SG_max, int RST)
{
	Cook* pC;

	NC = N;
	GC = G;
	VC = V;

	for (int i = 0; i < N; i++)
	{
		pC = new Cook;
		pC->setType(TYPE_NRM);
		pC->setID(i + 1);
		pC->setBO(BO);
		pC->setB(rand() % (BN_max - BN_min + 1) + BN_min);
		pC->setSpeed(rand() % (SN_max - SN_min + 1) + SN_min);
		pC->setRST(RST);
		AvailableCooks.InsertEnd(pC);
	}

	for (int i = N; i < (N + V); i++)
	{
		pC = new Cook;
		pC->setType(TYPE_VIP);
		pC->setID(i + 1);
		pC->setBO(BO);
		pC->setB(rand() % (BV_max - BV_min + 1) + BV_min);
		pC->setSpeed(rand() % (SV_max - SV_min + 1) + SV_min);
		pC->setRST(RST);
		AvailableCooks.InsertEnd(pC);
	}

	for (int i = (N + V); i < (N + V + G); i++)
	{
		pC = new Cook;
		pC->setType(TYPE_VGAN);
		pC->setID(i + 1);
		pC->setBO(BO);
		pC->setB(rand() % (BG_max - BG_min + 1) + BG_min);
		pC->setSpeed(rand() % (SG_max - SG_min + 1) + SG_min);
		pC->setRST(RST);
		AvailableCooks.InsertEnd(pC);
	}
}


void Restaurant::setAP(int a)
{
	AP = a > 0 ? a : 0;
}

void Restaurant::setVIP_WT(int a)
{
	VIP_W = a > 0 ? a : 0;
}

void Restaurant::setinjured_prop(float p)
{
	InjProp = p > 0 ? p : 0;
}


void Restaurant::DeleteFromNormalById(int id, Order*& pO)
{
	NormalList.DeleteById(id, pO);

}

void Restaurant::AutoPromote(int currTS)
{
	Order* pO = nullptr;
	int count = NormalList.getcount();
	for (int i = 0; i < count; i++)
	{
		if (!NormalList.isEmpty())
		{
			NormalList.RemoveBeg(pO);
			if (pO != nullptr && (currTS - pO->getAT()) >= AP)
			{
				pO->setType(TYPE_VIP);
				pO->setAT(currTS);
				VIPQueue.Insert(pO, pO->getpr());
				pGUI->PrintMessage(ROYALBLUE, false, to_string(pO->GetID()) + ": Auto-Promoted!");
				TotalP++;
				i--;
			}
			else NormalList.InsertEnd(pO);
		}
		else break;
	}
}


// ANOTHER IDEA FOR AUTOPROMOTION 

void Restaurant::AutoPromote_2(int currTS)
{
	List<Order*> ToBePromoted = NormalList.GetElementsAbove(currTS, AP);
	int count = ToBePromoted.getcount();
	Order* pO = nullptr;
	for (int i = 0; i < count; i++)
	{
		ToBePromoted.RemoveBeg(pO);
		pO->setType(TYPE_VIP);
		pO->setAT(currTS);
		VIPQueue.Insert(pO, pO->getpr());
		TotalP++;
	}
}

///////////////////////////////////////////////////// PHASE 2 FUNCTIONS /////////////////////////////////////////////////////////////

void Restaurant::GetCook(ORD_TYPE t, Cook*& pC)
{
	if (!AvailableCooks.isEmpty())
		if (AvailableCooks.DeleteByType(t, pC) == false)
			pC = nullptr;
}

void Restaurant::ServeVOrder(int TS)
{
	string cooktype;
	Cook* pC = nullptr;
	Order* pO = nullptr;
	while (!VIPQueue.isEmpty())
	{
		if (AvailableCooks.isEmpty())
			return;

		GetCook(TYPE_VIP, pC);
		VC--;
		cooktype = "V";
		if (pC == nullptr)
		{
			VC++;
			GetCook(TYPE_NRM, pC);
			NC--;
			cooktype = "N";
		}
		if (pC == nullptr)
		{
			NC++;
			GetCook(TYPE_VGAN, pC);
			cooktype = "G";
			GC--;
		}
		if (pC == nullptr)
		{
			GC++;
			return;
		}
		if (pC != nullptr)
		{
			VIPQueue.dequeue(pO);
			BusyCooks.enqueue(pC);
			pC->setOrder(pO);
			pO->setWT(TS - pO->getAT());
			pO->setST(ceil(float(pO->getSize()) / float(pC->getSpeed())));
			pO->setFT(pO->getAT() + pO->getST() + pO->getWT());
			pO->setStatus(SRV);
			InService.InsertEnd(pO);
			pGUI->PrintMessage(ROYALBLUE, false, cooktype + to_string(pC->getID()) + "(V" + to_string(pO->GetID()) + ")");
			pC = nullptr;
		}
	}
}

void Restaurant::ServeGOrder(int TS)
{
	Cook* pC = nullptr;
	Order* pO = nullptr;
	while (!VeganQueue.isEmpty())
	{
		if (AvailableCooks.isEmpty())
			return;

		GetCook(TYPE_VGAN, pC);
		GC--;
		if (pC == nullptr)
		{
			GC++;
			return;
		}
		if (pC != nullptr)
		{

			VeganQueue.dequeue(pO);
			BusyCooks.enqueue(pC);
			pC->setOrder(pO);
			pO->setWT(TS - pO->getAT());
			pO->setST(ceil(float(pO->getSize()) / float(pC->getSpeed())));
			pO->setFT(pO->getAT() + pO->getST() + pO->getWT());
			pO->setStatus(SRV);
			InService.InsertEnd(pO);
			pGUI->PrintMessage(DARKGREEN, false, "G" + to_string(pC->getID()) + "(G" + to_string(pO->GetID()) + ")");
			pC = nullptr;
		}
	}
}

void Restaurant::ServeNOrder(int TS)
{
	string cooktype;
	Cook* pC = nullptr;
	Order* pO = nullptr;
	int count = NormalList.getcount();
	while (!NormalList.isEmpty())
	{
		if (AvailableCooks.isEmpty())
			return;
		GetCook(TYPE_NRM, pC);
		NC--;
		cooktype = "N";
		if (pC == nullptr)
		{
			NC++;
			GetCook(TYPE_VIP, pC);
			VC--;
			cooktype = "V";
		}
		if (pC == nullptr)
		{
			VC++;
			return;
		}

		if (pC != nullptr)
		{
			NormalList.RemoveBeg(pO);

			BusyCooks.enqueue(pC);
			pC->setOrder(pO);
			pO->setWT(TS - pO->getAT());
			pO->setST(ceil(float(pO->getSize()) / float(pC->getSpeed())));
			pO->setFT(pO->getAT() + pO->getST() + pO->getWT());
			pO->setStatus(SRV);
			InService.InsertEnd(pO);
			pGUI->PrintMessage(RED, false, cooktype + to_string(pC->getID()) + "(N" + to_string(pO->GetID()) + ")");
			pC = nullptr;
		}
	}
}

void Restaurant::CheckOnOrders(int TS, float R_injured)
{
	bool firStvalid = true;  // thiS bolean to grantuee that i am going to take only one cook if injured 
	Cook* pC = nullptr;
	Order* pO = nullptr;
	int count = BusyCooks.getcount();
	for (int i = 0; i < count; i++)
	{
		if (!BusyCooks.isEmpty())
		{
			BusyCooks.dequeue(pC);
			if (pC != nullptr && (pC->getOrder() != nullptr) && pC->getOrder()->getFT() == TS)
			{
				pO = pC->getOrder();
				InService.DeleteById(pO->GetID(), pO);
				pO->setStatus(DONE);
				pC->setOrder(nullptr);
				Finished.enqueue(pO);

				switch (pO->GetType())  // number of served so far
				{
				case (TYPE_NRM):
				{
					SN++;
				}
				break;
				case (TYPE_VIP):
				{
					SV++;
				}
				break;
				case (TYPE_VGAN):
				{
					SG++;
				}
				break;
				}
				if (pC->getInj() == true)
				{
					pC->setInj_TS(TS);
					Injured_Cook.enqueue(pC);
				}

				if (pC->TakeBreak() == false && !pC->getInj())
				{
					AvailableCooks.InsertEnd(pC);
					switch (pC->getType())
					{
					case (TYPE_NRM):
					{
						NC++;
					}
					break;
					case (TYPE_VIP):
					{
						VC++;
					}
					break;
					case (TYPE_VGAN):
					{
						GC++;
					}
					break;
					}
					i--;
				}

				else if (!pC->getInj())
				{
					pC->setTS(TS);
					Cooks_OnBreak.enqueue(pC);
					pGUI->PrintMessage(BLACK, false, "Break: C" + to_string(pC->getID()));
				}

			}
			else
			{
				if (R_injured < InjProp && firStvalid)
				{
					if (!pC->getInj())
					{
						pC->setSpeed(pC->getSpeed() / 2);
						pC->setInj(true);
						// to know if injured before to keep count
						if (!pC->getInjuredB())
							Inj_Cooks++;
						pC->setInjuredB(true);
						firStvalid = false;
						pGUI->PrintMessage(BLACK, false, "Injured: C" + to_string(pC->getID()));
					}
				}
				BusyCooks.enqueue(pC);
			}

		}
		else break;
	}
}

void Restaurant::CheckOnCooks(int TS)
{
	Cook* pC = nullptr;
	int count = Cooks_OnBreak.getcount();
	for (int i = 0; i < count; i++)
	{
		if (!Cooks_OnBreak.isEmpty())
		{
			Cooks_OnBreak.dequeue(pC);
			if (pC->getBreak() == true && pC->EndBreak(TS) == true)
			{
				AvailableCooks.InsertEnd(pC);
				switch (pC->getType())
				{
				case (TYPE_NRM):
				{
					NC++;
				}
				break;
				case (TYPE_VIP):
				{
					VC++;
				}
				break;
				case (TYPE_VGAN):
				{
					GC++;
				}
				break;
				}
				i--;
			}
			else Cooks_OnBreak.enqueue(pC);
		}
		else break;
	}
}


void Restaurant::Move_To_Urgent(int TS)
{
	Queue<Order*> temp;
	int count = VIPQueue.getcount();
	Order* pO = nullptr;
	for (int i = 0; i < count; i++)
	{
		if (!VIPQueue.isEmpty())
		{
			VIPQueue.dequeue(pO);
			temp.enqueue(pO);
		}
		else break;
	}
	for (int i = 0; i < count; i++)
	{
		if (!temp.isEmpty())
		{
			temp.dequeue(pO);
			if (pO != nullptr && (TS - pO->getAT()) >= VIP_W)
			{
				UrgentOrders.enqueue(pO);
				pO->setURG(true);
				pGUI->PrintMessage(DARKORANGE, false, to_string(pO->GetID()) + ": To Urgent!");
				URG_Orders++;
				i--;
			}
			else VIPQueue.Insert(pO, pO->getpr());
		}
		else break;
	}
}



void Restaurant::ServeURGOrder(int TS)
{
	if (!UrgentOrders.isEmpty())
	{
		bool svip, snrm, sveg, sbreak, sinj;

		Order* pO = nullptr;

		Cook* pC = nullptr;

		while (!UrgentOrders.isEmpty())
		{
			if (Cooks_OnBreak.isEmpty() && Injured_Cook.isEmpty() && AvailableCooks.isEmpty())
				return;

			svip = true;
			snrm = true;
			sveg = true;
			sbreak = true;
			sinj = true;

			GetCook(TYPE_VIP, pC);
			if (pC != nullptr)
			{
				VC--;
				UrgentOrders.dequeue(pO);
				pC->setOrder(pO);
				pO->setWT(TS - pO->getAT());
				pO->setST(ceil(float(pO->getSize()) / float(pC->getSpeed())));
				pO->setFT(pO->getAT() + pO->getST() + pO->getWT());
				pO->setStatus(SRV);
				InService.InsertEnd(pO);
				BusyCooks.enqueue(pC);
				pGUI->PrintMessage(DARKORANGE, false, "URG " + to_string(pO->GetID()));
				svip = false;
				pC = nullptr;

			}

			if (svip)
			{
				GetCook(TYPE_NRM, pC);
				if (pC != nullptr)
				{
					NC--;
					UrgentOrders.dequeue(pO);
					pC->setOrder(pO);
					pO->setWT(TS - pO->getAT());
					pO->setST(ceil(float(pO->getSize()) / float(pC->getSpeed())));
					pO->setFT(pO->getAT() + pO->getST() + pO->getWT());
					pO->setStatus(SRV);
					InService.InsertEnd(pO);
					BusyCooks.enqueue(pC);
					pGUI->PrintMessage(DARKORANGE, false, "URG! " + to_string(pO->GetID()));
					snrm = false;
					svip = false;
					pC = nullptr;
				}

			}
			if (svip && snrm)
			{

				GetCook(TYPE_VGAN, pC);
				if (pC != nullptr)
				{
					GC--;
					UrgentOrders.dequeue(pO);
					pC->setOrder(pO);
					pO->setWT(TS - pO->getAT());
					pO->setST(ceil(float(pO->getSize()) / float(pC->getSpeed())));
					pO->setFT(pO->getAT() + pO->getST() + pO->getWT());
					pO->setStatus(SRV);
					InService.InsertEnd(pO);
					BusyCooks.enqueue(pC);
					pGUI->PrintMessage(DARKORANGE, false, "URG! " + to_string(pO->GetID()));
					snrm = false;
					svip = false;
					sveg = false;
					pC = nullptr;

				}

			}
			if (svip && snrm && sveg)
			{
				if (!Cooks_OnBreak.isEmpty())
				{
					Cooks_OnBreak.dequeue(pC);
					UrgentOrders.dequeue(pO);
					pC->setOrder(pO);
					pO->setWT(TS - pO->getAT());
					pO->setST(ceil(float(pO->getSize()) / float(pC->getSpeed())));
					pO->setFT(pO->getAT() + pO->getST() + pO->getWT());
					pO->setStatus(SRV);
					InService.InsertEnd(pO);
					BusyCooks.enqueue(pC);
					pGUI->PrintMessage(DARKORANGE, false, "URG! " + to_string(pO->GetID()));
					snrm = false;
					svip = false;
					sveg = false;
					sbreak = false;
					pC = nullptr;
				}
			}

			if (svip && snrm && sveg && sbreak)
			{
				if (!Injured_Cook.isEmpty())
				{
					Injured_Cook.dequeue(pC);
					UrgentOrders.dequeue(pO);
					pC->setOrder(pO);
					pC->setInj(false);
					pO->setWT(TS - pO->getAT());
					pO->setST(ceil(float(pO->getSize()) / float(pC->getSpeed())));
					pO->setFT(pO->getAT() + pO->getST() + pO->getWT());
					pO->setStatus(SRV);
					InService.InsertEnd(pO);
					BusyCooks.enqueue(pC);
					pGUI->PrintMessage(DARKORANGE, false, "URG! " + to_string(pO->GetID()));
					pC = nullptr;
				}
			}
		}
	}
}

void Restaurant::Save()
{
	QueueP <Order*> sorting;
	float percent = float(TotalP) / float(TotalN) * 100;
	int count = Finished.getcount();
	float wait = 0;
	float serv = 0;
	Order* pO = nullptr;
	Order* pO2 = nullptr;
	pGUI->PrintMessage(BLACK, true, "Enter the name of the file to save the data in");
	string name = pGUI->GetString();
	ofstream Output(name + ".txt");
	bool first = true;
	Output << "FT ID AT WT ST" << endl;


	while (!Finished.isEmpty())
	{
		first = true;

		if (!Finished.isEmpty())
			Finished.dequeue(pO2);
		if (pO && pO2)
		{
			while ((pO && pO2) && pO->getFT() == pO2->getFT())
			{
				if (first)
				{
					sorting.InsertAss(pO, pO->getST());
					first = false;

				}
				sorting.InsertAss(pO2, pO2->getST());
				if (!Finished.dequeue(pO2))
					pO2 = nullptr;
			}
		}

		while (!sorting.isEmpty())
		{
			sorting.dequeue(pO);
			wait += pO->getWT();
			serv += pO->getST();
			Output << pO->getFT() << "  " << pO->GetID() << "  " << pO->getAT() << "  " << pO->getWT() << "  " << pO->getST() << endl;
			delete pO;
			pO = nullptr;
		}
		if (sorting.isEmpty())
		{
			if (pO)
			{
				wait += pO->getWT();
				serv += pO->getST();
				Output << pO->getFT() << "  " << pO->GetID() << "  " << pO->getAT() << "  " << pO->getWT() << "  " << pO->getST() << endl;
				pO = nullptr;
			}
			pO = pO2;

		}
	}
	if (pO)
		Output << pO->getFT() << "  " << pO->GetID() << "  " << pO->getAT() << "  " << pO->getWT() << "  " << pO->getST() << endl;
	Output << endl;
	Output << "Orders: " << TotalG + TotalN + TotalV << " [Norm:" << TotalN << ", Veg:" << TotalG << ", VIP: " << TotalV << "]" << endl;
	Output << "Cooks: " << "[Norm:" << TNRMCOOK << ", Veg:" << TVGNCOOK << ", VIP: " << TVIPCOOK << ", INJ: " << Inj_Cooks << "]" << endl;
	Output << "Avg Wait = " << wait / count << ", Avg Serve=" << serv / count << endl;
	Output << "Urgent Order: " << URG_Orders << ", Auto-promoted " << percent << " %" << endl;
	Output.close();
	pGUI->PrintMessage(BLACK, true, "File Printed...Click to END");
	pGUI->waitForClick();

}


void Restaurant::Check_injured_finshed(int Ts)
{
	Cook* pC = nullptr;

	int count = Injured_Cook.getcount();

	for (int i = 0; i < count; i++)
	{
		if (!Injured_Cook.isEmpty())
		{
			Injured_Cook.dequeue(pC);
			if (Ts == (pC->getInj_TS() + pC->getRST()))
			{
				pC->setSpeed(pC->getSpeed() * 2);
				pC->setInj(false);
				pC->setInj_TS(0);
				AvailableCooks.InsertEnd(pC);
				switch (pC->getType())
				{
				case (TYPE_NRM):
				{
					NC++;
				}
				break;
				case (TYPE_VIP):
				{
					VC++;
				}
				break;
				case (TYPE_VGAN):
				{
					GC++;
				}
				break;
				}
				i--;
			}
			else
				Injured_Cook.enqueue(pC);
		}
		else break;
	}
}

void Restaurant::setTotalN(int num)
{
	TotalN = num;

}
int Restaurant::getTotalN()
{
	return TotalN;
}

void Restaurant::setTotalV(int num)
{
	TotalV = num;

}
int Restaurant::getTotalV()
{
	return TotalV;
}
void Restaurant::setTotalG(int num)
{
	TotalG = num;

}
int Restaurant::getTotalG()
{
	return TotalG;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////