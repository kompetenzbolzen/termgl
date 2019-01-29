#include <unistd.h>
#include <string>

#include "version.h"

#include "cRender.h"
#include "cObject.h"
#include "cObjectHandler.h"
#include "cInput.h"
#include "cWiremesh.h"

//#include "testobject.h"

int main(int argc, char* argv[])
{
	cRender render(' ', _COL_DEFAULT, 30,30);
	cObjectHandler handler(&render);
	cObject ver(45,1);
	cWiremesh obj;

	cInput input;

	unsigned int framecounter = 0;
	bool loop = true;

	if(argc > 1)
	{
			loop = false;
	}

	render.render();

	ver.drawPoint('v', {0,0}, true, _COL_WHITE);
	ver.drawPoint(VERSION + 48, {1,0}, true, _COL_WHITE);
	ver.drawPoint('.', {2,0}, true, _COL_WHITE);
	ver.drawPoint(PATCHLEVEL + 48, {3,0}, true, _COL_WHITE);
	ver.drawText(DATE, {32,0}, _COL_WHITE);
	ver.drawText(BRANCH, {5,0}, _COL_WHITE);
	int iver = handler.createObject(&ver);
	handler.moveObject(iver, {0,0}, _MOVE_ABSOLUTE);

	int x = 15;
	int y = 15;
	int z = 30;

	obj.addVector({-x,-y,z}, {2*x,0,0}, '+', _COL_RED);
	obj.addVector({-x,-y,z}, {0,2*y,0}, '+', _COL_RED);
	obj.addVector({-x,y,z}, {2*x,0,0}, '+', _COL_RED);
	obj.addVector({x,-y,z}, {0,2*y,0}, '+', _COL_RED);

	obj.addVector({-x,-y,0}, {0,0,z}, ':', _COL_RED);
	obj.addVector({x,-y,0}, {0,0,z}, ':', _COL_RED);
	obj.addVector({-x,y,0}, {0,0,z}, ':', _COL_RED);
	obj.addVector({x,y,0}, {0,0,z}, ':', _COL_RED);

	obj.addVector({-x,-y,0}, {2*x,0,0}, ',', _COL_RED);
	obj.addVector({-x,-y,0}, {0,2*y,0}, ',', _COL_RED);
	obj.addVector({-x,y,0}, {2*x,0,0}, ',', _COL_RED);
	obj.addVector({x,-x,0}, {0,2*y,0}, ',', _COL_RED);
	int imesh = handler.createWiremesh(&obj);

	sPos middle = render.getSize();
	middle.x /= 2;
	middle.y /= 2;

	handler.moveWiremesh(imesh,{middle.x,middle.y,0}, _MOVE_ABSOLUTE);

	while( loop || framecounter < 1000)
	{
		sInputEvent ie = input.poll();

		if(ie.type != _EVENT_NULL)
		{
			if(ie.type == _EVENT_KEY)
			{
				switch (ie.c)
				{
					case 'A'://up
						handler.moveWiremesh(imesh,{0,-1,0}, _MOVE_RELATIVE);
						break;
					case 'B'://down
						handler.moveWiremesh(imesh,{0,1,0}, _MOVE_RELATIVE);
						break;
					case 'C'://right
						handler.moveWiremesh(imesh,{1,0,0}, _MOVE_RELATIVE);
						break;
					case 'D'://left
						handler.moveWiremesh(imesh,{-1,0,0}, _MOVE_RELATIVE);
						break;
				};
			}
			else if (ie.type == _EVENT_MOUSE)
			{
				if(ie.b == 0)
					handler.clickEvent({ie.x, ie.y}, 0);
			}
			else if (ie.type == _EVENT_CHAR)
			{
				//handler.charEvent(ie.c);
				switch(ie.c)
				{
					case 'w':
						handler.rotateWiremesh(imesh,{-10,0,0});
						break;
					case 's':
						handler.rotateWiremesh(imesh,{10,0,0});
						break;
					case 'a':
						handler.rotateWiremesh(imesh,{0,-10,0});
						break;
					case 'd':
						handler.rotateWiremesh(imesh,{0,10,0});
						break;
					case 'q':
						handler.rotateWiremesh(imesh,{0,0,-10});
						break;
					case 'e':
						handler.rotateWiremesh(imesh,{0,0,10});
						break;
				};
			}
			else if (ie.type == _EVENT_TERM)
			{
				return 0;
			}
		}

		handler.rotateWiremesh(imesh,{1,1,1});

		handler.write();
		render.render();
		framecounter++;

		if(loop)
			usleep(10*1000);
	}

	return 0;
}
