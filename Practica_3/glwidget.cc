/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */


#include "glwidget.h"
#include "window.h"

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);

  Sacacorchos = new _sacacorchos(Cube, Cone, Cylinder, Ring, Spiral);

  timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(animation()));
}


/*****************************************************************************//**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){
        case Qt::Key_1:Object=OBJECT_TETRAHEDRON;break;
        case Qt::Key_2:Object=_gl_widget_ne::OBJECT_CUBE;break;
        case Qt::Key_3:Object=_gl_widget_ne::OBJECT_CONE;break;
        case Qt::Key_4:Object=_gl_widget_ne::OBJECT_CYLINDER;break;
        case Qt::Key_5:Object=_gl_widget_ne::OBJECT_SPHERE;break;
        case Qt::Key_6:Object=_gl_widget_ne::OBJECT_PLY;break;
        case Qt::Key_7:Object=_gl_widget_ne::OBJECT_SACACORCHOS;break;
        case Qt::Key_8:Object=_gl_widget_ne::OBJECT_AUX;break;

        case Qt::Key_P:Draw_point=!Draw_point;break;
        case Qt::Key_L:Draw_line=!Draw_line;break;
        case Qt::Key_F:Draw_fill=!Draw_fill;break;
        case Qt::Key_C:Draw_chess=!Draw_chess;break;

        case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
        case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
        case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
        case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
        case Qt::Key_N:Observer_distance*=1.2;break;
        case Qt::Key_M:Observer_distance/=1.2;break;

        // Teclas para controlar los grados de libertad del sacacorchos + animacion

        case Qt::Key_Q:Sacacorchos->increase_first_degree();break;
        case Qt::Key_W:Sacacorchos->decrease_first_degree();break;
        case Qt::Key_S:Sacacorchos->increase_second_degree();break;
        case Qt::Key_D:Sacacorchos->decrease_second_degree();break;
        case Qt::Key_Z:Sacacorchos->increase_third_degree();break;
        case Qt::Key_X:Sacacorchos->decrease_third_degree();break;
        case Qt::Key_A:if(timer->isActive()) timer->stop();else timer->start(20);break;

        case Qt::Key_E:Sacacorchos->increase_rate_first_degree();break;
        case Qt::Key_R:Sacacorchos->decrease_rate_first_degree();break;
        case Qt::Key_T:Sacacorchos->increase_rate_second_degree();break;
        case Qt::Key_Y:Sacacorchos->decrease_rate_second_degree();break;
        case Qt::Key_U:Sacacorchos->increase_rate_third_degree();break;
        case Qt::Key_I:Sacacorchos->decrease_rate_third_degree();break;

  }

  update();
}

/*****************************************************************************//**
 * Animación
 *
 *
 *
 *****************************************************************************/

void _gl_widget::animation(){
    if (Sacacorchos->getFirst_D() == Sacacorchos->getMax_First_D())
        incrementando = false;  // Necesito que baje
    else if (Sacacorchos->getFirst_D() == Sacacorchos->getMin_First_D())
        incrementando = true;

    if (incrementando)
        Sacacorchos->increase_first_degree();
    else
        Sacacorchos->decrease_first_degree();

    update();
}



/*****************************************************************************//**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}



/*****************************************************************************//**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}



/*****************************************************************************//**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
}


/*****************************************************************************//**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{
  Axis.draw_line();

  if (Draw_point){
    glPointSize(5);
    glColor3fv((GLfloat *) &BLACK);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;
    case OBJECT_CUBE:Cube.draw_point();break;
    case OBJECT_CONE:Cone.draw_point();break;
    case OBJECT_CYLINDER:Cylinder.draw_point();break;
    case OBJECT_SPHERE:Sphere.draw_point();break;
    case OBJECT_PLY:PlyObject.draw_point();break;
    case OBJECT_AUX:AUX.draw_point();break;
    case OBJECT_SACACORCHOS:Sacacorchos->draw_point();break;

    default:break;
    }
  }

  if (Draw_line){
    glLineWidth(3);
    glColor3fv((GLfloat *) &MAGENTA);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;
    case OBJECT_CUBE:Cube.draw_line();break;
    case OBJECT_CONE:Cone.draw_line();break;
    case OBJECT_CYLINDER:Cylinder.draw_line();break;
    case OBJECT_SPHERE:Sphere.draw_line();break;
    case OBJECT_PLY:PlyObject.draw_line();break;
    case OBJECT_AUX:AUX.draw_line();break;
    case OBJECT_SACACORCHOS:Sacacorchos->draw_line();break;
    default:break;
    }
  }

  if (Draw_fill){
    glColor3fv((GLfloat *) &BLUE);
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;
    case OBJECT_CUBE:Cube.draw_fill();break;
    case OBJECT_CONE:Cone.draw_fill();break;
    case OBJECT_CYLINDER:Cylinder.draw_fill();break;
    case OBJECT_SPHERE:Sphere.draw_fill();break;
    case OBJECT_PLY:PlyObject.draw_fill();break;
    case OBJECT_AUX:AUX.draw_fill();break;
    case OBJECT_SACACORCHOS:Sacacorchos->draw_fill();break;
    default:break;
    }
  }

  if (Draw_chess){
    switch (Object){
    case OBJECT_TETRAHEDRON:Tetrahedron.draw_chess();break;
    case OBJECT_CUBE:Cube.draw_chess();break;
    case OBJECT_CONE:Cone.draw_chess();break;
    case OBJECT_CYLINDER:Cylinder.draw_chess();break;
    case OBJECT_SPHERE:Sphere.draw_chess();break;
    case OBJECT_PLY:PlyObject.draw_chess();break;
    case OBJECT_AUX:AUX.draw_chess();break;
    case OBJECT_SACACORCHOS:Sacacorchos->draw_chess();break;
    default:break;
    }
  }
}



/*****************************************************************************//**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_objects();
}


/*****************************************************************************//**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0,0,Width1,Height1);
}


/*****************************************************************************//**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);;
  //glEnable(GL_CULL_FACE);

  Observer_angle_x=0;
  Observer_angle_y=0;
  Observer_distance=DEFAULT_DISTANCE;

  Draw_point=false;
  Draw_line=true;
  Draw_fill=false;
  Draw_chess=false;
}
