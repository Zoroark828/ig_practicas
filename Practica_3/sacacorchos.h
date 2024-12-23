
#ifndef SACACORCHOS_H
#define SACACORCHOS_H

#include "cylinder.h"
#include "cube.h"
#include "cone.h"
#include "spiral.h"
#include "rectangular_ring.h"
#include "ply_object.h"


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
};

class _tornillo {
    _cone * Cono;
public:
    _tornillo(_cone &Cone);
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
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

    void increase_first_degree(float d);
    void decrease_first_degree(float d);
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

    void increase_first_degree(float d);
    void decrease_first_degree(float d);
};

class _sacacorchos{
    const float MAX_FIRST_D = 10, MAX_SECOND_D = 10, MAX_THIRD_D = 10;
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
};

#endif


























