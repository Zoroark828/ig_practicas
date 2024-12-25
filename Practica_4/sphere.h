#ifndef SPHERE_H
#define SPHERE_H

#include "axis_revolution.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _sphere:public _axis_revolution
{
public:
  _sphere(int num_rotaciones=30);
    // Función que crea el perfil de la esfera con num_vertices siendo el numero de vertices de dicho perfil
    void createSphereProfile(int num_vertices);
};

#endif
