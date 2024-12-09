
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
}

void _spiral::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(0.04,0.04,0.04);
    this->_ply_object::draw_point();
    glPopMatrix();
}

void _spiral::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(0.04,0.04,0.04);
    this->_ply_object::draw_line();
    glPopMatrix();
}

void _spiral::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(0.04,0.04,0.04);
    this->_ply_object::draw_fill();
    glPopMatrix();
}

void _spiral::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(0.04,0.04,0.04);
    this->_ply_object::draw_chess();
    glPopMatrix();
}
