
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
    void draw_point();
    void draw_line(int alpha);
    void draw_fill();
    void draw_chess(int alpha);
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
    _cube * Cubo;
    _palanca * Palanca;
    _tornillo * Tornillo;
public:
    _soporte(_cube &Cube, _cone &Cone);
    ~_soporte(){delete Palanca; delete Tornillo;}
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
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
    _estructura(_cube &Cube, _cone &Cone, _cylinder &Cylinder, _rectangular_ring &Ring);
    ~_estructura(){delete Campana; delete Soporte;}
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

class _sacacorchos{
    _estructura * Estructura;
    _agarre * Agarre;
public:
    _sacacorchos(_cube &Cube, _cone &Cone, _cylinder &Cylinder, _rectangular_ring &Ring, _spiral &Spiral);
    ~_sacacorchos(){delete Estructura; delete Agarre;}
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

#endif
