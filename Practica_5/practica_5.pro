DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x050F00

HEADERS += \
  colors.h \
  basic_object3d.h \
  object3d.h \
  axis.h \
  tetrahedron.h \
  cube.h \
  glwidget.h \
  window.h \
  file_ply_stl.h \
  ply_object.h \
  axis_revolution.h \
  cone.h \
  cylinder.h \
  sphere.h \
  ply_object_revolution.h \
  car.h \
  spiral.h \
  rectangular_ring.h \
  sacacorchos.h \
  chessboard.h

SOURCES += \
  basic_object3d.cc \
  object3d.cc \
  axis.cc \
  tetrahedron.cc \
  cube.cc \
  main.cc \
  glwidget.cc \
  window.cc \
  file_ply_stl.cc \
  ply_object.cc \
  axis_revolution.cc \
  cone.cc \
  cylinder.cc \
  sphere.cc \
  ply_object_revolution.cc \
  car.cc \
  spiral.cc \
  rectangular_ring.cc \
  sacacorchos.cc \
  chessboard.cc


INCLUDEPATH += D:\AA_UNIVERSIDAD\IG\PRACTICAS\Practica_5\

LIBS += -lopengl32


CONFIG += c++14
QT += widgets opengl openglwidgets
