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
    Perfil[0]=_vertex3f(0,0,0);                       // Vertice abajo izq
    Perfil[1]=_vertex3f(0.5,0,0);                     // Vertice abajo derecha
    Perfil[2]=_vertex3f(0.5,1,0);                     // Vertice arriba derecha
    Perfil[3]=_vertex3f(0,1,0);                       // Vertice arriba izq


    num_rotaciones = 30;
    circular_sweeping(Perfil,num_rotaciones); // Se encarga de hacer la rotación y generar los vertices y triángulos
}




void _axis_revolution::circular_sweeping(vector<_vertex3f> Perfil, int num_rotaciones){
    int i, k;
    float   radio,
            alpha = 2 * M_PI / num_rotaciones;

    // VERTICES
    Vertices.resize(Perfil.size() * num_rotaciones);

    // Primero metemos los vertices del perfil
    for (int j = 0; j < Perfil.size(); j++){
        Vertices[j] = Perfil[j];
    }

    i = 0;  // Para referirnos a los elementos del Perfil
    k = 0;  // Indice
    for (int j = Perfil.size(); j < Vertices.size(); j++){      // Recorro cada vertice que debo crear
        radio = Perfil[i].x;
        if (j % Perfil.size() == 0) k++;    // Todos los vectores de un perfil tienen el mismo angulo. Cuando los recorremos todos, actualizamos el indice k

        Vertices[j].x = radio * cos(alpha*k);
        Vertices[j].y = Perfil[i].y;
        Vertices[j].z = - radio * sin(alpha*k);

        i = (i+1) % Perfil.size(); // Aumento i en 1 pero no debo pasarme del num de vertices del perfil
    }




    // TRIÁNGULOS
    // Recorremos los "triangulos" viendo los puntos como si formaran una matriz como la del guión de practicas
    Triangles.resize((Perfil.size()-1) * num_rotaciones * 2);

    _vertex3ui tA, tB;

    // El valor inicial del primer triángulo par siempre será T(numFila, numVerticesPerfil, numFila+1)
    // Como empezaremos por la fila numero 0, el triángulo será T(0,Perfil.size(),1)
    tA._0 = 0;
    tA._1 = Perfil.size();
    tA._2 = 1;

    // El valor del primer triángulo "impar" será T(numFila+1, Perfil.size(), Perfil.size()+1)
    // Siempre empezamos por la fila 0 así que será T(1,Perfil.size(), Perfil.size()+1)
    tB._0 = 1;
    tB._1 = Perfil.size();
    tB._2 = Perfil.size()+1;


    _vertex3ui tU;  //triangulo unidad que usaré para las sumas
    tU._0 = 1;
    tU._1 = 1;
    tU._2 = 1;

    _vertex3ui tV;  //triangulo con el número de vectores en el perfil original
    tV._0 = Perfil.size();
    tV._1 = Perfil.size();
    tV._2 = Perfil.size();

    i = 0;  // para ir llenando el vector de triangulos

    for (int f = 0; f < (Perfil.size() - 1); f++){
        // aqui actualizo tA y tb segun la fila
        if (f != 0){
            tA = sumaTriangulos(tA, tU, Vertices.size());
            tB = sumaTriangulos(tB, tU, Vertices.size());
        }

        for (int c = 0; c < (num_rotaciones); c++){
            if (c == 0){
                Triangles[i] = tA;
                Triangles[i+1] = tB;
            }
            else{
                Triangles[i] = sumaTriangulos(Triangles[i-2], tV, Vertices.size());
                Triangles[i+1] = sumaTriangulos(Triangles[i-1], tV, Vertices.size());
            }

            cout << "Para " << i << " tenemos:" << endl;
            cout << "x - " << Triangles[i].x << endl;
            cout << "y - " << Triangles[i].y << endl;
            cout << "z - " << Triangles[i].z << endl << endl;

            cout << "Para " << i+1 << " tenemos:" << endl;
            cout << "x - " << Triangles[i+1].x << endl;
            cout << "y - " << Triangles[i+1].y << endl;
            cout << "z - " << Triangles[i+1].z << endl << endl;

            i+=2;
        }
    }
    cout << "valor i: " << i << endl;
    cout << "perfil size: " << Perfil.size() << endl;
    cout << "num rotaciones: " << num_rotaciones << endl;
    cout << "num triangulos: " << Triangles.size() << endl;


}

_vertex3ui _axis_revolution::sumaTriangulos(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax){
    _vertex3ui t3;
    t3._0 = (t1._0 + t2._0) % valorMax;
    t3._1 = (t1._1 + t2._1) % valorMax;
    t3._2 = (t1._2 + t2._2) % valorMax;

    return t3;
}



void _axis_revolution::trianglescalc(vector<_vertex3f> Perfil, int f, int c, _vertex3ui &t0, _vertex3ui &t1){

}




/*  // vertices comprobación
        cout << "Para " << j << " tenemos:" << endl;
        cout << "x - " << Vertices[j].x << endl;
        cout << "y - " << Vertices[j].y << endl;
        cout << "z - " << Vertices[j].z << endl << endl;
*/









