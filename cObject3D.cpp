#include "cObject3D.h"

cObject3D::cObject3D(unsigned int _sx, unsigned int _sy)
{
  setSize(_sx, _sy);
}

cObject3D::~cObject3D()
{
  destruct();
}

void cObject3D::addVector(sCoord3d _origin, sCoord3d _vector, char _char, WORD _color)
{
  vectors.push_back(sVector{_origin, _vector, _char, _color});
}

void cObject3D::rotate(sCoord3d _val)
{

}

void cObject3D::reset()
{
  vectors.clear();
}

void cObject3D::write()
{
  for(long unsigned int i = 0; i < vectors.size(); i++)
  {
    drawLine(vectors[i].c,
          translate(vectors[i].origin),
          translate({vectors[i].origin.x + vectors[i].direction.x, vectors[i].origin.y + vectors[i].direction.y}),
          true, vectors[i].color);
  }
}

sPos cObject3D::translate(sCoord3d _coord)
{
  sPos ret;

  ret.x = (int)((float)_coord.x - ((float)_coord.z / (float)_DEPTH * (float)_coord.x));
  ret.y = (int)((float)_coord.y - ((float)_coord.z / (float)_DEPTH * (float)_coord.y));

  return ret;
}
