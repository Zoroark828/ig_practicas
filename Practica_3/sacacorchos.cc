
#include "sacacorchos.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

// ROSCA

void _rosca::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //?
    Espiral.draw_point();
    glPopMatrix();
}

void _rosca::draw_line(){
    Espiral.draw_line();
}

void _rosca::draw_fill(){
    Espiral.draw_fill();
}

void _rosca::draw_chess(){
    Espiral.draw_chess();
}






