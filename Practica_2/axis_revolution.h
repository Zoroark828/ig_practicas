
#ifndef AXIS_REV_H
#define AXIS_REV_H

#include "object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _axis_revolution:public _object3D
{
public:
    vector<_vertex3f> Perfil;
    _axis_revolution(){}   // Constructor que no hace nada

    // Crea el objeto rotando circularmente el Perfil sobre el eje Y (VERSIÓN NO OPTIMA)
    void circularSweepingNoOptim(int num_rotaciones);

    // Crea el objeto rotando circularmente el Perfil sobre el eje Y (VERSIÓN OPTIMA Y FINAL)
    void circularSweepingOptim(int num_rotaciones);

    // Devuelve la suma del triángulo t1 y t2 teniendo en cuenta que ninguna de sus componentes puede superar el valor valorMax
    _vertex3ui trianglesSum(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax);

    // Función que genera los vertices (de forma no optima y de forma optima)
    void vertexGenerationNoOptim(int num_rotaciones);
    void vertexGenerationOptim(int num_rotaciones);

    // Función que genera los triángulos (utilizadas en la funciones circular sweeping, dependiendo de si son version optima o no)
    void trianglesGenerationNoOptim(int num_rotaciones);
    void trianglesGenerationOptim(vector<_vertex3f> & vertices_extremos, vector<_vertex3f> & vertices_zona_central, int num_rotaciones);






    bool verticeRepetido(vector<_vertex3f> & vector, _vertex3f elemento);



};

#endif
