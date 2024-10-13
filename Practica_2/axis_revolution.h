
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
    _axis_revolution(int num_rotaciones);   // Crea el Perfil y utiliza la función circular_sweeping
    void circular_sweeping(vector<_vertex3f> Profile, int num_rotaciones);  // Crea el objeto rotando circularmente el Perfil sobre el eje Y
};

#endif
