
#include "ply_object_revolution.h"
#include "file_ply_stl.h"

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_ply_object_revolution::_ply_object_revolution(int num_rotaciones, string file_name){
    // Leo el archivo y guardo sus Vertices y Triángulos en un objeto ply
    readPlyFile(file_name);

    // El perfil contendrá dichos vertices
    Perfil = Vertices;

    // Vaciamos los vertices y triángulos que hemos leido porque los que definen al objeto serán los generados a partir del barrido circular
    Vertices.clear();
    Triangles.clear();

    // Rotamos el objeto y con ello generamos sus vertices y triángulos
    num_rotaciones = 40;
    circularSweeping(num_rotaciones);
}

void _ply_object_revolution::readPlyFile(string file_name){
    _file_ply LectorPLY;
    if (LectorPLY.open(file_name)){
        // Leo las coordenadas y posiciones (triángulos) del archivo
        vector<float> Coordinates;
        vector<unsigned int> Positions;
        LectorPLY.read(Coordinates,Positions);

        // Debo pasarlas a las componentes Vertices y Triangles de esta clase
        int j = 0;
        Vertices.clear();
        Vertices.resize(Coordinates.size()/3);  // Cada 3 numeros se define un vértice
        for (int i = 0; i < Vertices.size(); i++){
            Vertices[i].x = (GLfloat) Coordinates[j];
            Vertices[i].y = (GLfloat) Coordinates[j+1];
            Vertices[i].z = (GLfloat) Coordinates[j+2];

            j+=3;
        }

        j = 0;
        Triangles.clear();
        Triangles.resize(Positions.size()/3);  // Cada 3 numeros se define un triangulo
        for (int i = 0; i < Triangles.size(); i++){
            Triangles[i]._0 = Positions[j];
            Triangles[i]._1 = Positions[j+1];
            Triangles[i]._2 = Positions[j+2];

            j+=3;
        }
    }

    // Antes de acabar, cerramos el archivo
    LectorPLY.close();
}
