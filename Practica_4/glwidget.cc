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


  // Genero las normales de los objetos
  Tetrahedron.calculo_normales();
  Cube.calculo_normales();
  Cone.calculo_normales();
  Cylinder.calculo_normales();
  Sphere.calculo_normales();
  Spiral.calculo_normales();
  Ring.calculo_normales();
  PlyObject.calculo_normales();
  //Chessboard.calculo_normales();

  rotacion_luz = 0; // En un inicio la segunda luz se encuentra en la misma posición en la que se definió
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
        case Qt::Key_1:Object=_gl_widget_ne::OBJECT_TETRAHEDRON;break;
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

        // Nuevos casos Practica 4:
        case Qt::Key_F1:Draw_fill=!Draw_fill;break; // "Solid mode"
        case Qt::Key_F2:Draw_chess=!Draw_chess;break;
        case Qt::Key_F3:DrawFlat=!DrawFlat;break;
        case Qt::Key_F4:DrawGouraud=!DrawGouraud;break;
        case Qt::Key_F5:DrawTextureUnlit=!DrawTextureUnlit;break;
        case Qt::Key_F6:DrawTextureFlat=!DrawTextureFlat;break;
        case Qt::Key_F7:DrawTextureGouraud=!DrawTextureGouraud;break;

        case Qt::Key_J:FirstLight=!FirstLight;break;
        case Qt::Key_K:SecondLight=!SecondLight;break;
        case Qt::Key_M:Material=(Material + 1) % 3;break;
        //

        // Teclas para controlar los grados de libertad del sacacorchos + animacion (Practica 3)
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
        //

        case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
        case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
        case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
        case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
        case Qt::Key_B:Observer_distance*=1.2;break;
        case Qt::Key_N:Observer_distance/=1.2;break;
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

    // Aumento el número de grados que gira la segunda luz
    rotacion_luz += 2;

    update();
}


/*****************************************************************************//**
 * Funciones para definir las dos luces y los tres materiales
 *
 *
 *
 *****************************************************************************/

void _gl_widget::primera_luz(){
    GLfloat LIGHT0_POS[] = {-1.0f, 1.0f, 1.0f, 0.0f};    // El ultimo valor indica que está en el infinito
    GLfloat LIGHT0_COLOR[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, LIGHT0_POS);
    // GL_LIGHT0 es una luz blanca ya definida por OpenGL. La dejo como está. En otro caso:
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT0_COLOR);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT0_COLOR);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT0_COLOR); // no tiene definida la ambiental por defecto
}

void _gl_widget::segunda_luz(){
    GLfloat LIGHT1_POS[] = {5.0f, 10.0f, 2.0f, 1.0f};  // El ultimo valor indica que *NO* está en el infinito
    GLfloat LIGHT1_COLOR[] = {1.0f, 0.0f, 1.0f, 1.0f};   // RGBA (La A indica la opacidad). Este color es magenta (1,0,1)

    glLightfv(GL_LIGHT1, GL_POSITION, LIGHT1_POS);
    // Le pasamos el mismo color a las tres componentes
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LIGHT1_COLOR);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT1_COLOR);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LIGHT1_COLOR);
}



void _gl_widget::definir_material(){
    // El primer material va a ser amarillo y completamente difuso
    // Al incidir sobre él la luz blanca, se ve amarillo
    // Al incidir sobre él la luz magenta, se verá rojo.    (1,1,0) unido a (1,0,1) --> (1,0,0)
    GLfloat MATERIAL_DIFFUSE1[] = {0.5,0.5,0.0};
    GLfloat MATERIAL_SPECULAR1[] = {0.0,0.0,0.0};   // No quiero componente especular, así que la pongo "negra"
    GLfloat MATERIAL_AMBIENT1[] = {0.2,0.2,0.0};


    // El segundo material va a ser igual que el anterior, pero con constante especular también
    GLfloat MATERIAL_DIFFUSE2[] = {0.7,0.7,0.0};
    GLfloat MATERIAL_SPECULAR2[] = {0.2,0.2,0.0};
    GLfloat MATERIAL_AMBIENT2[] = {0.2,0.2,0.0};


    // El tercer material va a ser de color cyan, con reflejos especulares
    // Con la luz blanca, se ve cyan
    // Con la luz magenta se verá azul.     Cyan (0,1,1) unido a Magenta (1,0,1) --> Azul (1,0,0)
    GLfloat MATERIAL_DIFFUSE3[] = {0.0,0.7,0.7};
    GLfloat MATERIAL_SPECULAR3[] = {0.0,0.2,0.2};
    GLfloat MATERIAL_AMBIENT3[] = {0.0,0.2,0.2};

    float MATERIAL_SHINIESS = 50;

    switch(Material){
    case 0:
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, MATERIAL_DIFFUSE1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, MATERIAL_SPECULAR1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, MATERIAL_AMBIENT1);
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, MATERIAL_SHINIESS);
        break;
    case 1:
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, MATERIAL_DIFFUSE2);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, MATERIAL_SPECULAR2);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, MATERIAL_AMBIENT2);
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, MATERIAL_SHINIESS);
        break;
    case 2:
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, MATERIAL_DIFFUSE3);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, MATERIAL_SPECULAR3);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, MATERIAL_AMBIENT3);
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, MATERIAL_SHINIESS);
        break;
    default: break;
    }
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
    glDisable(GL_LIGHTING); // Desactivo la luz por si después de utilizar un modo de iluminación ya no quiero usarlo

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

  if (DrawFlat){
      glEnable(GL_LIGHTING);    // Activo la iluminación

      // Primera luz (es estática)
      primera_luz();

      // Segunda luz (debe moverse con la animación (letra A) al rededor del objeto)
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glRotated(rotacion_luz,0,1,0);    // Aumento rotacion_luz en animation() para que solo cambie si la anim. está activada
      segunda_luz();
      glPopMatrix();

      // Activo las dos luces según qué he elegido
      if(FirstLight){
          glEnable(GL_LIGHT0);
      }
      else
          glDisable(GL_LIGHT0);

      if(SecondLight){
          glEnable(GL_LIGHT1);
      }
      else
          glDisable(GL_LIGHT1);

      // Definimos el material, que depende del que hayamos elegido entre los 3 creados
      definir_material();

      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_flat();break;
      case OBJECT_CUBE:Cube.draw_flat();break;
      case OBJECT_CONE:Cone.draw_flat();break;
      case OBJECT_CYLINDER:Cylinder.draw_flat();break;
      case OBJECT_SPHERE:Sphere.draw_flat();break;
      case OBJECT_PLY:PlyObject.draw_flat();break;
      case OBJECT_SACACORCHOS:Sacacorchos->draw_flat();break;
      default:break;
      }
  }

  if (DrawGouraud){
      glEnable(GL_LIGHTING);    // Activo la iluminación

      // Primera luz (es estática)
      primera_luz();

      // Segunda luz (debe moverse con la animación (letra A) al rededor del objeto)
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glRotated(rotacion_luz,0,1,0);    // Aumento rotacion_luz en animation() para que solo cambie si la anim. está activada
      segunda_luz();
      glPopMatrix();

      // Activo las dos luces según qué he elegido
      if(FirstLight){
          glEnable(GL_LIGHT0);
      }
      else
          glDisable(GL_LIGHT0);

      if(SecondLight){
          glEnable(GL_LIGHT1);
      }
      else
          glDisable(GL_LIGHT1);

      // Definimos el material, que depende del que hayamos elegido entre los 3 creados
      definir_material();

      switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_gouraud();break;
      case OBJECT_CUBE:Cube.draw_gouraud();break;
      case OBJECT_CONE:Cone.draw_gouraud();break;
      case OBJECT_CYLINDER:Cylinder.draw_gouraud();break;
      case OBJECT_SPHERE:Sphere.draw_gouraud();break;
      case OBJECT_PLY:PlyObject.draw_gouraud();break;
      case OBJECT_SACACORCHOS:Sacacorchos->draw_gouraud();break;
      default:break;
      }
  }

  if (DrawTextureUnlit){

  }




  if (DrawTextureFlat){

  }

  if (DrawTextureGouraud){

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
  DrawFlat=false;
  DrawGouraud=false;
  DrawTextureUnlit=false;
  DrawTextureFlat=false;
  DrawTextureGouraud=false;
  FirstLight=false;
  SecondLight=false;
  Material=0;
}
