
#include "axis_revolution.h"
#include <cmath>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _axis_revolution::circularSweeping(int num_rotaciones){
    int i, k;
    float radio, alpha = 2 * M_PI / num_rotaciones;

    //////////// VÉRTICES ////////////
    Vertices.resize(Perfil.size() * num_rotaciones);

    // Primero metemos los vertices del propio Perfil
    for (int j = 0; j < Perfil.size(); j++){
        Vertices[j] = Perfil[j];
    }

    i = 0;  // Para referirnos a los elementos del Perfil
    k = 0;  // Indice para controlar el ángulo
    for (int j = Perfil.size(); j < Vertices.size(); j++){      // Recorro cada vertice que debo crear
        radio = Perfil[i].x;
        if (j % Perfil.size() == 0)
            k++;    // Todos los vectores de un perfil tienen el mismo angulo. Cuando los recorremos todos, actualizamos el indice k

        Vertices[j].x = radio * cos(alpha*k);
        Vertices[j].y = Perfil[i].y;
        Vertices[j].z = - radio * sin(alpha*k);

        i = (i+1) % Perfil.size(); // Aumento i en 1 pero no debo pasarme del num total de vertices del perfil
    }


    //////////// TRIÁNGULOS ////////////
    // La siguiente función se encarga de su generación
    trianglesGeneration(num_rotaciones);
}


_vertex3ui _axis_revolution::trianglesSum(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax){
    _vertex3ui t3;
    t3._0 = (t1._0 + t2._0) % valorMax;
    t3._1 = (t1._1 + t2._1) % valorMax;
    t3._2 = (t1._2 + t2._2) % valorMax;

    return t3;
}



void _axis_revolution::trianglesGeneration(int num_rotaciones){
    int perfil_size = Perfil.size();        // Para evitar llamar tantas veces a ambas funciones
    int vertices_size = Vertices.size();
    _vertex3ui tP, tI;                      // Triangulos par e impar
    _vertex3ui tU;  //triangulo unidad que usaré para las sumas
    tU._0 = 1;
    tU._1 = 1;
    tU._2 = 1;
    _vertex3ui tV;  //triangulo con el número de vectores en el perfil original
    tV._0 = perfil_size;
    tV._1 = perfil_size;
    tV._2 = perfil_size;


    // Recorreremos los "triangulos" viendo los puntos como si formaran una matriz como se explica en el guión de practicas
    Triangles.resize((perfil_size-1) * num_rotaciones * 2);

    // El valor inicial del primer triángulo "par" siempre será T(numFila, numVerticesPerfil, numFila+1)
    // Como empezaremos por la fila numero 0, el triángulo será T(0,Perfil.size(),1)
    tP._0 = 0;
    tP._1 = perfil_size;
    tP._2 = 1;

    // El valor del primer triángulo "impar" será T(numFila+1, Perfil.size(), Perfil.size()+1)
    // Siempre empezamos por la fila 0, así que será T(1,Perfil.size(), Perfil.size()+1)
    tI._0 = 1;
    tI._1 = perfil_size;
    tI._2 = perfil_size+1;

    int i = 0;  // indice para ir llenando el vector de triangulos

    for (int f = 0; f < (perfil_size - 1); f++){    // Recorremos las filas de la "matriz"
        // Actualizo los triángulos según la fila
        if (f != 0){
            tP = trianglesSum(tP, tU, vertices_size);
            tI = trianglesSum(tI, tU, vertices_size);
        }

        for (int c = 0; c < (num_rotaciones); c++){ // Recorremos sus columnas
            if (c == 0){
                Triangles[i] = tP;
                Triangles[i+1] = tI;
            }
            else{
                Triangles[i] = trianglesSum(Triangles[i-2], tV, vertices_size);
                Triangles[i+1] = trianglesSum(Triangles[i-1], tV, vertices_size);
            }

            i+=2;
        }
    }
}











