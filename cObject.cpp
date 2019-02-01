#include "cObject.h"

cObject::cObject(int _sx, int _sy)
{
	bSizeSet = false;

	pos = {0,0};
	setSize(_sx, _sy);
}

cObject::~cObject()
{
	destruct();
}

sPos cObject::getPosition()
{
	return pos;
}

void cObject::setPosition(sPos _pos)
{
	pos = _pos;
}


void cObject::setPosition(int _x, int _y)
{
	pos.x = _x;
	pos.y = _y;
}


sObject cObject::getObject()
{
	return sObject{pos, wColor, cScreen, sizeX, sizeY};
}

//protected
cObject::cObject()
{
	bSizeSet = false;
}

void cObject::setSize(int _sx, int _sy)
{
	if(bSizeSet)
		return;

	bBlockRender = true; //Block inherited render capabilities of parent

	sizeX = _sx;
	sizeY = _sy;

	//Initialize 2D array
	cScreen = (char**) malloc(sizeof *cScreen * _sx);
	for (int i = 0; i < _sx; i++)
		cScreen[i] = (char*)malloc(sizeof *cScreen[i] * _sy);

	wColor = (WORD**)malloc(sizeof *wColor * _sx);
	for (int i = 0; i < _sx; i++)
		wColor[i] = (WORD*)malloc(sizeof *wColor[i] * _sy);

	for (int i = 0; i < sizeY; i++) {
		for (int o = 0; o < sizeX; o++) {
			cScreen[o][i] = NULL;
			wColor[o][i] = _COL_DEFAULT;
		}
	}

	bSizeSet = true;
}

void cObject::destruct()
{
	if(!bSizeSet)
		return;

	for (int i = 0; i < sizeX; i++) {
		free(cScreen[i]);
		free(wColor[i]);
	}

	free(cScreen);
	free(wColor);

	bSizeSet = false;
}
