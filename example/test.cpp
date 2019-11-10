
#include <termgl.h>

class ball : public cObject
{
public:
	ball() : v({1,1}) { setSize(1,1); drawPoint('O', {0,0}, _COL_RED); }
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

class edge : public cObject
{
public:
	edge(unsigned int x, unsigned int y) { setSize(x,y); drawLine('#', {0,0},{(int)x-1,(int)y-1}, _COL_DEFAULT);}
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
	cRender render(' ', _COL_DEFAULT);
	cObjectHandler screen(&render);
	cInput input;

	render.forceScreenSize({20,20});
	render.mute(true);

	ball aball;
	edge edgeLeft(1,10);
	edge edgeRight(1,10);
	edge edgeTop(10,1);
	edge edgeBottom(10,1);

	int iEdgeTop = screen.createObject(&edgeTop);
	screen.moveObject(iEdgeTop, {0,0}, _MOVE_FORCE_ABSOLUTE);

	int iEdgeBottom = screen.createObject(&edgeBottom);
	screen.moveObject(iEdgeBottom, {0,10}, _MOVE_FORCE_ABSOLUTE);

	int iEdgeLeft = screen.createObject(&edgeLeft);
	screen.moveObject(iEdgeLeft, {0,0}, _MOVE_FORCE_ABSOLUTE);

	int iEdgeRight = screen.createObject(&edgeRight);
	screen.moveObject(iEdgeRight, {9,0}, _MOVE_FORCE_ABSOLUTE);

	int iAball= screen.createObject(&aball);
	screen.moveObject(iAball, {2,2}, _MOVE_FORCE_ABSOLUTE);

	render.render();

	for(unsigned int cc = 0; cc < 9999; cc++)
	{

		sInputEvent ie = input.poll();

		if(ie.type != _EVENT_NULL)
		{
			if (ie.type == _EVENT_TERM)
			{
				return 0;
			}
		}

		if(!(++cc % 3))
			screen.moveObject(iAball, aball.getV(), _MOVE_RELATIVE);

		screen.write();
		render.render();
	}

	return 0;
}
