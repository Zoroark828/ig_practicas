/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "axis_revolution.h"
#include <cmath>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_axis_revolution::_axis_revolution(int num_rotaciones)
{
    // Para esta clase voy a crear un cilindro, por lo que su perfil tendrá que ser un rectángulo (1 de alto x 0.5 de ancho)
    Perfil.resize(4);
    Vertices[0]=_vertex3f(0,1,0);                       // Vertice arriba izq
    Vertices[1]=_vertex3f(0,0,0);                       // Vertice abajo izq
    Vertices[2]=_vertex3f(0.5,0,0);                     // Vertice abajo derecha
    Vertices[3]=_vertex3f(0.5,1,0);                     // Vertice arriba derecha


    circular_sweeping(Perfil,num_rotaciones); // Se encarga de hacer la rotación y generar los vertices y triángulos
}




void _axis_revolution::circular_sweeping(vector<_vertex3f> Perfil, int num_rotaciones){
    float radio,
        alpha = 2 * M_PI / num_rotaciones;

    // VERTICES
    Vertices.resize(Perfil.size() * num_rotaciones);

    // Primero añado los 4 vertices del Perfil          (no hace falta)
    /*for (int  i = 0; i < Perfil.size(); i++){
        Vertices[i] = Perfil[i];
    }*/

    // Para un perfil de 1 solo vertice:
    for (int i = 0; i < num_rotaciones; i++){
        radio = Perfil[i].x;

        Vertices[i].x = radio * cos(alpha*i);
        Vertices[i].y = Perfil[0].y;    // Giramos sobre el eje Y, es siempre la misma
        Vertices[i].z = - radio * sin(alpha*i);
    }

    // Para uno de más vertices:
    for (int j = Perfil.size(); j < Vertices.size(); j++){
        for (int i = 0; i < num_rotaciones; i++){
            radio = Perfil[i].x;

            Vertices[j].x = radio * cos(alpha*i);
            Vertices[j].y = Perfil[0].y;    // Giramos sobre el eje Y, es siempre la misma
            Vertices[j].z = - radio * sin(alpha*i);
        }
    }




    // TRIÁNGULOS



}















