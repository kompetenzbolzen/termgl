#include "cPeasant.h"

cPeasant::cPeasant(int _direction, int *_phase)
{
	pPhase = _phase;
	iDirection = _direction;
	pe = new cObject(1, 1);
	pe->drawPoint(203, sPos{0,0}, true, _COL_YELLOW);

	switch (iDirection)
	{
	case _PE_DIR_NORTH:
		pe->setPosition(_SIZE_X_ / 2 - 7, -1);
		break;
	case _PE_DIR_WEST:
		pe->setPosition(-1, _SIZE_Y_ / 2 - 5);
		break;
	}
}

cPeasant::~cPeasant()
{
	delete pe;
}

cObject *cPeasant::getObject()
{
	return pe;
}

void cPeasant::run()
{
	sPos oldPos = pe->getPosition();
	switch (iDirection)
	{
	case _PE_DIR_NORTH:
		if(!(oldPos.y == _SIZE_Y_ / 2 - 5 && *pPhase != -1))
			pe->setPosition(oldPos.x, oldPos.y + 1);

		if(oldPos.y > _SIZE_Y_)
			pe->setPosition(oldPos.x, -1);
		break;
	case _PE_DIR_WEST:
		if (!(oldPos.x == _SIZE_X_ / 2 - 7 && *pPhase != 4))
			pe->setPosition(oldPos.x + 1, oldPos.y);

		if(oldPos.x > _SIZE_X_)
			pe->setPosition(-1, oldPos.y);
		break;
	}
}