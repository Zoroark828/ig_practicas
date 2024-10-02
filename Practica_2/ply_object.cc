
#include "ply_object.h"
#include "file_ply_stl.h"   // Para poder leer archivos PLY

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_ply_object::_ply_object(string file_name)
{


    _file_ply LectorPLY;
    if (LectorPLY.open(file_name)){   // Abro el archivo PLY
        // Leo las coordenadas y posiciones (triángulos) del archivo
        vector<float> Coordinates;
        vector<unsigned int> Positions;
        LectorPLY.read(Coordinates,Positions);

        // Debo pasarlas a las componentes Vertices y Triangles de esta clase
        Vertices.clear();
        Vertices.resize(Coordinates.size()/3);  // Cada 3 numeros se define un vértice
        for (int i = 0; i < (int) Coordinates.size(); i+=3){
            Vertices[i].x = Coordinates[i];
            Vertices[i].y = Coordinates[i+1];
            Vertices[i].z = Coordinates[i+2];
        }

        Triangles.clear();
        Triangles.resize(Positions.size()/3);  // Cada 3 numeros se define un triangulo
        for (int i = 0; i < (int) Positions.size(); i+=3){
            Triangles[i]._0 = Positions[i];
            Triangles[i]._1 = Positions[i+1];
            Triangles[i]._2 = Positions[i+2];
        }
    }

    // Antes de acabar, cerramos el archivo
    LectorPLY.close();
}

