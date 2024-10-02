/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "object3d.h"

using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_line()
{
    int vertex1, vertex2, vertex0;

    // PRIMERA FORMA DE HACERLO:
    /*
    glBegin(GL_LINES);
    // Para cada triángulo que componga al objeto...
    for (unsigned int i = 0; i < Triangles.size(); i++){
        vertex0 = Triangles[i]._0;  //(indices de cada vertice del triángulo)
        vertex1 = Triangles[i]._1;
        vertex2 = Triangles[i]._2;

        // Dibujo los tres lados del triangulo:
        glVertex3fv((GLfloat *) &Vertices[vertex0]);
        glVertex3fv((GLfloat *) &Vertices[vertex1]);

        glVertex3fv((GLfloat *) &Vertices[vertex2]);
        glVertex3fv((GLfloat *) &Vertices[vertex1]);

        glVertex3fv((GLfloat *) &Vertices[vertex2]);
        glVertex3fv((GLfloat *) &Vertices[vertex0]);
    }
    glEnd();
    */

    // SEGUNDA FORMA DE HACERLO:
    /*
    glBegin(GL_LINE_STRIP);
    // Para cada triángulo que componga al objeto...
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
    */

    // Tercera forma:
    glColor3f(0,0,0);
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


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
    int vertex0, vertex1, vertex2;

    // PRIMERA FORMA
    /*
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
    */

    // SEGUNDA FORMA, cambiando el modo de poligono
    glColor3f(1,0,0);
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


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess()
{
    int vertex0, vertex1, vertex2;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < Triangles.size(); i++){
        // Queremos dibujar usando dos colores distintos...
        if (i%2 == 0)
            glColor3f(1,0,0);   //rojo
        else
            glColor3f(0,0,1);   //azul

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
