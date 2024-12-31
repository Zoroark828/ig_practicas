
#include "car.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

// RUEDA

void _wheel::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(2,0.8,2);
    Cilindro.draw_point();
    glPopMatrix();
}

void _wheel::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(2,0.8,2);
    Cilindro.draw_line();
    glPopMatrix();
}

void _wheel::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(2,0.8,2);
    Cilindro.draw_fill();
    glPopMatrix();
}

void _wheel::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(2,0.8,2);
    Cilindro.draw_chess();
    glPopMatrix();
}



// EJE

void _wheels_axis::draw_point(){
    // El eje estará centrado en el origen. Lo "subimos" al eje X en la clase "plataforma", para que las ruedas toquen ese eje.

    // Eje como tal (el hierro que une las dos ruedas):
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(0.5,4,0.5);
    Cilindro.draw_point();
    glPopMatrix();

    // Rueda izquierda:
    glPushMatrix();
    glTranslatef(-2.4,0,0);
    Rueda.draw_point();
    glPopMatrix();

    // Rueda derecha:
    glPushMatrix();
    glTranslatef(2.4,0,0);
    Rueda.draw_point();
    glPopMatrix();
}

void _wheels_axis::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(0.5,4,0.5);
    Cilindro.draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.4,0,0);
    Rueda.draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.4,0,0);
    Rueda.draw_line();
    glPopMatrix();
}

void _wheels_axis::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(0.5,4,0.5);
    Cilindro.draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.4,0,0);
    Rueda.draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.4,0,0);
    Rueda.draw_fill();
    glPopMatrix();
}

void _wheels_axis::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(0.5,4,0.5);
    Cilindro.draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.4,0,0);
    Rueda.draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.4,0,0);
    Rueda.draw_chess();
    glPopMatrix();
}



// PLATAFORMA

void _platform::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    // Primer eje (delantero)
    glPushMatrix();
    glTranslatef(0,0,3);
    Eje.draw_point();
    glPopMatrix();

    // Segundo eje (trasero)
    glPushMatrix();
    glTranslatef(0,0,-3);
    Eje.draw_point();
    glPopMatrix();
}

void _platform::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    // Primer eje (delantero)
    glPushMatrix();
    glTranslatef(0,0,3);
    Eje.draw_line();
    glPopMatrix();

    // Segundo eje (trasero)
    glPushMatrix();
    glTranslatef(0,0,-3);
    Eje.draw_line();
    glPopMatrix();
}

void _platform::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    // Primer eje (delantero)
    glPushMatrix();
    glTranslatef(0,0,3);
    Eje.draw_fill();
    glPopMatrix();

    // Segundo eje (trasero)
    glPushMatrix();
    glTranslatef(0,0,-3);
    Eje.draw_fill();
    glPopMatrix();
}

void _platform::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    // Primer eje (delantero)
    glPushMatrix();
    glTranslatef(0,0,3);
    Eje.draw_chess();
    glPopMatrix();

    // Segundo eje (trasero)
    glPushMatrix();
    glTranslatef(0,0,-3);
    Eje.draw_chess();
    glPopMatrix();
}



// FARO (LUZ)

void _headlight::draw_point(){
    // Creamos una luz, que se forma con un cono. La dejamos de tamaño unidad.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    Cono.draw_point();
    glPopMatrix();
}

void _headlight::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    Cono.draw_line();
    glPopMatrix();
}

void _headlight::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    Cono.draw_fill();
    glPopMatrix();
}

void _headlight::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    Cono.draw_chess();
    glPopMatrix();
}



// CHASIS

void _chassis::draw_point(){
    // Chasis (parte baja) (centrado en el origen)
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(5.6,3,8);
    Cubo.draw_point();
    glPopMatrix();

    // Chasis (parte superior, donde irian las ventanas)
    glPushMatrix();
    glTranslatef(0,2.5,-1);
    glScalef(5.6,2,4);
    Cubo.draw_point();
    glPopMatrix();

    // Faro izquierdo
    glPushMatrix();
    glTranslatef(-2,0.5,4);
    Faro.draw_point();
    glPopMatrix();

    // Faro derecho
    glPushMatrix();
    glTranslatef(2,0.5,4);
    Faro.draw_point();
    glPopMatrix();
}

void _chassis::draw_line(){
    // Chasis (parte baja) (centrado en el origen)
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(5.6,3,8);
    Cubo.draw_line();
    glPopMatrix();

    // Chasis (parte superior, donde irian las ventanas)
    glPushMatrix();
    glTranslatef(0,2.5,-1);
    glScalef(5.6,2,4);
    Cubo.draw_line();
    glPopMatrix();

    // Faro izquierdo
    glPushMatrix();
    glTranslatef(-2,0.5,4);
    Faro.draw_line();
    glPopMatrix();

    // Faro derecho
    glPushMatrix();
    glTranslatef(2,0.5,4);
    Faro.draw_line();
    glPopMatrix();
}

void _chassis::draw_fill(){
    // Chasis (parte baja) (centrado en el origen)
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(5.6,3,8);
    Cubo.draw_fill();
    glPopMatrix();

    // Chasis (parte superior, donde irian las ventanas)
    glPushMatrix();
    glTranslatef(0,2.5,-1);
    glScalef(5.6,2,4);
    Cubo.draw_fill();
    glPopMatrix();

    // Faro izquierdo
    glPushMatrix();
    glTranslatef(-2,0.5,4);
    Faro.draw_fill();
    glPopMatrix();

    // Faro derecho
    glPushMatrix();
    glTranslatef(2,0.5,4);
    Faro.draw_fill();
    glPopMatrix();
}

void _chassis::draw_chess(){
    // Chasis (parte baja) (centrado en el origen)
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(5.6,3,8);
    Cubo.draw_chess();
    glPopMatrix();

    // Chasis (parte superior, donde irian las ventanas)
    glPushMatrix();
    glTranslatef(0,2.5,-1);
    glScalef(5.6,2,4);
    Cubo.draw_chess();
    glPopMatrix();

    // Faro izquierdo
    glPushMatrix();
    glTranslatef(-2,0.5,4);
    Faro.draw_chess();
    glPopMatrix();

    // Faro derecho
    glPushMatrix();
    glTranslatef(2,0.5,4);
    Faro.draw_chess();
    glPopMatrix();
}



// COCHE

void _car::draw_point(){
    // Chasis (estaba en el origen asi que hay que levantarlo)
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,2.5,0);
    Chasis.draw_point();
    glPopMatrix();

    // Plataforma (no necesita transformaciones)
    Plataforma.draw_point();
}

void _car::draw_line(){
    // Chasis (estaba en el origen asi que hay que levantarlo)
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,2.5,0);
    Chasis.draw_line();
    glPopMatrix();

    // Plataforma (no necesita transformaciones)
    Plataforma.draw_line();

}

void _car::draw_fill(){
    // Chasis (estaba en el origen asi que hay que levantarlo)
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,2.5,0);
    Chasis.draw_fill();
    glPopMatrix();

    // Plataforma (no necesita transformaciones)
    Plataforma.draw_fill();
}

void _car::draw_chess(){
    // Chasis (estaba en el origen asi que hay que levantarlo)
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,2.5,0);
    Chasis.draw_chess();
    glPopMatrix();

    // Plataforma (no necesita transformaciones)
    Plataforma.draw_chess();
}





