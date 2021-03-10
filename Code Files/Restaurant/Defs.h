#ifndef __DEFS_H_
#define __DEFS_H_

enum ORD_TYPE
{
	TYPE_NRM,
	TYPE_VGAN,
	TYPE_VIP,
	TYPE_CNT

};

enum ORD_STATUS	
{
	WAIT,	
	SRV,	
	DONE,
	ORD_STATUS_CNT
};


enum PROG_MODE
{
	MODE_INTR,	
	MODE_STEP,
	MODE_SLNT,
	MODE_CNT
};


#define MaxPossibleOrdCnt 999
#define MaxPossibleMcCnt  100


#endif