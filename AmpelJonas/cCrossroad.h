#pragma once
#include "stdafx.h"

#define _SIZE_X_ 150
#define _SIZE_Y_ 50

class cCrossroad
{
public:
	cCrossroad(void);
	~cCrossroad(void);

	void run(void);
private:
	cRender *render;
	//cObjectHandler *handler;
};
