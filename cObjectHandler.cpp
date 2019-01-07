#include "cObjectHandler.h"

cObjectHandler::cObjectHandler(cRender *_render)
{
	render = _render;
	iActiveObject = 0;

	objects.push_back(NULL); //Create first Object as Catcher for Events

	buildHitmap();
}

int cObjectHandler::createObject(cObject *_object)
{
	objects.push_back(_object);

	buildHitmap();
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
	else if (_mode == _MOVE_ABSOLUTE)
		objects[_object]->setPosition(_pos);

	buildHitmap();
	return 0;
}

int cObjectHandler::destroyObject(int _object)
{
	delete objects[_object];
	objects[_object] = NULL;

	buildHitmap();
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

int cObjectHandler::clickEvent(sPos _pos, unsigned int _button)
{
	if(_pos.x >= iHitMap.size())
		return 1;
	if(_pos.y >= iHitMap[_pos.x].size())
		return 1;


	if(objects[ iHitMap[_pos.x][_pos.y] ])
	{
		iActiveObject = iHitMap[_pos.x][_pos.y]; //Set active object
		objects[ iHitMap[_pos.x][_pos.y] ]->onClick(_pos, _button);
	}
	else
		return 1;

	return 0;
}

int cObjectHandler::charEvent(unsigned char _c)
{
	if(objects.size() > iActiveObject)
	{
		if(objects[iActiveObject])
		{
			objects[iActiveObject]->onChar(_c);
		}
		else
			return 1;
	}

	return 0;
}

void cObjectHandler::buildHitmap()
{
	//Rebuild 2D vector
	sPos size = render->getSize();

	vector<unsigned int> cp;

	while(size.y > cp.size())
	{
		cp.push_back(0);
	}

	while (size.x > iHitMap.size())
	{
		iHitMap.push_back(cp);
	}

	while (size.x <= iHitMap.size())
	{
		iHitMap.pop_back();
	}
	for(unsigned int x = 0; x < iHitMap.size(); x++)
	{
		for(unsigned int y = 0; y < iHitMap[x].size(); y++)
		{
			iHitMap[x][y] = 0;
		}
	}
	//Write object IDs to iHitMap
	for(unsigned int i = 0; i < objects.size(); i++)
	{
		if(objects[i])
		{
			sPos oPos = objects[i]->getPosition();
			sPos oSize = objects[i]->getSize();

			for(int x = oPos.x; x <= oPos.x + oSize.x; x++)
			{
				for(int y = oPos.y; y <= oPos.y + oSize.y; y++)
				{
					if((x < size.x && y < size.y) && (x >= 0 && y >= 0)) //Objects can be outside the screen.
						iHitMap[x][y] = i;
				}//for
			}//for
		}//if
	}//for
}//buildHitmap

void cObjectHandler::focusNext()
{
	iActiveObject++;

	if(iActiveObject >= objects.size())
		iActiveObject = 0;
}

void cObjectHandler::focus(unsigned int _id)
{
	if(_id >= objects.size())
		iActiveObject = objects.size();
	else
		iActiveObject = _id;
}
