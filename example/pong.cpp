#include <cRender.h>
#include <cObject.h>
#include <cObjectHandler.h>
#include <cInput.h>
#include <unistd.h>

class ball : public cObject
{
public:
  ball() : v({1,1}) { setSize(1,1); drawPoint('O', {0,0}, true, _COL_RED); }
  ~ball() { destruct(); }
  virtual bool onCollisionActive(sPos _hit, int _passiveObject)
  {
    if(_passiveObject == 1)
      v.y = v.y * (-1);
    else if (_passiveObject == 2)
      v.x = v.x * (-1);

    drawText(std::to_string(_passiveObject), {0,0}, _COL_GREEN);
    return true;
  }
  sPos getV() { return v; }
private:
  sPos v;

};

class bar : public cObject
{
public:
  bar() { setSize(1,5); drawLine('|', {0,0},{0,4}, true, _COL_BLUE);}
  ~bar() { destruct(); }
  virtual int onCollisionPassive(sPos _hit){ return 2; }
  virtual bool onCollisionActive(sPos _hit, int _passiveObject){ return true; }
};

class edge : public cObject
{
public:
  edge(unsigned int x, unsigned int y) { setSize(x,y); drawLine('#', {0,0},{x-1,y-1}, true, _COL_DEFAULT);}
  ~edge() { destruct(); }
  virtual int onCollisionPassive(sPos _hit)
  {
    if(getSize().x > getSize().y)
      return 1;
    else
      return 2;
  }
};

int main()
{
  cRender render(' ', _COL_DEFAULT, 10,10);
  cObjectHandler screen(&render);
  cInput input;

  bar barLeft;
  bar barRight;
  ball aball;
  edge edgeLeft(1,30);
  edge edgeRight(1,30);
  edge edgeTop(100,1);
  edge edgeBottom(100,1);

  int iEdgeTop = screen.createObject(&edgeTop);
  screen.moveObject(iEdgeTop, {0,0}, _MOVE_FORCE_ABSOLUTE);

  int iEdgeBottom = screen.createObject(&edgeBottom);
  screen.moveObject(iEdgeBottom, {0,30}, _MOVE_FORCE_ABSOLUTE);

  int iEdgeLeft = screen.createObject(&edgeLeft);
  screen.moveObject(iEdgeLeft, {0,0}, _MOVE_FORCE_ABSOLUTE);

  int iEdgeRight = screen.createObject(&edgeRight);
  screen.moveObject(iEdgeRight, {99,0}, _MOVE_FORCE_ABSOLUTE);

  int iAball= screen.createObject(&aball);
  screen.moveObject(iAball, {50,6}, _MOVE_FORCE_ABSOLUTE);

  unsigned int iBarLeft = screen.createObject(&barLeft);
  screen.moveObject(iBarLeft, {10,4}, _MOVE_FORCE_ABSOLUTE);

  unsigned int iBarRight = screen.createObject(&barRight);
  screen.moveObject(iBarRight, {90,4}, _MOVE_FORCE_ABSOLUTE);

  render.render();

  //printf ("%i %i %i %i %i", iEdgeTop, iEdgeBottom, iEdgeLeft, iEdgeRight, iAball);
  /*return 0;*/

  unsigned int cc = 0;

  while(1)
  {

    sInputEvent ie = input.poll();

		if(ie.type != _EVENT_NULL)
		{
			if(ie.type == _EVENT_KEY)
			{
				switch (ie.c)
				{
					case 'A'://up
						screen.moveObject(iBarRight, {0,-1}, _MOVE_RELATIVE);
						break;
					case 'B'://down
						screen.moveObject(iBarRight, {0,1}, _MOVE_RELATIVE);
						break;
				};
			}
			else if (ie.type == _EVENT_MOUSE)
			{
				if(ie.b == 0)
					screen.clickEvent({ie.x, ie.y}, 0);
			}
			else if (ie.type == _EVENT_CHAR)
			{
				//handler.charEvent(ie.c);
				switch(ie.c)
				{
					case 'w':
						screen.moveObject(iBarLeft, {0,-1}, _MOVE_RELATIVE);
						break;
					case 's':
						screen.moveObject(iBarLeft, {0,1}, _MOVE_RELATIVE);
            break;
				};
			}
			else if (ie.type == _EVENT_TERM)
			{
				return 0;
			}
    }
    if(!(++cc % 3))
      screen.moveObject(iAball, aball.getV(), _MOVE_RELATIVE);

    screen.write();
    render.render();

    usleep(50*1000);
  }

  return 0;
}
