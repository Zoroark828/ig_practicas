
#ifndef PLY_OBJECT_REVOLUTION
#define PLY_OBJECT_REVOLUTION

#include "axis_revolution.h"
#include <QCoreApplication>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _ply_object_revolution:public _axis_revolution
{
public:
    _ply_object_revolution(int num_rotaciones = 40,
                           string File = QCoreApplication::applicationDirPath().toStdString() + "/../../../ply_models/perfil_revolucion.ply");
    void readPlyFile(string file_name);
};

#endif
