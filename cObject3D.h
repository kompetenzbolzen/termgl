#pragma once

#include <vector>

#include "cObject.h"

#define _DEPTH 50

struct sCoord3d
{
  int x;
  int y;
  int z;
};

struct sVector
{
  sCoord3d origin;
  sCoord3d direction;

  char c;
  WORD color;
};

class cObject3D : cObject
{
public:

  cObject3D(unsigned int _sx, unsigned int _sy);

  virtual ~cObject3D();

  void addVector(sCoord3d _origin, sCoord3d _vector, char _char, WORD _color);

  void rotate(sCoord3d _val);

  void reset();

  void write();

protected:

  cObject3D(){}

private:

  sPos translate(sCoord3d _coord);

  std::vector<sVector> vectors;
};
