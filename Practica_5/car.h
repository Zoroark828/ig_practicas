
#ifndef CAR_H
#define CAR_H

#include "cylinder.h"
#include "cube.h"
#include "cone.h"


/*
Previo a hacer mi propio modelo, voy a intentar implementar el coche que se explica en el guión de prácticas.
Concretamente, el coche tal y como se indica en el grafo que aparece en el documento "como crear un grafo de
escena".

*/

class _wheel {
    _cylinder Cilindro;
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

class _wheels_axis {
    _wheel Rueda;       // para crear las 4 ruedas del eje
    _cylinder Cilindro; // para crear el eje como tal (un eje une dos ruedas)
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

class _platform {
    _wheels_axis Eje;   // Para crear los dos ejes de nuestro coche
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

class _headlight {
    _cone Cono;   // Para crear un faro del coche
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

class _chassis {
    _headlight Faro;    // Para añadir las dos luces que hay en el chasis
    _cube Cubo;         // Para crear los dos rectángulos que forman el chasis del coche
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};

class _car {
    _platform Plataforma;   // Los dos ejes del coche
    _chassis Chasis;        // El chasis como tal
public:
    void draw_point();
    void draw_line();
    void draw_fill();
    void draw_chess();
};


#endif
