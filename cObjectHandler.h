#pragma once

#include <vector>

#include "cObject.h"

//movemodes
#define _MOVE_RELATIVE	0
#define _MOVE_ABSOULUTE	1

using namespace std;

class cObject; //Circular dependency break (Bad practice. I Know.)

class cObjectHandler
{
public:
	cObjectHandler(cRender *_render);

	int createObject(cObject *_object);
	//Adds _object to managed objects vector
	//returns Identifier for newly created vector

	int moveObject(int _object, sPos _pos, int _mode);
	//Alters position of _object by _pos either relative to old position or Absolute
	//Depending on selected _mode (_MOVE_RELATIVE / _MOVE_ABSOLUTE).

	int destroyObject(int _object);
	//removes _object from vector after deleting it

	int write();
	//writes all objects in objects[] to render buffer

	int clickEvent(sPos _pos, unsigned int _button);
	//Calls onClick of cObject at _pos, focuses Object
	//returns 0 if successfull, 1 if Object is empty

	int charEvent(unsigned char _c);
	//Calls onChar of active cObject, default 0
	//returns 0 if successfull, 1 if focused Object is empty

	void focusNext();
	//Focuses next Object

	void focus(unsigned int _id);
	//Focuses specific Object

private:
	void buildHitmap();

	vector<cObject*> objects;
	vector<vector<unsigned int>> iHitMap;
	cRender *render;
	unsigned long int iActiveObject;
};
