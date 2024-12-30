/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _basic_object3D
{
  public:
  vector<_vertex3ui> Triangles;
  vector<_vertex3f> NormalesTriangulos, NormalesVertices;

  void draw_line();
  void draw_fill();
  void draw_chess();

  // Nuevos practica 4:
  void calculo_normales();
  void calculo_normales_triangulos();
  void calculo_normales_vertices();

  void draw_flat();
  void draw_gouraud();
  void draw_texture_unlit();
  void draw_texture_flat();
  void draw_texture_gouraud();

};

#endif // OBJECT3D_H
