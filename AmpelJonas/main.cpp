#include <unistd.h>

#include "cRender.h"
#include "cObject.h"
#include "cObjectHandler.h"

int main()
{
	cRender a(' ', _COL_DEFAULT, 10,10);
	cObjectHandler b(&a);
	cObject x(1,1);

	int i = b.createObject(&x);
	int dir1 = 1;
	int dir2 = -1;
	int cntr = 0;

	b.moveObject(i, {0,30}, _MOVE_ABSOULUTE);
	x.drawPoint('X', {0,0}, true,_COL_GREEN);
	while(1)
	{
		b.moveObject(i, {2 * dir1, 1 * dir2}, _MOVE_RELATIVE);

		b.write();
		a.render();
		usleep(10*1000);

		if(x.getPosition().x <= 0)
			dir1 *= -1;
		else if(x.getPosition().x >= a.getSize().x)
		{
			dir1 *= -1;
			x.setPosition({a.getSize().x, x.getPosition().y});
		}

		if(x.getPosition().y <= 0)
			dir2 *= -1;
		else if(x.getPosition().y >= a.getSize().y)
		{
			dir2 *= -1;
			x.setPosition({x.getPosition().x, a.getSize().y});
		}
	}

	a.render();
	return 0;
}
