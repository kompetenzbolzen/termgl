#include <unistd.h>
#include <string>

#include "version.h"

#include "cRender.h"
#include "cObject.h"
#include "cObjectHandler.h"
#include "cInput.h"
#include "cWiremesh.h"

//#include "testobject.h"

class testobject : cObject
{
public:
  testobject()
  {
    setSize(10,5);
    cc = 0;
    kc = 0;

    drawRectangle('#', NULL, {0,0}, {9,4}, _COL_GREEN, _COL_DEFAULT);
  }

  ~testobject() { destruct(); }

  virtual void onClick(sPos _pos, unsigned int _button)
  {
    cc++;
    drawText(std::to_string(cc), {2,2}, _COL_RED);

    drawPoint('Q', _pos, _COL_YELLOW);
  }

  virtual bool onCollisionActive(sPos _hit, int _passiveObject){
    kc++;
    drawText(std::to_string(kc), {0,0},  _COL_RED);
    return true;
  }

	virtual void onChar(unsigned char _c) { drawPoint(_c, {1,1}, _COL_BLUE); }
private:
  int cc;
  int kc;
};

int main(int argc, char* argv[])
{
	cRender render(' ', _COL_DEFAULT, 30,30);
	cObjectHandler handler(&render);
	cObject ver(45,1);
	testobject obj2;

	cInput input;

	unsigned int framecounter = 0;
	bool loop = true;

	if(argc > 1)
	{
			loop = false;
	}

	render.render();

	ver.drawText(DATE, {20,0}, _COL_WHITE);
	ver.drawText(VERSTRING, {0,0}, _COL_WHITE);
	int iver = handler.createObject(&ver);
	handler.moveObject(iver, {0,0}, _MOVE_FORCE_ABSOLUTE);

	int iobj2 = handler.createObject((cObject*)&obj2);
	handler.moveObject(iobj2, {3,3}, _MOVE_FORCE_ABSOLUTE);

	sPos middle = render.getSize();
	middle.x /= 2;
	middle.y /= 2;

	while( loop )
	{
		sInputEvent ie = input.poll();

		if(ie.type != _EVENT_NULL)
		{
			if(ie.type == _EVENT_KEY)
			{
				switch (ie.c)
				{
					case 'A'://up
						handler.setCameraPosition({0,-1}, _MOVE_RELATIVE);
						break;
					case 'B'://down
						handler.setCameraPosition({0,1}, _MOVE_RELATIVE);
						break;
					case 'C'://right
						handler.setCameraPosition({1,0}, _MOVE_RELATIVE);
						break;
					case 'D'://left
						handler.setCameraPosition({-1,0}, _MOVE_RELATIVE);
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
						handler.moveObject(iobj2, {0,-1}, _MOVE_RELATIVE);
						break;
					case 's':
						handler.moveObject(iobj2, {0,1}, _MOVE_RELATIVE);
						break;
					case 'a':
						handler.moveObject(iobj2, {-1,0}, _MOVE_RELATIVE);
						break;
					case 'd':
						handler.moveObject(iobj2, {1,0}, _MOVE_RELATIVE);
						break;
				};
			}
			else if (ie.type == _EVENT_TERM)
			{
				return 0;
			}
		}

		handler.write();
		render.render();
		framecounter++;

		if(loop)
			usleep(10*1000);
	}

	return 0;
}
