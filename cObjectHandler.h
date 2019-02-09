#pragma once

#include <vector>

#include "cObject.h"
#include "cWiremesh.h"

//movemodes
#define _MOVE_RELATIVE	0
#define _MOVE_ABSOLUTE	1

using namespace std;


/**
* Manages cObject and cWiremesh and writes them to a cRender framebuffer.
* forwards input events to corresponding cObject.
*/
class cObjectHandler
{
public:
	/**
	* *_render: pointer to instance of cRender all objects will be written to
	*/
	explicit cObjectHandler(cRender *_render);

	/**
	* Adds _object to managed objects vector
	* returns Identifier for newly created vector
	*/
	int createObject(cObject *_object);

	/**
	* Alters position of _object by _pos either relative to old position or Absolute
	* Depending on selected _mode (_MOVE_RELATIVE / _MOVE_ABSOLUTE).
	*/
	int moveObject(int _object, sPos _pos, int _mode);

 /**
 * removes _object from vector after deleting it
 */
	int destroyObject(int _object);

	/**
	* Analog to createObject()
	*/
	int createWiremesh(cWiremesh *_mesh);

	int moveWiremesh(int _mesh, sCoord3d _pos, int _mode);

	int rotateWiremesh(int _mesh, sCoord3d _angle);

	int destroyWiremesh(int _mesh);


	/**
	* writes all objects in objects[] to render buffer
	*/
	int write();


	/**
	* Calls onClick of cObject at _pos, focuses Object
	* returns 0 if successfull, 1 if no Object is at _pos
	*/
	int clickEvent(sPos _pos, unsigned int _button);

	/**
	* Calls onChar of active cObject, default 0
	* returns 0 if successfull, 1 if no Object or destroyed Object is empty
	*/
	int charEvent(unsigned char _c);

	/**
	* Focuses next Object
	*/
	void focusNext();

	/**
	* Focuses Object by id.
	* 0 is empty by default and can be used to unfocus
	*/
	void focus(unsigned int _id);


private:
	void buildHitmap();

	vector<cObject*> objects;
	vector<cWiremesh*> meshes;
	vector< vector<unsigned int> > iHitMap;
	cRender *render;
	unsigned long int iActiveObject;
};
