
#include "sphere.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_sphere::_sphere(int n_r)
{
    // Creamos el perfil de la esfera. Será una circunferencia. Utilizo una función auxiliar, para organizarlo mejor
    createSphereProfile(n_r);

    // Hago el barrido circular de dicho perfil
    num_rotaciones = n_r;
    circularSweeping(n_r);
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

    /* Defino los dos primeros vértices primero, de forma que el vertice 0 sea el de arriba
    a la izquierda (sobre el eje Y) y el vértice 1 sea el punto más bajo del perfil, el que toca
    el eje Y abajo a la izquierda.
    Ejemplo: si el perfil tiene n vertices, estos se definen así:   (se supone que es una semicircunferencia)
    0
       n
         n-1
          ...
         3
       2
    1
    */
    Perfil[0].x = 0;
    Perfil[0].y = radio;
    Perfil[0].z = 0;

    Perfil[1].x = 0;
    Perfil[1].y = - radio;
    Perfil[1].z = 0;

    for (int i = 2; i < num_vertices; i++){
        /*
        Los vertices de la circunferencia se crean de abajo a arriba, por lo que empezamos por un ángulo
        igual a -90. A este ángulo le tendremos que sumar el incremento definido antes teniendo en cuenta
        el vértice por el que vamos (de ahi que multipliquemos su indice i).
        */
        angulo = -M_PI/2 + (i-1)*incremento;
        Perfil[i].x = radio * cos(angulo);
        Perfil[i].y = radio * sin(angulo);
        Perfil[i].z = 0;
    }
}






