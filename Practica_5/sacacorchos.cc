
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

_soporte::_soporte(float f_d, _cube &Cube, _cone &Cone){
    first_d = f_d;

    Cubo = &Cube;
    Palanca = new _palanca(Cube);
    Tornillo = new _tornillo(Cone);
}

_campana::_campana(_cylinder &Cylinder, _rectangular_ring &Ring){
    Cilindro = &Cylinder;
    Anillo = &Ring;
}

_estructura::_estructura(float f_d, _cube &Cube, _cone &Cone, _cylinder &Cylinder, _rectangular_ring &Ring){
    Campana = new _campana(Cylinder, Ring);
    Soporte = new _soporte(f_d, Cube, Cone);
}

_sacacorchos::_sacacorchos(_cube &Cube, _cone &Cone, _cylinder &Cylinder, _rectangular_ring &Ring, _spiral &Spiral){
    // Inicializo los valores relacionados con los grados de libertad
    first_d = MIN_FIRST_D;
    second_d = 0;
    third_d = MAX_THIRD_D;
    first_d_rate = 1;
    second_d_rate = -5;
    third_d_rate = -0.05;

    // Creo sus dos subpartes
    Estructura = new _estructura(first_d, Cube, Cone, Cylinder, Ring);
    Agarre = new _agarre(Cylinder, Ring, Spiral);


}








////////////// FUNCIONES RELACIONADAS CON LOS GRADOS DE LIBERTAD

void _sacacorchos::increase_first_degree(){
    float sum = first_d + first_d_rate;

    if (sum < MAX_FIRST_D)
        first_d = sum;
    else
        first_d = MAX_FIRST_D;

    Estructura->modify_first_degree(first_d);
    // También cambian los otros dos grados de libertad, ya que dependen unos de otros
    third_d = equivalent_degrees_first(first_d);
    if (first_d != MAX_FIRST_D) // No dejo que el agarre pueda girar más si las palancas no se pueden mover
        second_d += second_d_rate;
}

void _sacacorchos::increase_second_degree(){
    // En un principio hace lo mismo que la función increase_first_degree, que además se encarga de comprobar que
    // el agarre no gire más si las otras piezas no se pueden mover
    increase_first_degree();
}

void _sacacorchos::increase_third_degree(){
    float sum = third_d + third_d_rate;

    if (sum > MIN_THIRD_D)
        third_d = sum;
    else
        third_d = MIN_THIRD_D;

    // Calculo y modifico el first degree equivalente
    first_d = equivalent_degrees_third(third_d);
    Estructura->modify_first_degree(first_d);
    // Asigno el nuevo second_d (si he podido mover el agarre)
    if (third_d != MIN_THIRD_D)
        second_d += second_d_rate;
}

void _sacacorchos::decrease_first_degree(){
    float res = first_d - first_d_rate;

    if (res > MIN_FIRST_D)
        first_d = res;
    else
        first_d = MIN_FIRST_D;

    Estructura->modify_first_degree(first_d);
    // También cambian los otros dos grados de libertad, ya que dependen unos de otros
    third_d = equivalent_degrees_first(first_d);
    if (first_d != MIN_FIRST_D) // No dejo que el agarre pueda girar más si las palancas no se pueden mover
        second_d -= second_d_rate;
}

void _sacacorchos::decrease_second_degree(){
    decrease_first_degree();
}

void _sacacorchos::decrease_third_degree(){
    float res = third_d - third_d_rate;

    if (res < MAX_THIRD_D)
        third_d = res;
    else
        third_d = MAX_THIRD_D;

    // Calculo y modifico el first degree equivalente
    first_d = equivalent_degrees_third(third_d);
    Estructura->modify_first_degree(first_d);
    // Asigno el nuevo second_d (si he podido mover el agarre)
    if (third_d != MAX_THIRD_D)
        second_d -= second_d_rate;
}



// Funciones para cambiar la cantidad que se modifica al incrementar/decrementar los grados de libertad
void _sacacorchos::increase_rate_first_degree(){
    first_d_rate+=1;    // grados
}

void _sacacorchos::increase_rate_second_degree(){
    second_d_rate-=1;   // grados
}

void _sacacorchos::increase_rate_third_degree(){
    third_d_rate-=0.1;    // unidades
}

void _sacacorchos::decrease_rate_first_degree(){
    first_d_rate-=0.1;
}

void _sacacorchos::decrease_rate_second_degree(){
    second_d_rate+=1;
}

void _sacacorchos::decrease_rate_third_degree(){
    third_d_rate+=1;
}


void _estructura::modify_first_degree(float d){
    Soporte->modify_first_degree(d);
}


void _soporte::modify_first_degree(float d){
    first_d = d;
}



// Funciones que devuelven el equivalente de cierto grado, ya que los grados de libertad guardan
// dependencia entre ellos
// Por ejemplo, cuando el agarre está en su punto más alto, las palas deben estar en su punto más bajo (y viceversa)

// Devuelve el nuevo valor de second
float _sacacorchos::equivalent_degrees_first(float fd){
    float third, aux;

    /* Normalizo el primer grado de libertad a un valor entre un intervalo 0 - 1
    La ecuación que utilizo es
                                    x = (x' - MIN) / (MAX - MIN),
    donde MAX=1, MIN=0, x el valor normalizado y x' su valor no normalizado
    */
    aux = (fd - MIN_FIRST_D) / (MAX_FIRST_D - MIN_FIRST_D);

    /* Dicho valor entre 0 y 1 lo convierto al equivalente en el intervalo de posibles valores del tercer grado de libertad
    Utilizo la misma formula pero despejando el valor x', es decir:
                                        x' = x * (MAX - MIN) + MIN
    También tengo que tener en cuenta que MIN = MAX_THIRD_D y MAX = MIN_THIRD_D, porque el agarre debe hacer un movimiento
    inverso a las palancas (cuando estas suben, el agarre baja, y viceversa)
    */
    third = aux * (MIN_THIRD_D - MAX_THIRD_D) + MAX_THIRD_D;

    return third;
}

// Devuelve el nuevo valor de first
float _sacacorchos::equivalent_degrees_third(float td){
    float first, aux;

    // Utilizo el mismo planteamiento que en la anterior función
    aux = (td - MAX_THIRD_D) / (MIN_THIRD_D - MAX_THIRD_D);
    first = aux * (MAX_FIRST_D - MIN_FIRST_D) + MIN_FIRST_D;

    return first;
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

void _rosca::draw_flat(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-2.2,0);
    glScalef(0.55,5,0.55);
    //Espiral->draw_flat(); // no puedo, no la genera correctamente
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(0.6,5,0.6);
    Cilindro->draw_flat();
    glPopMatrix();
}

void _rosca::draw_gouraud(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-2.2,0);
    glScalef(0.55,5,0.55);
    //Espiral->draw_gouraud();  // no puedo
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(0.6,5,0.6);
    Cilindro->draw_gouraud();
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
    glRotatef(90,1,0,0);
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

void _agarre::draw_flat(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-4.9,0);
    Rosca->draw_flat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.9,0);
    glRotatef(90,1,0,0);
    glScalef(2.8,0.8,1.8);
    Anillo->draw_flat();
    glPopMatrix();
}

void _agarre::draw_gouraud(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-4.9,0);
    Rosca->draw_gouraud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.9,0);
    glRotatef(90,1,0,0);
    glScalef(2.8,0.8,1.8);
    Anillo->draw_gouraud();
    glPopMatrix();
}

// PALANCA
void _palanca::draw_point(float fd){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(fd,0,0,1);
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_point();
    glPopMatrix();
}

void _palanca::draw_line(float fd){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(fd,0,0,1);
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_line();
    glPopMatrix();
}

void _palanca::draw_fill(float fd){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(fd,0,0,1);
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_fill();
    glPopMatrix();
}

void _palanca::draw_chess(float fd){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(fd,0,0,1);
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_chess();
    glPopMatrix();
}

void _palanca::draw_flat(float fd){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(fd,0,0,1);
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_flat();
    glPopMatrix();
}

void _palanca::draw_gouraud(float fd){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(fd,0,0,1);
    glTranslatef(0,-3,0);
    glScalef(0.75,8,0.5);
    Cubo->draw_gouraud();
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

void _tornillo::draw_flat(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glScalef(0.5,1.3,0.5);
    Cono->draw_flat();
    glPopMatrix();
}

void _tornillo::draw_gouraud(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glScalef(0.5,1.3,0.5);
    Cono->draw_gouraud();
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
    Palanca->draw_point(-first_d);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_point(first_d);
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
    Palanca->draw_line(-first_d);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_line(first_d);
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
    Palanca->draw_fill(-first_d);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_fill(first_d);
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
    Palanca->draw_chess(-first_d);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_chess(first_d);
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

void _soporte::draw_flat(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(3,2.5,1.2);
    Cubo->draw_flat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Palanca->draw_flat(-first_d);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_flat(first_d);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Tornillo->draw_flat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Tornillo->draw_flat();
    glPopMatrix();
}

void _soporte::draw_gouraud(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(3,2.5,1.2);
    Cubo->draw_gouraud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Palanca->draw_gouraud(-first_d);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Palanca->draw_gouraud(first_d);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75,0,0);
    Tornillo->draw_gouraud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75,0,0);
    Tornillo->draw_gouraud();
    glPopMatrix();
}


// CAMPANA
void _campana::draw_point(){
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


void _campana::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-1.5,0);
    glScalef(2.5,0.75,2.5);
    Anillo->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_line();
    glPopMatrix();
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

void _campana::draw_flat(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-1.5,0);
    glScalef(2.5,0.75,2.5);
    Anillo->draw_flat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_flat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_flat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_flat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_flat();
    glPopMatrix();

}

void _campana::draw_gouraud(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,-1.5,0);
    glScalef(2.5,0.75,2.5);
    Anillo->draw_gouraud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_gouraud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,0.55);
    glRotatef(-6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_gouraud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(-5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_gouraud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55,0.75,-0.55);
    glRotatef(6,1,0,0);    // Sobre el eje X
    glRotatef(5,0,0,1);    // Sobre el eje Z
    glScalef(0.5,4,0.5);
    Cilindro->draw_gouraud();
    glPopMatrix();

}








// ESTRUCTURA
void _estructura::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1.25,0); // Lo muevo para arriba de forma que su parte baja toque el eje X
    Soporte->draw_point();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0); // Lo coloco debajo del soporte
    Campana->draw_point();
    glPopMatrix();
}


void _estructura::draw_line(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1.25,0);
    Soporte->draw_line();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0);
    Campana->draw_line();
    glPopMatrix();
}

void _estructura::draw_fill(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1.25,0);
    Soporte->draw_fill();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0);
    Campana->draw_fill();
    glPopMatrix();

}

void _estructura::draw_chess(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1.25,0);
    Soporte->draw_chess();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0);
    Campana->draw_chess();
    glPopMatrix();
}

void _estructura::draw_flat(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1.25,0);
    Soporte->draw_flat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0);
    Campana->draw_flat();
    glPopMatrix();

}

void _estructura::draw_gouraud(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,1.25,0);
    Soporte->draw_gouraud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-2.5,0);
    Campana->draw_gouraud();
    glPopMatrix();
}





// SACACORCHOS

void _sacacorchos::draw_point(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Estructura->draw_point();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,third_d,0);
    glRotatef(second_d,0,1,0);
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
    glTranslatef(0,third_d,0);
    glRotatef(second_d,0,1,0);
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
    glTranslatef(0,third_d,0);
    glRotatef(second_d,0,1,0);
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
    glTranslatef(0,third_d,0);
    glRotatef(second_d,0,1,0);
    glTranslatef(0,3,0);
    Agarre->draw_chess();
    glPopMatrix();
}

void _sacacorchos::draw_flat(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Estructura->draw_flat();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,third_d,0);
    glRotatef(second_d,0,1,0);
    glTranslatef(0,3,0);
    Agarre->draw_flat();
    glPopMatrix();
}

void _sacacorchos::draw_gouraud(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    Estructura->draw_gouraud();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,third_d,0);
    glRotatef(second_d,0,1,0);
    glTranslatef(0,3,0);
    Agarre->draw_gouraud();
    glPopMatrix();
}

















