/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "object3d.h"

using namespace _colors_ne;



////////////////// CALCULO NORMALES
void _object3D::calculo_normales(){
    calculo_normales_triangulos();
    calculo_normales_vertices();
}

void _object3D::calculo_normales_triangulos(){
    _vertex3f A, B; // Vectores que obtenemos gracias a los puntos de cada triangulo
    _vertex3f N;
    NormalesTriangulos.resize(Triangles.size());

    for (int i = 0; i < Triangles.size(); i++){
        // Utilizamos los 3 puntos del triangulo para obtener dos vectores
        // El vector A = P1 - P0 y el vector B es P2 - P0
        A = Vertices[Triangles[i]._1] - Vertices[Triangles[i]._0];
        B = Vertices[Triangles[i]._2] - Vertices[Triangles[i]._0];

        // La normal de este triángulo será el producto (vectorial) de A*B
        /* Para cada componente se calcula así
        aux.x = A.y * B.z - A.z * B.y;
        aux.y = A.z * B.x - A.x * B.z;
        aux.z = A.x * B.y - A.y * B.x;
        No obstante, hay una función de _vertex3 que lo hace automaticamente xd
        */
        N = A.cross_product(B);

        // También es importante normalizar el vector
        N.normalize();

        NormalesTriangulos[i] = N;
    }
}

void _object3D::calculo_normales_vertices(){
    vector<_vertex3f> normTriangParticip;   // Vector en el que iré guardando las normales de los triangulos en los que el vertice participe
    _vertex3f N;
    NormalesVertices.resize(Vertices.size());

    // La normal de cada vertice es la media de las normales de los triángulos en los que dicho vertice "participa"

    for (int i = 0; i < Vertices.size(); i++){
        for (int j = 0; j < Triangles.size(); j++){ // Busco las normales de los triangulos en los que aparece este vertice
            if (Vertices[Triangles[j]._0] == Vertices[i] ||
                    Vertices[Triangles[j]._1] == Vertices[i] ||
                    Vertices[Triangles[j]._2] == Vertices[i]){
                normTriangParticip.push_back(NormalesTriangulos[j]);
            }
        }

        for (int k = 0; k < normTriangParticip.size(); k++){
            N += normTriangParticip[k]; // Sumo en N todas las normales en las que participa
        }

        // Divido para calcular la media, normalizo y añado la nueva normal
        N /= normTriangParticip.size();
        N.normalize();
        NormalesVertices[i] = N;

        // Antes de pasar al siguiente vertice tengo que vacíar el vector auxiliar
        normTriangParticip.clear();
        N = _vertex3f(0,0,0);
    }

}







////////////////// FUNCIONES DIBUJO

void _object3D::draw_line()
{
    int vertex1, vertex2, vertex0;

    glColor3fv((GLfloat *) &BLACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < Triangles.size(); i++){
        vertex0 = Triangles[i]._0;  //(indices de cada vertice del triángulo)
        vertex1 = Triangles[i]._1;
        vertex2 = Triangles[i]._2;

        // Dibujo los tres vertices del triangulo. OpenGL hace una linea del primero al segundo,
        // del segundo al tercero y del tercero al primero...
        glVertex3fv((GLfloat *) &Vertices[vertex0]);
        glVertex3fv((GLfloat *) &Vertices[vertex1]);
        glVertex3fv((GLfloat *) &Vertices[vertex2]);
    }
    glEnd();
}

void _object3D::draw_fill()
{
    int vertex0, vertex1, vertex2;

    glColor3fv((GLfloat *) &RED);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < Triangles.size(); i++){
        vertex0 = Triangles[i]._0;  //(indices de cada vertice del triángulo)
        vertex1 = Triangles[i]._1;
        vertex2 = Triangles[i]._2;

        // Defino los tres vertices del triangulo. OpenGL define el triángulo y lo colorea
        glVertex3fv((GLfloat *) &Vertices[vertex0]);
        glVertex3fv((GLfloat *) &Vertices[vertex1]);
        glVertex3fv((GLfloat *) &Vertices[vertex2]);
    }
    glEnd();
}

void _object3D::draw_chess()
{
    int vertex0, vertex1, vertex2;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < Triangles.size(); i++){
        // Queremos dibujar usando dos colores distintos...
        if (i%2 == 0)
            glColor3fv((GLfloat *) &RED);
        else
            glColor3fv((GLfloat *) &BLUE);

        vertex0 = Triangles[i]._0;  //(indices de cada vertice del triángulo)
        vertex1 = Triangles[i]._1;
        vertex2 = Triangles[i]._2;

        // Defino los tres vertices del triangulo. OpenGL define el triángulo y lo colorea
        glVertex3fv((GLfloat *) &Vertices[vertex0]);
        glVertex3fv((GLfloat *) &Vertices[vertex1]);
        glVertex3fv((GLfloat *) &Vertices[vertex2]);
    }
    glEnd();
}



void _object3D::draw_flat(){
    int vertex0, vertex1, vertex2;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glBegin(GL_TRIANGLES);
    glShadeModel(GL_FLAT);  // Modo de sombreado FLAT
    for (unsigned int i = 0; i < Triangles.size(); i++){
        vertex0 = Triangles[i]._0;
        vertex1 = Triangles[i]._1;
        vertex2 = Triangles[i]._2;

        glNormal3fv((GLfloat *) &NormalesTriangulos[i]);
        glVertex3fv((GLfloat *) &Vertices[vertex0]);
        glVertex3fv((GLfloat *) &Vertices[vertex1]);
        glVertex3fv((GLfloat *) &Vertices[vertex2]);
    }
    glEnd();
}

void _object3D::draw_gouraud(){
    int vertex0, vertex1, vertex2, j = 0;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);
    glShadeModel(GL_SMOOTH);  // Modo de sombreado SMOOTH (GOURAUD)
    for (unsigned int i = 0; i < Triangles.size(); i++){
        vertex0 = Triangles[i]._0;
        vertex1 = Triangles[i]._1;
        vertex2 = Triangles[i]._2;

        glNormal3fv((GLfloat *) &NormalesVertices[vertex0]);
        glVertex3fv((GLfloat *) &Vertices[vertex0]);
        glNormal3fv((GLfloat *) &NormalesVertices[vertex1]);
        glVertex3fv((GLfloat *) &Vertices[vertex1]);
        glNormal3fv((GLfloat *) &NormalesVertices[vertex2]);
        glVertex3fv((GLfloat *) &Vertices[vertex2]);
        j+=3;
    }
    glEnd();
}

void _object3D::draw_texture_unlit(){

}

void _object3D::draw_texture_flat(){

}

void _object3D::draw_texture_gouraud(){

}























