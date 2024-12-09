

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
    void readPlyFile(string file_name);

};

#endif

// Absolute path:
// "D:\\AA_UNIVERSIDAD\\IG\\PRACTICAS\\Practica_X\\ply_models\\beethoven.ply"

// Relative path:
// QCoreApplication::applicationDirPath().toStdString() + "/../../../ply_models/beethoven.ply"



