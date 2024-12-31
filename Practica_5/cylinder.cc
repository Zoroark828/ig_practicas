
#include "cylinder.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cylinder::_cylinder(int n_r)
{
    // El perfil tendrá que ser un rectángulo
    Perfil.resize(4);
    Perfil[0]=_vertex3f(0,0.5,0);                       // Vertice arriba izq
    Perfil[1]=_vertex3f(0,-0.5,0);                       // Vertice abajo izq
    Perfil[2]=_vertex3f(0.5,-0.5,0);                     // Vertice abajo derecha
    Perfil[3]=_vertex3f(0.5,0.5,0);                     // Vertice arriba derecha

    num_rotaciones = 40;
    circularSweeping(num_rotaciones);
}

