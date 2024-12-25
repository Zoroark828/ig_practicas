
#include "spiral.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_spiral::_spiral(string File){
    _ply_object Espiral(File);
    Vertices = Espiral.Vertices;
    Triangles = Espiral.Triangles;

    float maxY = 0;
    float maxX = 0;

    // Busco los valores máximos y mínimos del eje X e Y
    for (int i = 0; i < Vertices.size(); i++){
        if (Vertices[i].y > maxY)
            maxY = Vertices[i].y;

        if (Vertices[i].x > maxX)
            maxX = Vertices[i].x;
    }

    // Variables utilizadas para normalizar la espiral (transformandola), porque en el archivo que usamos la espiral es más larga que ancha
    // Quiero que como mucho la X e Y valgan 0'5 para que la espiral mida una unidad
    normalizacionXZ = 0.5 / maxX;
    normalizacionY = 0.5 / maxY;
}

void _spiral::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(normalizacionXZ,normalizacionY,normalizacionXZ);
    this->_ply_object::draw_point();
    glPopMatrix();
}

void _spiral::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(normalizacionXZ,normalizacionY,normalizacionXZ);
    this->_ply_object::draw_line();
    glPopMatrix();
}

void _spiral::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(normalizacionXZ,normalizacionY,normalizacionXZ);
    this->_ply_object::draw_fill();
    glPopMatrix();
}

void _spiral::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(normalizacionXZ,normalizacionY,normalizacionXZ);
    this->_ply_object::draw_chess();
    glPopMatrix();
}
