#pragma once

#include <vector>
#include <cmath>

#include "cRender.h"

#define _DEPTH 99
#define PI 3.14159265

struct sCoord3d
{
  int x;
  int y;
  int z;

  sCoord3d operator+(sCoord3d p)
  {
    sCoord3d ret;
    ret.x = x + p.x;
    ret.y = y + p.y;
    ret.z = z + p.z;
    return ret;
  }

  sCoord3d operator-(sCoord3d p)
  {
    sCoord3d ret;
    ret.x = x - p.x;
    ret.y = y - p.y;
    ret.z = z - p.z;
    return ret;
  }
};

struct sVector
{
  sCoord3d origin;
  sCoord3d direction;

  char c;
  uint16_t color;
};

/**
* cWiremesh stores 3D objects as multiple vectors. it can write itself on a cRender framebuffer.
*/
class cWiremesh
{
public:

  cWiremesh();

  virtual ~cWiremesh();

  /**
  * Add a line from _origin to (_origin + _vector) in 3D space.
  */
  void addVector(sCoord3d _origin, sCoord3d _vector, char _char, uint16_t _color);

  /**
  * Rotates by (x,y,z) degrees around the corresponding axis.
  * Rotation is stored seperatately from original vectors while they stay untouched to prevent growing rounding errors by repeated rotation.
  *
  * Rotation is applied relative to the origin of this wiremsh.
  */
  void rotate(sCoord3d _val);

  /**
  * Scales by _scalar. The scalar is directly applied to all vectors. Be wary of growing rounding errors!
  */
  void scale(float _scalar);

  sCoord3d getPosition();

  void setPosition(int _x, int _y, int _z);

  void setPosition(sCoord3d _pos);

  /**
  * clear this wiremesh
  */
  void reset();

  /**
  * Translates wiremesh into 2D space after applying rotation to each vector.
  * The vanishing point is set to the center of _render with depth _DEPTH. Alter _DEPTH to achieve optimal resultst.
  */
  void write(cRender *_render);

protected:

private:

  sPos translate(sCoord3d _coord, sCoord3d _origin);

  sCoord3d applyRotation(sCoord3d _vector, sCoord3d _angle);

  sCoord3d position;

  sCoord3d angle;

  std::vector<sVector> vectors;
};
