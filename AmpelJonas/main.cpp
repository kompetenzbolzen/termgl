#include <unistd.h>

#include "cRender.h"
#include "cObject.h"
#include "cObjectHandler.h"

int main()
{
	unsigned long int framecounter = 0;
	cRender a(' ', _COL_DEFAULT, 10,10);
	a.render();
	cObjectHandler b(&a);
	cObject x(1,1);

	int i = b.createObject(&x);
	int dir1 = 1;
	int dir2 = -1;
	int cntr = 0;

	a.clear(true);
	b.moveObject(i, {0,30}, _MOVE_ABSOULUTE);
	x.drawPoint('X', {0,0}, true,_COL_GREEN);

	while(1)
	{
		b.moveObject(i, {2 * dir1, 1 * dir2}, _MOVE_RELATIVE);

		b.write();
		a.drawText(to_string(framecounter), {0,0}, _COL_RED);
		a.render();

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

		framecounter++;
		//cin.get();
		usleep(100*1000);
		//for(unsigned int i = 0; i < 6000; i++)
			//for(unsigned int o = 0; o < 3000; o++);
	}
	return 0;
}
