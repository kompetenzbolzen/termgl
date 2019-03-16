#include "cObject.h"

cObject::cObject(int _sx, int _sy)  : pos({0,0}) , bSizeSet(false)
{
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

void cObject::write(cRender *_render, sPos _cameraPosition)
{
	if(!bSizeSet)
		return;

	for (unsigned int o = 0; o < sizeY; o++) { //y axis
		for (unsigned int p = 0; p < sizeX; p++) { //x axis
			if (cScreen[p][o]) { //Dont overwrite empty pixels
				sPos npos{ pos.x + (int)p - _cameraPosition.x,
									pos.y + (int)o - _cameraPosition.y };
				_render->drawPoint(cScreen[p][o], npos, wColor[p][o]);
			}
		}
	}
}

//protected
cObject::cObject() : pos({0,0}) , bSizeSet(false){}

void cObject::setSize(unsigned int _sx, unsigned int _sy)
{
	if(bSizeSet)
		return;

	bBlockRender = true; //Block inherited render capabilities of parent

	sizeX = _sx;
	sizeY = _sy;

	//Initialize 2D array
	cScreen = (char**) malloc(sizeof *cScreen * _sx);
	for (unsigned int i = 0; i < _sx; i++)
		cScreen[i] = (char*)malloc(sizeof *cScreen[i] * _sy);

	wColor = (WORD**)malloc(sizeof *wColor * _sx);
	for (unsigned int i = 0; i < _sx; i++)
		wColor[i] = (WORD*)malloc(sizeof *wColor[i] * _sy);

	for (unsigned int i = 0; i < sizeY; i++) {
		for (unsigned int o = 0; o < sizeX; o++) {
			cScreen[o][i] = 0;
			wColor[o][i] = _COL_DEFAULT;
		}
	}

	bSizeSet = true;
}

void cObject::destruct()
{
	if(!bSizeSet)
		return;

	for (unsigned int i = 0; i < sizeX; i++) {
		free(cScreen[i]);
		free(wColor[i]);
	}

	free(cScreen);
	free(wColor);

	bSizeSet = false;
}
