
#ifndef AXIS_REV_H
#define AXIS_REV_H

#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _axis_revolution:public _object3D
{
public:
    vector<_vertex3f> Perfil;
    _axis_revolution(int num_rotaciones = 5);   // Crea el Perfil y utiliza la función circular_sweeping
    void circular_sweeping(vector<_vertex3f> Profile, int num_rotaciones);  // Crea el objeto rotando circularmente el Perfil sobre el eje Y

    _vertex3ui sumaTriangulos(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax);
    void trianglescalc(vector<_vertex3f> Perfil, int f, int c, _vertex3ui &t0, _vertex3ui &t1);
};

#endif
