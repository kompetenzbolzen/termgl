#pragma once
#include "stdafx.h"

#define _CAR_DIR_SOUTH 2
#define _CAR_DIR_NORTH 4
#define _CAR_DIR_EAST 1
#define _CAR_DIR_WEST 3

class cCar
{
public:
	cCar(int _direction, int *_phase);
	~cCar();

	cObject *getObject();

	void drive();
private:
	cObject *car;
	int iDirection;
	int *pPhase;
};