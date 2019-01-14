#include "cWiremesh.h"

cWiremesh::cWiremesh()
{
  position = {0,0,0};
}

cWiremesh::~cWiremesh()
{

}

void cWiremesh::addVector(sCoord3d _origin, sCoord3d _vector, char _char, WORD _color)
{
  vectors.push_back(sVector{_origin, _vector, _char, _color});
}

void cWiremesh::rotate(sCoord3d _val)
{
  //Implement rotate
}

void cWiremesh::reset()
{
  vectors.clear();
}

void cWiremesh::write(cRender *_render)
{
  if(!_render)
    return;

  sPos porigin = _render->getSize();
  sCoord3d origin = {porigin.x / 2, porigin.y / 2, 0};

  for(long unsigned int i = 0; i < vectors.size(); i++)
  {
    _render->drawLine(vectors[i].c,
          translate(vectors[i].origin + position, origin),
          translate(vectors[i].origin + vectors[i].direction + position, origin),
          true, vectors[i].color);

    /*_render->drawPoint(vectors[i].c, translate(vectors[i].origin + position, origin), true, vectors[i].color);
    _render->drawPoint(vectors[i].c, translate(vectors[i].origin + vectors[i].direction + position, origin), true, vectors[i].color);*/
  }
}

sPos cWiremesh::translate(sCoord3d _coord, sCoord3d _origin)
{
  sPos ret;

  sCoord3d coord;
  coord.x = _coord.x - _origin.x;
  coord.y = _coord.y - _origin.y;
  coord.z = _coord.z - _origin.z;

  ret.x = (int)((float)coord.x - ((float)coord.z / (float)_DEPTH * (float)(coord.x)));
  ret.y = (int)((float)coord.y - ((float)coord.z / (float)_DEPTH * (float)(coord.y)));

  ret.x += _origin.x;
  ret.y += _origin.y;

  return ret;
}

sCoord3d cWiremesh::getPosition()
{
  return position;
}

void cWiremesh::setPosition(int _x, int _y, int _z)
{
  position = {_x, _y, _z};
}

void cWiremesh::setPosition(sCoord3d _pos)
{
  position = _pos;
}

void cWiremesh::scale(int _scalar)
{
  //Implement Scale
}
