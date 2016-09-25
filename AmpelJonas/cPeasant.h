#pragma once
#include "stdafx.h"

#define _PE_DIR_NORTH 0
#define _PE_DIR_WEST 1

class cPeasant
{
public:
	cPeasant(int _direction, int *_phase);
	~cPeasant();

	cObject *getObject();

	void run();
private:
	cObject *pe;
	int iDirection;
	int *pPhase;
};