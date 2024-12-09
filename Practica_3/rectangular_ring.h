
#ifndef RECTANGULAR_RING_H
#define RECTANGULAR_RING_H

#include "axis_revolution.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _rectangular_ring:public _object3D
{
public:
    vector<_vertex3f> PerfilExterior, PerfilInterior;
    _rectangular_ring(int num_rotaciones=40);
};

#endif
