
#ifndef CYLINDER_H
#define CYLINDER_H

#include "axis_revolution.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _cylinder:public _axis_revolution
{
public:
  _cylinder(float size = 1.0f, int num_rotaciones=30);
};

#endif
