#include "cCrossroad.h"

cCrossroad::cCrossroad()
{
	render = new cRender(' ', _COL_GREEN, _SIZE_X_, _SIZE_Y_);
	//handler = new cObjectHandler(render);
}

cCrossroad::~cCrossroad()
{
	delete render;
	//delete handler;
}

void cCrossroad::run()
{
	int iWait = 4;
	int iPhase = -1;
	int iFrames = 0;

	cObjectHandler handler(render);
	cObject *backround = new cObject(_SIZE_X_, _SIZE_Y_);

	//Objects
	cTrafficLight tlNorth(_TL_NORTH_, _TL_COL_GREEN_);
	cTrafficLight tlSouth(_TL_SOUTH_, _TL_COL_GREEN_);
	cTrafficLight tlEast(_TL_EAST_, _TL_COL_RED_);
	cTrafficLight tlWest(_TL_WEST_, _TL_COL_RED_);

	cPeasantTrafficLight ptl1(_CTL_1, _CTL_COL_GREEN);
	cPeasantTrafficLight ptl2(_CTL_2, _CTL_COL_RED);
	cPeasantTrafficLight ptl3(_CTL_3, _CTL_COL_RED);
	cPeasantTrafficLight ptl4(_CTL_4, _CTL_COL_GREEN);
	cPeasantTrafficLight ptl5(_CTL_5, _CTL_COL_GREEN);
	cPeasantTrafficLight ptl6(_CTL_6, _CTL_COL_RED);
	cPeasantTrafficLight ptl7(_CTL_7, _CTL_COL_RED);
	cPeasantTrafficLight ptl8(_CTL_8, _CTL_COL_GREEN);

	cCar carSouth(_CAR_DIR_SOUTH, &iPhase);
	cCar carNorth(_CAR_DIR_NORTH, &iPhase);
	cCar carEast(_CAR_DIR_EAST, &iPhase);
	cCar carWest(_CAR_DIR_WEST, &iPhase);

	cPeasant peasantNorth(_PE_DIR_NORTH, &iPhase);
	cPeasant peasantWest(_PE_DIR_WEST, &iPhase);

	//init
	backround->setPosition(0, 0);
	backround->drawRectangle('°', '°', sPos{ 0, _SIZE_Y_ / 2 - 4 }, sPos{ _SIZE_X_ - 1, _SIZE_Y_ / 2 + 4 }, _COL_DEFAULT, _COL_DEFAULT);
	backround->drawRectangle('°', '°', sPos{ _SIZE_X_ / 2 - 6, 0 }, sPos{ _SIZE_X_ / 2 + 6, _SIZE_Y_ }, _COL_DEFAULT, _COL_DEFAULT);

	//add objects to handler
	handler.createObject(backround);

	handler.createObject(tlNorth.getObject());
	handler.createObject(tlSouth.getObject());
	handler.createObject(tlEast.getObject());
	handler.createObject(tlWest.getObject());

	handler.createObject(ptl1.getObject());
	handler.createObject(ptl2.getObject());
	handler.createObject(ptl3.getObject());
	handler.createObject(ptl4.getObject());
	handler.createObject(ptl5.getObject());
	handler.createObject(ptl6.getObject());
	handler.createObject(ptl7.getObject());
	handler.createObject(ptl8.getObject());

	handler.createObject(carSouth.getObject());
	handler.createObject(carNorth.getObject());
	handler.createObject(carEast.getObject());
	handler.createObject(carWest.getObject());

	handler.createObject(peasantNorth.getObject());
	handler.createObject(peasantWest.getObject());

	handler.write();
	render->render();

	//main Loop

	//Starting with vertical Green, horizontal red

	while(1)
	{
		if (iWait <= 0)
		{
			iPhase++;
			switch (iPhase)
			{
			case 0: //ptls to red
				ptl1.next();
				ptl4.next();
				ptl5.next();
				ptl8.next();
				iWait = 4;
				break;
			case 1: //switch to yellow
				tlNorth.next();
				tlSouth.next();
				iWait = 4;
				break;
			case 2: //to red
				tlNorth.next();
				tlSouth.next();
				iWait = 4;
				break;
			case 3: //Yellow-Red
				tlEast.next();
				tlWest.next();
				iWait = 4;
				break;
			case 4: //Green
				tlEast.next();
				tlWest.next();
				ptl2.next();
				ptl3.next();
				ptl7.next();
				ptl6.next();
				iWait = 10;
				break;
			case 5: //vert ptls to red
				ptl2.next();
				ptl3.next();
				ptl7.next();
				ptl6.next();
				iWait = 4;
				break;
			case 6: //Yellow-red
				tlEast.next();
				tlWest.next();
				iWait = 4;
				break;
			case 7: //red
				tlEast.next();
				tlWest.next();
				iWait = 4;
				break;
			case 8: //yellow-red
				tlNorth.next();
				tlSouth.next();
				iWait = 4;
				break;
			case 9: //green
				tlNorth.next();
				tlSouth.next();
				ptl1.next();
				ptl4.next();
				ptl5.next();
				ptl8.next();
				iPhase = -1;
				iWait = 10;
				break;
			}
		}
		
		
		carWest.drive();
		carEast.drive();
		carNorth.drive();
		carSouth.drive();

		if (iFrames % 2 == 0) { //Run every 2nd frame
			peasantNorth.run();
			peasantWest.run();
		}



		handler.write();
		render->render();

		iWait--;
		iFrames++;
		backround->drawText(to_string(iFrames) , sPos{ 0,0 }, _COL_DEFAULT); //Framecounter
	}
}