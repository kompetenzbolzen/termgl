#include "cCar.h"

cCar::cCar(int _direction, int *_phase)
{
	pPhase = _phase;
	iDirection = _direction;
	if (iDirection ==_CAR_DIR_NORTH) { //South or north
		car = new cObject(4, 4);
		car->setPosition(_SIZE_X_ / 2 - 4, - 4 );
		car->drawRectangle('+', 'X', sPos{ 0,0 }, sPos{3,3}, _COL_RED, _COL_RED);
	}
	else if (iDirection == _CAR_DIR_SOUTH) { //South or north
		car = new cObject(4, 4);
		car->setPosition(_SIZE_X_ / 2 +1, _SIZE_Y_);
		car->drawRectangle('+', 'X', sPos{ 0,0 }, sPos{ 3,3 }, _COL_RED, _COL_RED);
	}
	else if(iDirection == _CAR_DIR_WEST){
		car = new cObject(6, 3);
		car->setPosition( -6, _SIZE_Y_ / 2 + 1);
		car->drawRectangle('+', ' ', sPos{ 0,0 }, sPos{5, 2}, _COL_BLUE, _COL_BLUE);
		car->drawText("AUTO", sPos{ 1,1 }, _COL_BLUE);
	}
	else if (iDirection == _CAR_DIR_EAST)
	{
		car = new cObject(6, 3);
		car->setPosition(_SIZE_X_, _SIZE_Y_ / 2 -3);
		car->drawRectangle('+', ' ', sPos{ 0,0 }, sPos{ 5, 2 }, _COL_BLUE, _COL_BLUE);
		car->drawText("AUTO", sPos{ 1,1 }, _COL_BLUE);
	}
}

cCar::~cCar()
{
	delete car;
}

cObject *cCar::getObject()
{
	return car;
}

void cCar::drive()
{
	sPos oldPos;
	switch(iDirection)
	{
	case _CAR_DIR_EAST:
		oldPos = car->getPosition();
		if (!((*pPhase != 5 && *pPhase != 4) && oldPos.x == (_SIZE_X_ / 2) + 11)){
			car->setPosition(oldPos.x - 1, oldPos.y);
		}
		if (oldPos.x < -6) {
			car->setPosition(_SIZE_X_, oldPos.y);
		}
		break;
	case _CAR_DIR_WEST:
		oldPos = car->getPosition();
		if (!((*pPhase != 5 && *pPhase != 4) && oldPos.x == (_SIZE_X_ / 2) - 15)){
			car->setPosition(oldPos.x + 1, oldPos.y);
		}
		if (oldPos.x > _SIZE_X_) {
			car->setPosition(-6 , oldPos.y);
		}
		break;
	case _CAR_DIR_NORTH:
		oldPos = car->getPosition();
		if (!((*pPhase != 0 && *pPhase != 9 && *pPhase != -1) && oldPos.y == (_SIZE_Y_ / 2) - 11)) {
			car->setPosition(oldPos.x, oldPos.y + 1);
		}
		if (oldPos.y > _SIZE_Y_) {
			car->setPosition(oldPos.x, -4);
		}
		break;
	case _CAR_DIR_SOUTH:
		oldPos = car->getPosition();
		if (!((*pPhase != 0 && *pPhase != 9 && *pPhase != -1) && oldPos.y == (_SIZE_Y_ / 2) + 8)) {
			car->setPosition(oldPos.x, oldPos.y - 1);
		}
		if (oldPos.y < -4) {
			car->setPosition(oldPos.x, _SIZE_Y_);
		}
		break;
	}
}