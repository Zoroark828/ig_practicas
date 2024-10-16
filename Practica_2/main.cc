/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2023
 * GPL 3
 */

#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "window.h"

#include <iostream>
/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

int main( int argc, char ** argv )
{
  QApplication Application( argc, argv );

  QSurfaceFormat Format;
  Format.setDepthBufferSize(24);
  Format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(Format);

  std::cout << QCoreApplication::applicationDirPath().toStdString() << std::endl;

  _window Window;
  Window.show();
  return Application.exec();
}
