
#ifndef SPIRAL_H
#define SPIRAL_H

#include "ply_object.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _spiral:public _ply_object
{
    float normalizacionXZ, normalizacionY;

public:
    _spiral(string File = QCoreApplication::applicationDirPath().toStdString() + "/../../../ply_models/spring.ply");

    // Necesito redefinir las funciones que pintan el modelo porque tengo que NORMALIZAR la espiral,
    // ya que tal y como está en el modelo que descargué es demasiado grande comparada con los otros objetos
    // básicos que sí son de tamaño unidad
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

#endif
