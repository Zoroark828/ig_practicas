
#include "sacacorchos.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

////////////// CONSTRUCTORES POR COPIA DE TODAS LAS CLASES

_rosca::_rosca(_cylinder &Cylinder, _spiral &Spiral){
    Cilindro = &Cylinder;
    Espiral = &Spiral;
}

_agarre::_agarre(_cylinder &Cylinder, _rectangular_ring &Ring, _spiral &Spiral){
    Rosca = new _rosca(Cylinder, Spiral);
    Anillo = &Ring;
}

_palanca::_palanca(_cube &Cube){
    Cubo = &Cube;
}

_tornillo::_tornillo(_cone &Cone){
    Cono = &Cone;
}

_soporte::_soporte(_cube &Cube, _cone &Cone){
    Cubo = &Cube;
    Palanca = new _palanca(Cube);
    Tornillo = new _tornillo(Cone);
}

_campana::_campana(_cylinder &Cylinder, _rectangular_ring &Ring){
    Cilindro = &Cylinder;
    Anillo = &Ring;
}

_estructura::_estructura(_cube &Cube, _cone &Cone, _cylinder &Cylinder, _rectangular_ring &Ring){
    Campana = new _campana(Cylinder, Ring);
    Soporte = new _soporte(Cube, Cone);
}

_sacacorchos::_sacacorchos(_cube &Cube, _cone &Cone, _cylinder &Cylinder, _rectangular_ring &Ring, _spiral &Spiral){
    Estructura = new _estructura(Cube, Cone, Cylinder, Ring);
    Agarre = new _agarre(Cylinder, Ring, Spiral);
}








////////////// FUNCIONES PARA DIBUJAR CADA PARTE DEl SACACORCHOS

// ROSCA
void _rosca::draw_point(){
    // Espiral del sacacorchos. El "pincho" por así decirlo
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-2.2,0);
    glScalef(0.55,5,0.55);
    Espiral->draw_point();
    glPopMatrix();

    // Cilindro que sujeta superiormente a la espiral
    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(0.6,5,0.6);
    Cilindro->draw_point();
    glPopMatrix();
}


void _rosca::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-2.2,0);
    glScalef(0.55,5,0.55);
    Espiral->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(0.6,5,0.6);
    Cilindro->draw_line();
    glPopMatrix();
}

void _rosca::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-2.2,0);
    glScalef(0.55,5,0.55);
    Espiral->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(0.6,5,0.6);
    Cilindro->draw_fill();
    glPopMatrix();
}

void _rosca::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-2.2,0);
    glScalef(0.55,5,0.55);
    Espiral->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(0.6,5,0.6);
    Cilindro->draw_chess();
    glPopMatrix();
}



// AGARRE
void _agarre::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-4.9,0); // Bajo la rosca 4'9 unidades y no 5 porque si no parece que está separada del agarre
    Rosca->draw_point();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.9,0);  // Lo pongo sobre el origen
    glRotatef(90,1.1,0,0);
    glScalef(2.8,0.8,1.8);
    Anillo->draw_point();
    glPopMatrix();
}

void _agarre::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-4.9,0);
    Rosca->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.9,0);
    glRotatef(90,1,0,0);
    glScalef(2.8,0.8,1.8);
    Anillo->draw_line();
    glPopMatrix();
}

void _agarre::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-4.9,0);
    Rosca->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.9,0);
    glRotatef(90,1,0,0);
    glScalef(2.8,0.8,1.8);
    Anillo->draw_fill();
    glPopMatrix();
}

void _agarre::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-4.9,0);
    Rosca->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.9,0);
    glRotatef(90,1,0,0);
    glScalef(2.8,0.8,1.8);
    Anillo->draw_chess();
    glPopMatrix();
}



// PALANCA
void _palanca::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_point();
    glPopMatrix();
}

void _palanca::draw_line(int alpha){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(alpha,0,0,1);
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_line();
    glPopMatrix();
}

void _palanca::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_fill();
    glPopMatrix();
}

void _palanca::draw_chess(int alpha){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(alpha,0,0,1);
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_chess();
    glPopMatrix();
}



// TORNILLO
void _tornillo::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glScalef(0.5,1.3,0.5);
    Cono->draw_point();
    glPopMatrix();
}

void _tornillo::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glScalef(0.5,1.3,0.5);
    Cono->draw_line();
    glPopMatrix();
}

void _tornillo::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glScalef(0.5,1.3,0.5);
    Cono->draw_fill();
    glPopMatrix();
}

void _tornillo::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glScalef(0.5,1.3,0.5);
    Cono->draw_chess();
    glPopMatrix();
}




// SOPORTE
void _soporte::draw_point(){
    // Soporte como tal, pieza en la que se anclan las palas con ayuda de los tornillos
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(3,2.5,1.2);
    Cubo->draw_point();
    glPopMatrix();

    // Palancas izquierda y derecha
    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Palanca->draw_point();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_point();
    glPopMatrix();

    // Tornillos izquierdo y derecho
    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Tornillo->draw_point();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Tornillo->draw_point();
    glPopMatrix();
}

void _soporte::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(3,2.5,1.2);
    Cubo->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Palanca->draw_line(-45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_line(45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Tornillo->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Tornillo->draw_line();
    glPopMatrix();
}

void _soporte::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(3,2.5,1.2);
    Cubo->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Palanca->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Tornillo->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Tornillo->draw_fill();
    glPopMatrix();
}

void _soporte::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(3,2.5,1.2);
    Cubo->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Palanca->draw_chess(-45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_chess(45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Tornillo->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Tornillo->draw_chess();
    glPopMatrix();
}




// CAMPANA
void _campana::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-1.5,0);
    glScalef(2.5,0.75,2.5);
    Anillo->draw_point();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.75,0.7);
    glRotatef(-10,1,0,0);
    glScalef(0.5,4,0.5);
    Cilindro->draw_point();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_point();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_point();
    glPopMatrix();
}


void _campana::draw_line(){
    // Anillo al que se unen los tres cilindros. Se encuentra abajo
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-1.5,0);
    glScalef(2.5,0.75,2.5);
    Anillo->draw_line();
    glPopMatrix();

    // Primer cilindro, colocado en la parte "delantera", izquierda
    glPushMatrix();
    glTranslatef(-0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_line();
    glPopMatrix();

    // Segundo cilindro, colocado en la parte "delantera", derecha
    glPushMatrix();
    glTranslatef(0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_line();
    glPopMatrix();

    // Tercer cilindro, colocado en la parte "trasera", izquierda
    glPushMatrix();
    glTranslatef(-0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_line();
    glPopMatrix();

    // Cuarto cilindro, colocado en la parte "trasera", derecha. Mismas medidas que el anterior pero inversas en algun valor
    glPushMatrix();
    glTranslatef(0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_line();
    glPopMatrix();


    /* Antiguo cilindro, cuando solo había 3 cilindros en la campana
    glPushMatrix();
    glTranslatef(0,0.75,0.7);
    glRotatef(-10,1,0,0);
    glScalef(0.5,4,0.5);
    Cilindro->draw_fill();
    glPopMatrix();
    */
}

void _campana::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-1.5,0);
    glScalef(2.5,0.75,2.5);
    Anillo->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_fill();
    glPopMatrix();

}

void _campana::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-1.5,0);
    glScalef(2.5,0.75,2.5);
    Anillo->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_chess();
    glPopMatrix();
}



// ESTRUCTURA
void _estructura::draw_point(){

}


void _estructura::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1.25,0); // Lo muevo para arriba de forma que su parte baja toque el eje X
    Soporte->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0); // Lo coloco debajo del soporte
    Campana->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,3,0);
    //Agarre->draw_line();         ///////////////////////////////////////////////////////////
    glPopMatrix();
}

void _estructura::draw_fill(){


}

void _estructura::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1.25,0); // Lo muevo para arriba de forma que su parte baja toque el eje X
    Soporte->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0); // Lo coloco debajo del soporte
    Campana->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,3,0);
    //Agarre->draw_chess();         ///////////////////////////////////////////////////////////
    glPopMatrix();

}




void _sacacorchos::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Estructura->draw_point();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,3,0);
    Agarre->draw_point();
    glPopMatrix();
}

void _sacacorchos::draw_line(){
    glLineWidth(0.2);   // Le he cambiado la anchura de línea a todo el sacacorchos para que se vea mejor al alejarse la cámara

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Estructura->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,3,0);
    Agarre->draw_line();
    glPopMatrix();
}

void _sacacorchos::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Estructura->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,3,0);
    Agarre->draw_fill();
    glPopMatrix();
}

void _sacacorchos::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Estructura->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,3,0);
    Agarre->draw_chess();
    glPopMatrix();
}












