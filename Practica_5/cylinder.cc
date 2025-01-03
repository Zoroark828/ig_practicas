
#include "cylinder.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cylinder::_cylinder(float size, int n_r)
{
    // El perfil tendrá que ser un rectángulo
    Perfil.resize(4);
    Perfil[0]=_vertex3f(0,size/2.0,0);                       // Vertice arriba izq
    Perfil[1]=_vertex3f(0,-size/2.0,0);                       // Vertice abajo izq
    Perfil[2]=_vertex3f(size/2.0,-size/2,0);                     // Vertice abajo derecha
    Perfil[3]=_vertex3f(size/2.0,size/2.0,0);                     // Vertice arriba derecha

    num_rotaciones = n_r;
    circularSweeping(n_r);
}

