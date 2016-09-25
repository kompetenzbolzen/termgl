#include "cTrafficLight.h"

cTrafficLight::cTrafficLight(int _type, int _startphase)
{
	iPhase = _startphase - 1; //-1 because iPhase is incremented before switch statement
	iType = _type;
	if (_type == _TL_SOUTH_ ) {
		tl = new cObject(3, 5);
		tl->setPosition(_SIZE_X_ / 2 + 10, _SIZE_Y_ / 2 + 7);
		tl->drawRectangle('#', NULL, sPos{ 0,0 }, sPos{ 2,4 }, _COL_WHITE, NULL);
	}
	else if (_type == _TL_NORTH_) {
		tl = new cObject(3, 5);
		tl->setPosition(_SIZE_X_ / 2 - 11, _SIZE_Y_ / 2 - 11);
		tl->drawRectangle('#', NULL, sPos{ 0,0 }, sPos{ 2,4 }, _COL_WHITE, NULL);
	}
	else if (_type == _TL_EAST_) {
		tl = new cObject(5, 3);
		tl->setPosition(_SIZE_X_ / 2  + 10, _SIZE_Y_ / 2 - 9);
		tl->drawRectangle('#', NULL, sPos{ 0,0 }, sPos{ 4,2 }, _COL_WHITE, NULL);
	}
	else if (_type == _TL_WEST_) {
		tl = new cObject(5, 3);
		tl->setPosition(_SIZE_X_ / 2 - 13, _SIZE_Y_ / 2 + 7);
		tl->drawRectangle('#', NULL, sPos{ 0,0 }, sPos{ 4,2 }, _COL_WHITE, NULL);
	}

	next();
}

cTrafficLight::~cTrafficLight()
{
	delete tl;
}

void cTrafficLight::next()
{
	iPhase >= _TL_COL_RED_YELLOW_ ? iPhase = _TL_COL_GREEN_ : iPhase++;

	switch(iPhase)
	{
		case _TL_COL_GREEN_:
			if (iType == _TL_SOUTH_) {
				
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 1,2 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 1,3 }, true, _COL_GREEN);
			}
			else if (iType == _TL_NORTH_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_GREEN);
				tl->drawPoint('0', sPos{ 1,2 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 1,3 }, true, _COL_DEFAULT);
			}
			else if (iType == _TL_EAST_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 2,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 3,1 }, true, _COL_GREEN);
			}
			else if (iType == _TL_WEST_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_GREEN);
				tl->drawPoint('0', sPos{ 2,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 3,1 }, true, _COL_DEFAULT);
			}
			break;
		case _TL_COL_YELLOW_:
			if (iType == _TL_SOUTH_) {
				
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 1,2 }, true, _COL_YELLOW);
				tl->drawPoint('0', sPos{ 1,3 }, true, _COL_DEFAULT);
			}
			else if (iType == _TL_NORTH_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 1,2 }, true, _COL_YELLOW);
				tl->drawPoint('0', sPos{ 1,3 }, true, _COL_DEFAULT);
			}
			else if (iType == _TL_EAST_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 2,1 }, true, _COL_YELLOW);
				tl->drawPoint('0', sPos{ 3,1 }, true, _COL_DEFAULT);
			}
			else if (iType == _TL_WEST_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 2,1 }, true, _COL_YELLOW);
				tl->drawPoint('0', sPos{ 3,1 }, true, _COL_DEFAULT);
			}
			break;
		case _TL_COL_RED_:
			if (iType == _TL_SOUTH_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_RED);
				tl->drawPoint('0', sPos{ 1,2 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 1,3 }, true, _COL_DEFAULT);
			}
			else if (iType == _TL_NORTH_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 1,2 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 1,3 }, true, _COL_RED);
			}
			else if (iType == _TL_EAST_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_RED);
				tl->drawPoint('0', sPos{ 2,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 3,1 }, true, _COL_DEFAULT);
			}
			else if (iType == _TL_WEST_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 2,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 3,1 }, true, _COL_RED);
			}
			break;
		case _TL_COL_RED_YELLOW_:
			if (iType == _TL_SOUTH_) {
				
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_RED);
				tl->drawPoint('0', sPos{ 1,2 }, true, _COL_YELLOW);
				tl->drawPoint('0', sPos{ 1,3 }, true, _COL_DEFAULT);
			}
			else if (iType == _TL_NORTH_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 1,2 }, true, _COL_YELLOW);
				tl->drawPoint('0', sPos{ 1,3 }, true, _COL_RED);
			}
			else if (iType == _TL_EAST_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_RED);
				tl->drawPoint('0', sPos{ 2,1 }, true, _COL_YELLOW);
				tl->drawPoint('0', sPos{ 3,1 }, true, _COL_DEFAULT);
			}
			else if (iType == _TL_WEST_) {
				tl->drawPoint('0', sPos{ 1,1 }, true, _COL_DEFAULT);
				tl->drawPoint('0', sPos{ 2,1 }, true, _COL_YELLOW);
				tl->drawPoint('0', sPos{ 3,1 }, true, _COL_RED);
			}
			break;
	}
}

cObject *cTrafficLight::getObject()
{
	return tl;
}