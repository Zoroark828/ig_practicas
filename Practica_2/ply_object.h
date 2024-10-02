

#ifndef PLY_OBJECT
#define PLY_OBJECT

#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _ply_object:public _object3D
{
public:
  _ply_object(std::string File = "./../../../ant.ply");

};

#endif
//"ply_models/ant.ply"
