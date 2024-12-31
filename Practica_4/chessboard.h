
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _chessboard:public _object3D
{
public:
    _chessboard(int size = 1, int num_divisiones = 4);

    // Suma dos triángulos. La suma de cada componente no puede superar valorMax (se hace un modulo)
    _vertex3ui trianglesSum(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax);

};

#endif
