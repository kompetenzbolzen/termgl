#include "cPeasantTrafficLight.h"

cPeasantTrafficLight::cPeasantTrafficLight(int _type, int _startphase)
{
	iPhase = _startphase;
	iPhase == _CTL_COL_GREEN ? iPhase = _CTL_COL_RED : iPhase = _CTL_COL_GREEN; //switch arround bc switch occurs before lights are switched
	iType = _type;

	_type % 2 == 0 ? tl = new cObject(1, 2) : tl = new cObject(2, 1);

	//tl->setPosition(_SIZE_X_ / 2, _SIZE_Y_ / 2);

	switch (_type)
	{
	case _CTL_1:
		tl->setPosition(_SIZE_X_ / 2 - 9, _SIZE_Y_ / 2 - 6);
		break;
	case _CTL_4:
		tl->setPosition(_SIZE_X_ / 2 + 10, _SIZE_Y_ / 2 - 6);
		break;
	case _CTL_5:
		tl->setPosition(_SIZE_X_ / 2 + 10, _SIZE_Y_ / 2 + 5);
		break;
	case _CTL_8:
		tl->setPosition(_SIZE_X_ / 2 - 9, _SIZE_Y_ / 2 + 5);
		break;
	case _CTL_2:
		tl->setPosition(_SIZE_X_ / 2 - 8, _SIZE_Y_ / 2 - 7);
		break;
	case _CTL_3:
		tl->setPosition(_SIZE_X_ / 2 + 7, _SIZE_Y_ / 2 - 7);
		break;
	case _CTL_6:
		tl->setPosition(_SIZE_X_ / 2 + 7, _SIZE_Y_ / 2 + 7);
		break;
	case _CTL_7:
		tl->setPosition(_SIZE_X_ / 2 - 8, _SIZE_Y_ / 2 + 7);
		break;
	}

	next();
}

cPeasantTrafficLight::~cPeasantTrafficLight()
{
	delete tl;
}

void cPeasantTrafficLight::next()
{
	iPhase == _CTL_COL_GREEN ? iPhase = _CTL_COL_RED : iPhase = _CTL_COL_GREEN;
	switch (iType)
	{
	case _CTL_1:
	case _CTL_4:
		tl->drawPoint('o', sPos{ 0,0 }, true, _COL_DEFAULT);
		tl->drawPoint('o', sPos{ 0,1 }, true, _COL_DEFAULT);
		iPhase == _CTL_COL_GREEN ? tl->drawPoint('o', sPos{ 0,1 }, true, _COL_GREEN) : tl->drawPoint('o', sPos{ 0,0 }, true, _COL_RED);
		break;
	case _CTL_5:
	case _CTL_8:
		tl->drawPoint('o', sPos{ 0,0 }, true, _COL_DEFAULT);
		tl->drawPoint('o', sPos{ 0,1 }, true, _COL_DEFAULT);
		iPhase == _CTL_COL_GREEN ? tl->drawPoint('o', sPos{ 0,0 }, true, _COL_GREEN) : tl->drawPoint('o', sPos{ 0,1 }, true, _COL_RED);
		break;
	case _CTL_2:
	case _CTL_7:
		tl->drawPoint('o', sPos{ 0,0 }, true, _COL_DEFAULT);
		tl->drawPoint('o', sPos{ 1,0 }, true, _COL_DEFAULT);
		iPhase == _CTL_COL_GREEN ? tl->drawPoint('o', sPos{ 1,0 }, true, _COL_GREEN) : tl->drawPoint('o', sPos{ 0,0 }, true, _COL_RED);
		break;
	case _CTL_6:
	case _CTL_3:
		tl->drawPoint('o', sPos{ 0,0 }, true, _COL_DEFAULT);
		tl->drawPoint('o', sPos{ 1,0 }, true, _COL_DEFAULT);
		iPhase == _CTL_COL_GREEN ? tl->drawPoint('o', sPos{ 0,0 }, true, _COL_GREEN) : tl->drawPoint('o', sPos{ 1,0 }, true, _COL_RED);
		break;
	}
}

cObject *cPeasantTrafficLight::getObject()
{
	return tl;
}