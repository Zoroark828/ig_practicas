
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
    _axis_revolution(){}   // Constructor que no hace nada

    // Crea el objeto rotando circularmente el Perfil sobre el eje Y
    void circularSweeping(int num_rotaciones);

    // Devuelve la suma del triángulo t1 y t2 teniendo en cuenta que ninguna de sus componentes puede superar el valor valorMax
    _vertex3ui trianglesSum(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax);

    // Función que genera los triángulos. Utilizo la función para serar esté código de circular_sweeping
    void trianglesGeneration(int num_rotaciones);
};

#endif
