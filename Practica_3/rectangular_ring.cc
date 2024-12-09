
#include "rectangular_ring.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_rectangular_ring::_rectangular_ring(int num_rotaciones)
{
    // El perfil exterior son solo dos puntos
    PerfilExterior.resize(2);
    PerfilExterior[0]=_vertex3f(0,0.5,0);                       // Vertice arriba izq
    PerfilExterior[1]=_vertex3f(0,-0.5,0);                       // Vertice abajo izq

    // El interior tiene 2 puntos también
    PerfilInterior.resize(2);
    PerfilInterior[0]=_vertex3f(0,0.5,0);                       // Vertice arriba izq
    PerfilInterior[1]=_vertex3f(0,-0.5,0);                       // Vertice abajo izq

    num_rotaciones = 40;


    // VERTICES
    int i, k;
    float radio_ext, radio_int, alpha = 2 * M_PI / num_rotaciones;
    int max_vertices = PerfilExterior.size() * num_rotaciones * 2;  // x2 porque tenemos dos perfiles distintos
    _vertex3f nuevo_vertice_ext, nuevo_vertice_int;

    // Metemos los vertices de los perfiles
    for (int j = 0; j < PerfilExterior.size(); j++){
        Vertices.push_back(PerfilExterior[j]);
        Vertices.push_back(PerfilInterior[j]);
    }

    i = 0;  // Para referirnos a los elementos del Perfil
    k = 0;  // Indice para controlar el ángulo
    for (int j = PerfilExterior.size(); j < max_vertices; j+=2){      // Añado los vertices de 2 en 2
        radio_ext = PerfilExterior[i].x;
        radio_int = PerfilInterior[i].x;
        if (j % PerfilExterior.size() == 0)
            k++;    // Todos los vectores de un perfil tienen el mismo angulo. Cuando los recorremos todos, actualizamos el indice k

        nuevo_vertice_ext.x = radio_ext * cos(alpha*k);
        nuevo_vertice_ext.y = PerfilExterior[i].y;
        nuevo_vertice_ext.z = - radio_ext * sin(alpha*k);

        nuevo_vertice_int.x = radio_int * cos(alpha*k);
        nuevo_vertice_int.y = PerfilInterior[i].y;
        nuevo_vertice_int.z = - radio_int * sin(alpha*k);

        Vertices[j] = nuevo_vertice_ext;
        Vertices[j+1] = nuevo_vertice_int;

        i = (i+1) % PerfilExterior.size();
    }



    // TRIANGULOS




}

