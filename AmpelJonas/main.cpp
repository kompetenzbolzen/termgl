#include "stdafx.h"

int main()
{
	cCrossroad *crossroad;
	crossroad = new cCrossroad;
	crossroad->run();
	delete crossroad;

	cout << endl;
	cin.get();

	return 0;
}
