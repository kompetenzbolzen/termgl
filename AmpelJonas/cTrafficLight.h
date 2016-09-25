#pragma once
#define _TL_SOUTH_ 0
#define _TL_NORTH_ 1
#define _TL_EAST_ 2
#define _TL_WEST_ 3

#define _TL_COL_GREEN_ 0
#define _TL_COL_YELLOW_ 1
#define _TL_COL_RED_ 2
#define _TL_COL_RED_YELLOW_ 3

#include "stdafx.h"

class cTrafficLight
{
public:
	cTrafficLight(int _type, int _startphase);
	~cTrafficLight();

	void next();

	cObject *getObject();
private:
	cObject *tl;
	int iPhase;
	int iType;
};