
#include "cube.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cube::_cube(float Size)
{
    Vertices.resize(8);

    // Primero indicamos las posiciones de los 8 vertices del cubo
    // Cara "de enfrente":
    Vertices[0]=_vertex3f(-Size/2,Size/2,Size/2);           // vertice arriba izq
    Vertices[1]=_vertex3f(-Size/2,-Size/2,Size/2);          // vertice abajo izq
    Vertices[2]=_vertex3f(Size/2,-Size/2,Size/2);           // abajo derecha
    Vertices[3]=_vertex3f(Size/2,Size/2,Size/2);            // arriba derecha
    // Cara "del fondo":
    Vertices[4]=_vertex3f(-Size/2,Size/2,-Size/2);          // vertice arriba izq
    Vertices[5]=_vertex3f(-Size/2,-Size/2,-Size/2);         // vertice abajo izq
    Vertices[6]=_vertex3f(Size/2,-Size/2,-Size/2);          // abajo derecha
    Vertices[7]=_vertex3f(Size/2,Size/2,-Size/2);           // arriba derecha


    // Definimos sus triángulos, de forma antihoraria en cada cara
    Triangles.resize(12);

    Triangles[0]=_vertex3ui(0,1,2);
    Triangles[1]=_vertex3ui(0,2,3);

    Triangles[2]=_vertex3ui(3,2,6);
    Triangles[3]=_vertex3ui(3,6,7);

    Triangles[4]=_vertex3ui(7,6,5);
    Triangles[5]=_vertex3ui(7,5,4);

    Triangles[6]=_vertex3ui(4,5,1);
    Triangles[7]=_vertex3ui(4,1,0);

    Triangles[8]=_vertex3ui(4,0,3);
    Triangles[9]=_vertex3ui(4,3,7);

    Triangles[10]=_vertex3ui(1,5,6);
    Triangles[11]=_vertex3ui(1,6,2);
}


