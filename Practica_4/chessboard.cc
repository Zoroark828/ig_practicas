
#include "chessboard.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_chessboard::_chessboard(){
    Vertices.resize(4);
    Vertices[0]=_vertex3f(-0.5,0,-0.5);
    Vertices[1]=_vertex3f(-0.5,0,0.5);
    Vertices[2]=_vertex3f(0.5,0,0.5);
    Vertices[3]=_vertex3f(0.5,0,-0.5);


    Triangles.resize(2);
    Triangles[0]=_vertex3ui(0,1,2);
    Triangles[1]=_vertex3ui(0,2,3);

    CoordenadasTextura.resize(Vertices.size());
    CoordenadasTextura[0]=_vertex2f(0,1);
    CoordenadasTextura[1]=_vertex2f(0,0);
    CoordenadasTextura[2]=_vertex2f(1,0);
    CoordenadasTextura[3]=_vertex2f(1,1);
}
