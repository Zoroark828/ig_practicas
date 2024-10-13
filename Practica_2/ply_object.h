

#ifndef PLY_OBJECT
#define PLY_OBJECT

#include "object3d.h"
#include <QCoreApplication>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _ply_object:public _object3D
{
public:
  _ply_object(string File = QCoreApplication::applicationDirPath().toStdString() + "/../../../ply_models/beethoven.ply");

};

#endif

// Absolute path:
// "D:\\AA_UNIVERSIDAD\\IG\\PRACTICAS\\Practica_2\\ply_models\\beethoven.ply"

// Relative path:
// QCoreApplication::applicationDirPath().toStdString() + "/../../../ply_models/beethoven.ply"



