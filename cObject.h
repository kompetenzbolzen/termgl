#pragma once
#include <stdlib.h>

#include "cRender.h"

#define _HIT_TOP 1
#define _HIT_BOTTOM 2
#define _HIT_LEFT 3
#define _HIT_RIGHT 4

struct sObject
{
	sPos pos;
	WORD **wColor;
	char **cScreen;
	int sizeX;
	int sizeY;
};

/** cObject can be used standalone as well as inherited
* every cObject has its own framebuffer as well as position viariables to be moveable.
* cObject is used by cObjectHandler to manage all objects to be displayed.
*
* Minimal example for inheriting class
*
*
*			class example : cObject
*			{
*			public:
*				example() { setSize(10,5); }
*				~example() { destruct(); }
*			};
*
*/
class cObject : public cRender
{
public:
	/** Sets the size to _sx x _sy
	*/
	cObject(int _sx, int _sy);

	virtual ~cObject();

	/** Returns current position
	*/
	sPos getPosition();

	/** Sets position to _pos
	*/
	void setPosition(sPos _pos);
	/** Sets position by coordinates
	*/
	void setPosition(int _x, int _y);

	/** Returns sObject with framebuffer and current position
	*/
	sObject getObject();

	/** Called by cObjecthandler if cObject is clicked
	*/
	virtual void onClick(sPos _pos, unsigned int _button){}
	/** Called by cObjecthandler if cObject is active on keyboard input
	* _pos decribes the relative position of mousepointer to origin of object
	*/
	virtual void onChar(unsigned char _c){}


	/** Called by cObjectHandler if Object hits another during move operation
	*	return true to abort move, false to continue and allow overlap
	*/
	virtual bool onCollisionActive(unsigned int _hit, int _passiveObject) { return false; }

	/** Called by cObjectHandler if Object is hit by another object
	*	return any integer value to be identified by hitting object
	*/
	virtual int onCollisionPassive(unsigned int _hit) { return 0; }




protected: //For child classes
	cObject();
	/** For inheriting classes: sets size of framebuffer
	*/
	void setSize(int _sx, int _sy);

	/** For inheriting classes: frees the framebuffer
	*/
	void destruct();

private:
	//wColor, cScreen, sizeX and sizeY are inherited from cRender
	sPos pos;
	bool bSizeSet;
};
