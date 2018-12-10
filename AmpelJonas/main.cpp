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
		//usleep(10*1000);

		if(x.getPosition().x <= 0 || x.getPosition().x >= a.getSize().x - 1)
			dir1 *= -1;
		if(x.getPosition().y <= 0 || x.getPosition().y >= a.getSize().y)
			dir2 *= -1;
	}

	a.render();
	return 0;
}
