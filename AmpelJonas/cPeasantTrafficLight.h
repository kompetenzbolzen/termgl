#pragma once
#include "stdafx.h"

#define _CTL_COL_RED 0
#define _CTL_COL_GREEN 1

//Counted clockwise, starting with the upper tl of west lane
#define _CTL_1 2
#define _CTL_2 1
#define _CTL_3 3
#define _CTL_4 4
#define _CTL_5 6
#define _CTL_6 5
#define _CTL_7 7
#define _CTL_8 8

class cPeasantTrafficLight
{
public:
	cPeasantTrafficLight(int _type, int _startphase);
	~cPeasantTrafficLight();

	void next();

	cObject *getObject();
private:
	cObject *tl;
	int iPhase;
	int iType;
};