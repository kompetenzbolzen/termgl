#pragma once
#include <stdlib.h>

#include "cRender.h"

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

	virtual ~cObject();

	sPos getPosition();

	void setPosition(sPos _pos);

	void setPosition(int _x, int _y);

	sObject getObject();

	virtual void onClick(sPos _pos, unsigned int _button){};

	virtual void onChar(unsigned char _c){};

protected: //For child classes
	cObject();

	void setSize(int _sx, int _sy);

	void destruct();

private:
	//wColor, cScreen, sizeX and sizeY are inherited from cRender
	sPos pos;
	bool bSizeSet;
};
