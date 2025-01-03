
#include "cone.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cone::_cone(int n_r)
{
    // Como es un cono, su perfil tendrá 3 vertices (será un triángulo)
    Perfil.resize(3);
    Perfil[0]=_vertex3f(0,0.5,0);               // Arriba izquierda
    Perfil[1]=_vertex3f(0,-0.5,0);              // Abajo izquierda
    Perfil[2]=_vertex3f(0.5,-0.5,0);            // Abajo derecha

    num_rotaciones = n_r;
    circularSweeping(n_r);
}
