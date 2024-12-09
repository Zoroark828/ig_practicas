
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
    _spiral Espiral;
    //_cylinder Cilindro;
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};


class _pincho {
    _spiral Espiral;
    _cylinder Cilindro;
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};


class _pepe {
    _spiral Espiral;
    _cylinder Cilindro;
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};


class _pepon {
    _spiral Espiral;
    _cylinder Cilindro;
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};






class _sacacorchos{
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

#endif
