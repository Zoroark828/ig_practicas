
#ifndef SACACORCHOS_H
#define SACACORCHOS_H

#include "cylinder.h"
#include "cube.h"
#include "cone.h"
#include "spiral.h"
#include "rectangular_ring.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/


class _rosca {
    _spiral * Espiral;
    _cylinder * Cilindro;
public:
    _rosca(_cylinder &Cylinder, _spiral &Spiral);
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
    // Funciones para poder iluminar el modelo
    void draw_flat();
    void draw_gouraud();
};

class _agarre {
    _rosca * Rosca;
    _rectangular_ring * Anillo;
public:
    _agarre(_cylinder &Cylinder, _rectangular_ring &Ring, _spiral &Spiral);
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
    // Funciones para poder iluminar el modelo
    void draw_flat();
    void draw_gouraud();
};

class _palanca{
    _cube * Cubo;
public:
    _palanca(_cube &Cube);
    void draw_point(float fd);
    void draw_line(float fd);
    void draw_fill(float fd);
    void draw_chess(float fd);

    void increase_first_degree(float d);
    void decrease_first_degree(float d);
    // Funciones para poder iluminar el modelo
    void draw_flat(float fd);
    void draw_gouraud(float fd);
};

class _tornillo {
    _cone * Cono;
public:
    _tornillo(_cone &Cone);
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
    // Funciones para poder iluminar el modelo
    void draw_flat();
    void draw_gouraud();
};

class _soporte {
    float first_d;
    _cube * Cubo;
    _palanca * Palanca;
    _tornillo * Tornillo;
public:
    _soporte(float f_d, _cube &Cube, _cone &Cone);
    ~_soporte(){delete Palanca; delete Tornillo;}
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();

    void modify_first_degree(float d);
    // Funciones para poder iluminar el modelo
    void draw_flat();
    void draw_gouraud();
};

class _campana {
    _cylinder * Cilindro;
    _rectangular_ring * Anillo;
public:
    _campana(_cylinder &Cylinder, _rectangular_ring &Ring);
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
    // Funciones para poder iluminar el modelo
    void draw_flat();
    void draw_gouraud();
};

class _estructura {
    _campana * Campana;
    _soporte * Soporte;
public:
    _estructura(float f_d, _cube &Cube, _cone &Cone, _cylinder &Cylinder, _rectangular_ring &Ring);
    ~_estructura(){delete Campana; delete Soporte;}
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();

    void modify_first_degree(float d);
    // Funciones para poder iluminar el modelo
    void draw_flat();
    void draw_gouraud();
};

class _sacacorchos{
    const float MAX_FIRST_D = 90, MAX_THIRD_D = 1.5;
    const float MIN_FIRST_D = 10, MIN_THIRD_D = -0.2;
    float first_d, second_d, third_d;   // valor de cada grado de libertad
    float first_d_rate, second_d_rate, third_d_rate;   // Valor sumado a los grados de libertad

    _estructura * Estructura;
    _agarre * Agarre;
public:
    _sacacorchos(_cube &Cube, _cone &Cone, _cylinder &Cylinder, _rectangular_ring &Ring, _spiral &Spiral);
    ~_sacacorchos(){delete Estructura; delete Agarre;}
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();

    // Funciones para incrementar/decrementar los grados de libertad
    void increase_first_degree();   // Translacion palas
    void increase_second_degree();  // Translacion soporte
    void increase_third_degree();   // Rotacion soporte
    void decrease_first_degree();
    void decrease_second_degree();
    void decrease_third_degree();

    // Funciones para cambiar la cantidad que se modifica al incrementar/decrementar los grados de libertad
    // Lo aumentan/decrementan de 5 en 5
    void increase_rate_first_degree();   // Translacion palas
    void increase_rate_second_degree();  // Translacion soporte
    void increase_rate_third_degree();   // Rotacion soporte
    void decrease_rate_first_degree();
    void decrease_rate_second_degree();
    void decrease_rate_third_degree();

    // Funciones que calculan el valor de un grado dado el valor de otro
    float equivalent_degrees_first(float fd);   // Devuelve el nuevo valor de second
    float equivalent_degrees_third(float td);   // Devuelve el nuevo valor de first

    // Funciones para poder iluminar el modelo
    void draw_flat();
    void draw_gouraud();

    // Getter necesarios para que la animación sea infinita en _gl_widget
    float getFirst_D(){
        return first_d;
    }

    float getMax_First_D(){
        return MAX_FIRST_D;
    }

    float getMin_First_D(){
        return MIN_FIRST_D;
    }
};

#endif


























