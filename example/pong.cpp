#include <cRender.h>
#include <cObject.h>
#include <cObjectHandler.h>
#include <cInput.h>
#include <unistd.h>

class ball : public cObject
{
public:
  ball() : v({1,1}), cc(0) { setSize(1,1); drawPoint('O', {0,0}, true, _COL_RED); }
  ~ball() { destruct(); }
  virtual bool onCollisionActive(sPos _hit, int _passiveObject)
  {
    if(_passiveObject == 1)
      v.y = v.y * (-1);
    else if (_passiveObject == 2)
      v.x = v.x * (-1);
    cc++;
    drawText(std::to_string(_passiveObject), {0,0}, _COL_GREEN);
    return true;
  }
  sPos getV() { return v; }
private:
  sPos v;
  int cc;
};

class bar : public cObject
{
public:
  bar() { setSize(1,5); drawLine('|', {0,0},{0,4}, true, _COL_BLUE);}
  ~bar() { destruct(); }
  virtual int onCollisionPassive(){ return 2; }
};

class edges : public cObject
{
public:
  edges() { setSize(1,20); drawLine('#', {0,0},{0,19}, true, _COL_DEFAULT);}
  ~edges() { destruct(); }
  virtual int onCollisionPassive(sPos _hit)
  {
    if(getSize().x > getSize().y)
      return 1;
    else
      return 2;
  }
};

class edget : public cObject
{
public:
  edget() { setSize(40,1); drawLine('#', {0,0},{39, 0}, true, _COL_DEFAULT);}
  ~edget() { destruct(); }
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

  //bar barLeft, barRight;
  ball aball;
  edges edgeLeft;
  edges edgeRight;
  edget edgeTop;
  edget edgeBottom;

  int iEdgeTop = screen.createObject(&edgeTop);
  screen.moveObject(iEdgeTop, {2,0}, _MOVE_FORCE_ABSOLUTE);

  int iEdgeBottom = screen.createObject(&edgeBottom);
  screen.moveObject(iEdgeBottom, {0,21}, _MOVE_FORCE_ABSOLUTE);

  int iEdgeLeft = screen.createObject(&edgeLeft);
  screen.moveObject(iEdgeLeft, {0,0}, _MOVE_FORCE_ABSOLUTE);

  int iEdgeRight = screen.createObject(&edgeRight);
  screen.moveObject(iEdgeRight, {43,0}, _MOVE_FORCE_ABSOLUTE);


  int iAball= screen.createObject(&aball);
  screen.moveObject(iAball, {9,6}, _MOVE_FORCE_ABSOLUTE);

  render.render();

  //printf ("%i %i %i %i %i", iEdgeTop, iEdgeBottom, iEdgeLeft, iEdgeRight, iAball);
  /*return 0;*/

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
						//handler.setCameraPosition({0,-1}, _MOVE_RELATIVE);
						break;
					case 'B'://down
						//handler.setCameraPosition({0,1}, _MOVE_RELATIVE);
						break;
				};
			}
			else if (ie.type == _EVENT_MOUSE)
			{
				if(ie.b == 0);
					//handler.clickEvent({ie.x, ie.y}, 0);
			}
			else if (ie.type == _EVENT_CHAR)
			{
				//handler.charEvent(ie.c);
				switch(ie.c)
				{
					case 'w':
						//handler.moveObject(iobj2, {0,-1}, _MOVE_RELATIVE);
						break;
					case 's':
						//handler.moveObject(iobj2, {0,1ngine (the most creative name I could come up with)}, _MOVE_RELATIVE);
            break;
				};
			}
			else if (ie.type == _EVENT_TERM)
			{
				return 0;
			}
    }

    //screen.moveObject(iAball, aball.getV(), _MOVE_RELATIVE);

    screen.write();
    render.render();

    usleep(50*1000);
  }

  return 0;
}
