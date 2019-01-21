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
  angle = angle + _val;
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
  }
}

sPos cWiremesh::translate(sCoord3d _coord, sCoord3d _origin)
{
  sPos ret;

  ret.x = (int)((float)_coord.x - ((float)_coord.z / (float)_DEPTH * (float)(_coord.x - _origin.x)));
  ret.y = (int)((float)_coord.y - ((float)_coord.z / (float)_DEPTH * (float)(_coord.y - _origin.y)));

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

void cWiremesh::scale(float _scalar)
{
  for(unsigned long int i = 0; i < vectors.size(); i++)
  {
    vectors[i].origin.x = (int)((float)vectors[i].origin.x * _scalar);
    vectors[i].origin.y = (int)((float)vectors[i].origin.y * _scalar);
    vectors[i].origin.z = (int)((float)vectors[i].origin.z * _scalar);

    vectors[i].direction.x = (int)((float)vectors[i].direction.x * _scalar);
    vectors[i].direction.y = (int)((float)vectors[i].direction.y * _scalar);
    vectors[i].direction.z = (int)((float)vectors[i].direction.z * _scalar);
  }
}

sCoord3d applyRotation(sCoord3d _vector, sCoord3d _angle)
{
  sCoord3d ret = _vector;

  if(_angle.x)
  {

  }
  if(_angle.y)
  {

  }
  if(_angle.z)
  {

  }

  return ret;
}
