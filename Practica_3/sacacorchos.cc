
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


// ANILLO (BORRAAAAAAAAAAAAAAAAA ES SOLO PRUEBA)

void _anillo::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(1,0.3,0.7);
    Anillo.draw_point();
    glPopMatrix();
}

void _anillo::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(1,0.3,0.7);
    Anillo.draw_line();
    glPopMatrix();
}

void _anillo::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(1,0.3,0.7);
    Anillo.draw_fill();
    glPopMatrix();
}

void _anillo::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(1,0.3,0.7);
    Anillo.draw_chess();
    glPopMatrix();
}



