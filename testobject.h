#pragma once

#include "cObject.h"

class testobject : cObject
{

public:
  testobject()
  {
    setSize(10,5);
    cc = 0;

    drawRectangle('#', NULL, {0,0}, {9,4}, _COL_GREEN, _COL_DEFAULT);
  }

  ~testobject()
  {
    destruct();
  }

  virtual void onClick(sPos _pos, unsigned int _button)
  {
    cc++;
    drawText(to_string(cc), {2,2}, _COL_RED);
  }

	virtual void onChar(unsigned char _c)
  {
    drawPoint(_c, {1,1},true, _COL_BLUE);
  }
private:
  int cc;
};
