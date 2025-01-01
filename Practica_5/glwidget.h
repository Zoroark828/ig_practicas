/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/gl.h>
#include <QWindow>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <filesystem>
#include <iostream>
#include "vertex.h"
#include "colors.h"
#include "axis.h"
#include "tetrahedron.h"
#include "cube.h"
#include "ply_object.h"
#include "cone.h"
#include "cylinder.h"
#include "sphere.h"
#include "spiral.h"
#include "rectangular_ring.h"
#include "car.h"
#include "sacacorchos.h"
#include <QTimer>
#include <QImageReader>
#include "chessboard.h"


namespace _gl_widget_ne {

  const float X_MIN=-.1;
  const float X_MAX=.1;
  const float Y_MIN=-.1;
  const float Y_MAX=.1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;  // 1000
  const float DEFAULT_DISTANCE=2;
  const float ANGLE_STEP=1;

  typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS} _mode_draw;
  typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE,OBJECT_PLY,OBJECT_CONE,OBJECT_CYLINDER,OBJECT_SPHERE, OBJECT_AUX, OBJECT_SACACORCHOS, OBJECT_CHESSBOARD} _object;
}

class _window;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();

  // Nuevas:
  void primera_luz();
  void segunda_luz();
  void definir_material();
  void initialize_texture();
  void pick();

public slots:   // Necesario este tipo para QTimer
  void animation(); // Funcion encargada de producir la animación


protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;
  // Nuevas Practica 5:
  void mouseMoveEvent(QMouseEvent *Mouseevent) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent *Mouseevent) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent *Mouseevent) Q_DECL_OVERRIDE;
  void wheelEvent(QWheelEvent *Wheelevent) Q_DECL_OVERRIDE;


private:
  _window *Window;

  _axis Axis;
  _tetrahedron Tetrahedron;
  _cube Cube;
  _ply_object PlyObject;
  _cone Cone;
  _cylinder Cylinder;
  _sphere Sphere;
  _spiral Spiral;
  _rectangular_ring Ring;
  _sacacorchos * Sacacorchos;
  _chessboard Chessboard;

  _spiral AUX;    ////////// Borra, solo era para conseguir fotos


  // Necesarios para la animación
  QTimer * timer;
  bool incrementando;

  // Necesario para la textura
  GLuint texChessboard; // Guardará el ID de la textura para el chessboard


  _gl_widget_ne::_object Object;

  bool Draw_point;
  bool Draw_line;
  bool Draw_fill;
  bool Draw_chess;
  // Nuevos P4:
  bool DrawFlat;
  bool DrawGouraud;
  bool DrawTextureUnlit;
  bool DrawTextureFlat;
  bool DrawTextureGouraud;
  bool FirstLight;
  bool SecondLight;
  int Material; // Entero que valdrá 0, 1 o 2 dependiendo del material elegido
  int rotacion_luz; // Número de grados que gira la segunda luz

  // Nuevos P5:
  bool PerspectiveP;    // Si es true, proyección de perspectiva. Si es false, proyección paralela
  int Mouse_pos_x;  // variables para guardar la posición del ratón
  int Mouse_pos_y;





  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;
};

#endif
