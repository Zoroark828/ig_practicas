
#include "cone.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cone::_cone(int num_rotaciones)
{
    // Como es un cono, su perfil tendrá 3 vertices (será un triángulo)
    Perfil.resize(3);
    Perfil[0]=_vertex3f(0,-0.5,0);
    Perfil[1]=_vertex3f(0.5,-0.5,0);
    Perfil[2]=_vertex3f(0,0.5,0);


    num_rotaciones = 40;
    circularSweeping(num_rotaciones);
}
