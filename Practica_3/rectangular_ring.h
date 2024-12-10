
#ifndef RECTANGULAR_RING_H
#define RECTANGULAR_RING_H

#include "object3d.h"


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
    _vertex3ui trianglesSum(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax);
};

#endif
