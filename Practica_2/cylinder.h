
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
  _cylinder(int num_rotaciones=30);
};

#endif
