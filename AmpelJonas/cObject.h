#pragma once
#include "stdafx.h"

struct sObject 

{
	sPos pos;
	WORD **wColor;
	char **cScreen;
	int sizeX;
	int sizeY;
};

class cObject : public cRender
{
public:
	cObject(int _sx, int _sy);
	//_sx : SizeX
	//_sy : SizeY
	~cObject();

	sPos getPosition();
	void setPosition(sPos _pos);
	void setPosition(int _x, int _y);
	sObject getObject();

private:
	//wColor, cScreen, sizeX and sizeY are inherited from cRender
	sPos pos;
	
};

