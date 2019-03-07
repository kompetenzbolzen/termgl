#include "cObjectHandler.h"

cObjectHandler::cObjectHandler(cRender *_render, bool _enableInputMapping, bool _enableCollision) :  iActiveObject(0), cameraPosition ({0,0})
{
	render = _render;

	enableInputMapping = _enableInputMapping;
	enableCollision = enableInputMapping ? _enableCollision : false; // Collision requires input mapping

	objects.push_back(NULL); //Create first Object as Catcher for Events

	buildHitmap();
}

unsigned int cObjectHandler::createObject(cObject *_object)
{
	objects.push_back(_object);

	buildHitmap();
	return objects.size() - 1;
}

int cObjectHandler::moveObject(unsigned int _object, sPos _pos, int _mode)
{
	if (_object >= objects.size()) //prevent segmentation faults
		return 1;

	if (!objects[_object])
		return 1;

	sPos objPosition = objects[_object]->getPosition();
	sPos newPosition = {0,0};

	if (_mode == _MOVE_RELATIVE)
		newPosition = { objPosition.x + _pos.x, objPosition.y + _pos.y };
	else if (_mode == _MOVE_ABSOLUTE)
		newPosition = _pos;
	else if (_mode == _MOVE_FORCE_ABSOLUTE)
	{
		objects[_object]->setPosition(_pos);
		return 0;
	}

	sCollision coll = checkCollision(newPosition, objects[_object]->getSize());


	bool abort = false;

	if(coll.idc)
	{
		for(unsigned int i = 0; i < coll.idc; i++)
		{
			if(coll.idv[i] != _object && objects[coll.idv[i]])
				abort += objects[_object]->onCollisionActive(_pos, objects[coll.idv[i]]->onCollisionPassive(_pos));
		}
	}

	if(!abort)
		objects[_object]->setPosition(newPosition);

	if(coll.idv)
		free (coll.idv);
	if(coll.hitv)
		free (coll.hitv);

	buildHitmap();
	return abort;
}

int cObjectHandler::destroyObject(unsigned int _object)
{
	if(!objects[_object])
		return 1;

	delete objects[_object];
	objects[_object] = NULL;

	buildHitmap();
	return 0;
}

int cObjectHandler::write()
{
	render->clear();

	for (unsigned long int i = 0; i < meshes.size(); i++)
	{
		if(meshes[i])
		{
			moveWiremesh(i,{-cameraPosition.x, -cameraPosition.y, 0} ,_MOVE_RELATIVE);
			meshes[i]->write(render);
			moveWiremesh(i,{cameraPosition.x, cameraPosition.y, 0},_MOVE_RELATIVE);
		}
	}

	for (unsigned long int i = 0; i < objects.size(); i++)
	{
		if (objects[i])
		{
			objects[i]->write(render, cameraPosition);
		}
	}

	return 0;
}

int cObjectHandler::clickEvent(sPos _pos, unsigned int _button)
{
	if(_pos.x >= (int)iHitMap.size())
		return 1;
	if(_pos.y >= (int)iHitMap[_pos.x].size())
		return 1;


	if(objects[ iHitMap[_pos.x][_pos.y] ])
	{
		sPos rel_pos;
		sPos obj_pos = objects[ iHitMap[_pos.x][_pos.y] ]->getPosition();
		rel_pos.x = _pos.x - obj_pos.x + cameraPosition.x;
		rel_pos.y = _pos.y - obj_pos.y + cameraPosition.y;

		iActiveObject = iHitMap[_pos.x][_pos.y]; //Set active object
		objects[ iHitMap[_pos.x][_pos.y] ]->onClick(rel_pos, _button);
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
	if(!enableInputMapping)
		return;

	//Rebuild 2D vector
	sPos size = render->getSize();

	vector<unsigned int> cp;

	while(size.y > (int)cp.size())
	{
		cp.push_back(0);
	}

	while (size.x > (int)iHitMap.size())
	{
		iHitMap.push_back(cp);
	}

	while (size.x < (int)iHitMap.size())
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

			oPos.x -= cameraPosition.x;
			oPos.y -= cameraPosition.y;

			for(int x = oPos.x; x < oPos.x + oSize.x; x++)
			{
				for(int y = oPos.y; y < oPos.y + oSize.y; y++)
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

unsigned int cObjectHandler::createWiremesh(cWiremesh *_mesh)
{
	meshes.push_back(_mesh);

	return meshes.size() - 1;
}

int cObjectHandler::moveWiremesh(unsigned int _mesh, sCoord3d _pos, int _mode)
{
	if (_mesh >= meshes.size()) //prevent segmentation faults
		return 1;

	if (!meshes[_mesh])
		return 1;

	sCoord3d meshPosition = meshes[_mesh]->getPosition();

	if (_mode == _MOVE_RELATIVE)
		meshes[_mesh]->setPosition(meshPosition + _pos);
	else if (_mode == _MOVE_ABSOLUTE)
		meshes[_mesh]->setPosition(_pos);

	return 0;
}

int cObjectHandler::destroyWiremesh(unsigned int _mesh)
{
	if(!meshes[_mesh])
		return 1;

	delete meshes[_mesh];
	meshes[_mesh] = NULL;

	return 0;
}

int cObjectHandler::rotateWiremesh(unsigned int _mesh, sCoord3d _angle)
{
	if (_mesh >= meshes.size()) //prevent segmentation faults
		return 1;

	if (!meshes[_mesh])
		return 1;

	meshes[_mesh]->rotate(_angle);

	return 0;
}

void cObjectHandler::setCameraPosition(sPos _pos, int _mode)
{
	if(_mode == _MOVE_ABSOLUTE)
		cameraPosition = _pos;
	else if(_mode == _MOVE_RELATIVE)
	{
		cameraPosition.x += _pos.x;
		cameraPosition.y += _pos.y;
	}

	buildHitmap();
}

sPos cObjectHandler::getCameraPosition()
{
	return cameraPosition;
}

sCollision cObjectHandler::checkCollision(sPos _pos, sPos _size)
{
	sCollision ret;
	vector<unsigned int> collisions;
	vector<int> hitTypes;
	ret.idc = 0;
	ret.idv = NULL;
	ret.hitv = NULL;

	if(!render)
		return ret;

	if(!enableCollision || !enableInputMapping)
		return ret;

	int sizeX, sizeY;

	sizeX = render->getSize().x;
	sizeY = render->getSize().y;

	//The mother of if-statements
	//No collision for offscreen objects
	if( (_pos.x < cameraPosition.x && _pos.x + _size.x + cameraPosition.x < 0) ||
			(_pos.x - cameraPosition.x >= (int)iHitMap.size() && _pos.x + _size.x - cameraPosition.x >= (int)iHitMap.size()) ||
			(_pos.y < cameraPosition.y && _pos.y + _size.y + cameraPosition.y < 0) ||
			(_pos.y - cameraPosition.y >= (int)iHitMap[0].size() && _pos.y + _size.y - cameraPosition.y >= (int)iHitMap[0].size()) )
		return ret;

	for(int x = _pos.x - cameraPosition.x; x < _pos.x + _size.x - cameraPosition.x; x++)
	{
		for(int y = _pos.y - cameraPosition.y; y < _pos.y + _size.y - cameraPosition.y; y++)
		{
			if(!(x >= sizeX || x < 0 || y >= sizeY || y < 0))
			{
				if(iHitMap[x][y])
					collisions.push_back(iHitMap[x][y]);
			}
		}
	}

	//Since Object can hit on multiple Pixels, duplications can occur.
	//Sort and set duplicates to zero
	//-> zeros are at front of vector
	for(unsigned int swaps = 1; swaps > 0;)
	{
		swaps = 0;

		for(long int i = 0; i  < (long int)collisions.size() - 1; i++) //Do not change to unsigned! can cause underflow!!
		{
			if(collisions[i] > collisions[i + 1])
			{
				swaps ++;
				unsigned int tmp = 0;

				tmp = collisions[i];
				collisions[i] = collisions[i + 1];
				collisions[i + 1] = tmp;
			}
			if(collisions[i] == collisions[i + 1])
				collisions[i] = 0;
		}
	}


	//Since every empty entry is in front, pop them
	while( collisions.size() && !collisions.front())
		collisions.erase(collisions.begin());

	ret.idc = collisions.size();
	ret.idv = (unsigned int*) malloc( sizeof(*ret.idv) * ret.idc );

	for(unsigned int i = 0; i < ret.idc; i++)
	{
		ret.idv[i] = collisions[i];
	}

	return ret;
}
