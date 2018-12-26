#include "cObjectHandler.h"

cObjectHandler::cObjectHandler(cRender *_render)
{
	render = _render;
}

int cObjectHandler::createObject(cObject *_object)
{
	objects.push_back(_object);
	return objects.size() - 1;
}

int cObjectHandler::moveObject(int _object, sPos _pos, int _mode)
{
	if (_object >= objects.size()) //prevent segmentation faults
		return 1;

	if (!objects[_object])
		return 1;

	sPos objPosition = objects[_object]->getPosition();

	if (_mode == _MOVE_RELATIVE)
		objects[_object]->setPosition(sPos{ objPosition.x + _pos.x, objPosition.y + _pos.y });
	else if (_mode == _MOVE_ABSOULUTE)
		objects[_object]->setPosition(_pos);

	return 0;
}

int cObjectHandler::destroyObject(int _object)
{
	delete objects[_object];
	objects[_object] = NULL;

	return 0;
}

int cObjectHandler::write()
{
	render->clear();

	for (unsigned long int i = 0; i < objects.size(); i++)
	{
		if (objects[i]) // Check if objects[i] is existent
		{
			//Draw every Object
			sObject obj = objects[i]->getObject(); //get Object #i

			for (int o = 0; o < obj.sizeY; o++) { //y axis
				for (int p = 0; p < obj.sizeX; p++) { //x axis
					if (obj.cScreen[p][o]) { //Dont overwrite empty pixels
						sPos pos{ obj.pos.x + p, obj.pos.y + o };
						render->drawPoint(obj.cScreen[p][o], pos, true, obj.wColor[p][o]);
					}
				}
			}
		}
	}

	return 0;
}
