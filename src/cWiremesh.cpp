#include "cWiremesh.h"

cWiremesh::cWiremesh() : position({0,0,0}), angle({0,0,0}) { }

cWiremesh::~cWiremesh() { }

void cWiremesh::addVector(sCoord3d _origin, sCoord3d _vector, char _char, uint16_t _color)
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
    sCoord3d vorigin    = applyRotation(vectors[i].origin,    angle);
    sCoord3d vdirection = applyRotation(vectors[i].direction, angle);

    _render->drawLine(vectors[i].c,
          translate(vorigin + position, origin),
          translate(vorigin + vdirection + position, origin),
          vectors[i].color);
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

sCoord3d cWiremesh::applyRotation(sCoord3d _vector, sCoord3d _angle)
{
  sCoord3d ret = _vector;

  //Perform some algebra-magic
  //couldn't be bothered to implement or use a matrix class

  if(_angle.x)
  {
    float rads = (float)_angle.x * PI / 180.0;

    ret.y = (int)(
      (float)_vector.y * cos(rads) -
      (float)_vector.z * sin(rads)
    );
    ret.z = (int)(
      (float)_vector.y * sin(rads) +
      (float)_vector.z * cos(rads)
    );
  }
  if(_angle.y)
  {
    float rads = (float)_angle.y * PI / 180.0;
    sCoord3d tmp = ret;

    ret.x = (int)(
      (float)tmp.x * cos(rads) +
      (float)tmp.z * sin(rads)
    );

    ret.z = (int)(
      - (float)tmp.x * sin(rads)
      + (float)tmp.z * cos(rads)
    );
  }
  if(_angle.z)
  {
    float rads = (float)_angle.z * PI / 180.0;
    sCoord3d tmp = ret;

    ret.x = (int) (
      (float)tmp.x * cos(rads) -
      (float)tmp.y * sin(rads)
    );
    ret.y = (int) (
      (float)tmp.x * sin(rads) +
      (float)tmp.y * cos(rads)
    );
  }

  return ret;
}
