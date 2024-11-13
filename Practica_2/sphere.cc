
#include "sphere.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_sphere::_sphere(int num_rotaciones)
{
    // Creamos el perfil de la esfera. Será una circunferencia. Utilizo una función auxiliar, para organizarlo mejor
    createSphereProfile(41);    // Quiero que el perfil tenga 10 vértices, para que sea más realista

    num_rotaciones =40;
    // Hago el barrido circular de dicho perfil
    circularSweeping(num_rotaciones);
}

void _sphere::createSphereProfile(int num_vertices){
    /* Para calcular los vertices de la semicircunferencia necesitamos usar las funciones trigonométricas.
    Es como el planteamiento seguido en el guión de prácticas para el barrido circular, solo que
    esta vez queremos usar los ejes X e Y, en vez del X y Z, por lo que la z siempre valdrá 0.
            x = R * cos(angulo)
            y = R * sen(angulo)
            z = 0

    R es el radio de la semicircunferencia. En nuestro caso será 0'5 porque queremos que la esfera tenga diámetro 1.
    */
    double radio = 0.5, incremento, angulo;
    Perfil.resize(num_vertices);

    // Al ser una semicircunferencia, repartimos sus 180 (PI) grados entre el número de vertices
    // Restamos uno porque el primer vertice que añadamos no cuenta, ya que no tendrá incremento
    incremento = M_PI /(num_vertices-1);

    for (int i = 0; i < num_vertices; i++){
        /*
        Los vertices de la circunferencia se crean de abajo a arriba, por lo que empezamos por un ángulo
        igual a -90. A este ángulo le tendremos que sumar el incremento definido antes teniendo en cuenta
        el vértice por el que vamos (de ahi que multipliquemos su indice i).
        */
        angulo = -M_PI/2 + i*incremento;
        Perfil[i].x = radio * cos(angulo);
        Perfil[i].y = radio * sin(angulo);
        Perfil[i].z = 0;
    }
}








