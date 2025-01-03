
#ifndef CONE_H
#define CONE_H

#include "axis_revolution.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _cone:public _axis_revolution
{
public:
  _cone(float size = 1.0f,int num_rotaciones=30);
};

#endif
