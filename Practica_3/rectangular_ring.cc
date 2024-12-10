
#include "rectangular_ring.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_rectangular_ring::_rectangular_ring(int num_rotaciones)
{
    // El perfil exterior son solo dos puntos
    PerfilExterior.resize(2);
    PerfilExterior[0]=_vertex3f(0.5,0.5,0);
    PerfilExterior[1]=_vertex3f(0.5,-0.5,0);

    // El interior tiene 2 puntos también
    PerfilInterior.resize(2);
    PerfilInterior[0]=_vertex3f(0.30,0.5,0);
    PerfilInterior[1]=_vertex3f(0.30,-0.5,0);

    num_rotaciones = 40;


    // VERTICES
    int i, k;
    float radio_ext, radio_int, alpha = 2 * M_PI / num_rotaciones;
    int max_vertices = PerfilExterior.size() * num_rotaciones * 2;  // x2 porque tenemos dos perfiles distintos
    _vertex3f nuevo_vertice_ext, nuevo_vertice_int;
    Vertices.resize(max_vertices);

    // Metemos los vertices de los perfiles
    i = 0;
    for (int j = 0; j < PerfilExterior.size(); j++){
        Vertices[i] = PerfilExterior[j];
        Vertices[i+1] = PerfilInterior[j];
        i+=2;
    }

    i = 0;  // Para referirnos a los elementos del Perfil
    k = 0;  // Indice para controlar el ángulo
    for (int j = 4; j < max_vertices; j+=2){      // Añado los vertices de 2 en 2
        radio_ext = PerfilExterior[i].x;
        radio_int = PerfilInterior[i].x;
        if (j % 4 == 0)
            k++;    // Todos los vertices de un perfil tienen el mismo angulo. Cuando los recorremos todos, actualizamos el indice k

        nuevo_vertice_ext.x = radio_ext * cos(alpha*k);
        nuevo_vertice_ext.y = PerfilExterior[i].y;
        nuevo_vertice_ext.z = - radio_ext * sin(alpha*k);

        nuevo_vertice_int.x = radio_int * cos(alpha*k);
        nuevo_vertice_int.y = PerfilInterior[i].y;
        nuevo_vertice_int.z = - radio_int * sin(alpha*k);

        Vertices[j] = nuevo_vertice_ext;
        Vertices[j+1] = nuevo_vertice_int;

        i = (i+1) % PerfilExterior.size();
    }



    // TRIANGULOS
    int vertices_size = Vertices.size();
    Triangles.resize(num_rotaciones * 4 * 2);   // num_rot * 4 ("caras": la superior, la inferior y 2 centrales) * 2 (triángulos por "cara")

    _vertex3ui tPar, tImp, tCuatro;
    tCuatro._0 = 4; // Lo usamos para las sumas
    tCuatro._1 = 4;
    tCuatro._2 = 4;

    // PARTE CENTRAL
    // PARTE CENTRAL EXTERIOR
    tPar._0 = 0;
    tPar._1 = 2;
    tPar._2 = 6;

    tImp._0 = 0;
    tImp._1 = 6;
    tImp._2 = 4;

    i = 0;  // indice para ir llenando el vector de triangulos
    for (int c = 0; c < num_rotaciones; c++){  // recorro las caras de la zona central
        if (c == 0){
            Triangles[i] = tPar;
            Triangles[i+1] = tImp;
        }
        else if(c == num_rotaciones-1){
            _vertex3ui tAUX = trianglesSum(Triangles[i-2], tCuatro, vertices_size);
            tAUX._2 = 2;    // el tercer vertice siempre será 2
            Triangles[i] = tAUX;

            tAUX = trianglesSum(Triangles[i-1], tCuatro, vertices_size);
            tAUX._1 = 2;
            tAUX._2 = 0;
            Triangles[i+1] = tAUX;
        }
        else{
            Triangles[i] = trianglesSum(Triangles[i-2], tCuatro, vertices_size);
            Triangles[i+1] = trianglesSum(Triangles[i-1], tCuatro, vertices_size);
        }

        /*
        cout << i << endl;
        cout << "X: " << Triangles[i].x << " Y: " << Triangles[i].y << " Z: " << Triangles[i].z << endl;
        cout << i+1 << endl;
        cout << "X: " << Triangles[i+1].x << " Y: " << Triangles[i+1].y << " Z: " << Triangles[i+1].z << endl;
        */

        i+=2;
    }

    // PARTE CENTRAL INTERIOR
    tPar._0 = 1;
    tPar._1 = 3;
    tPar._2 = 7;

    tImp._0 = 1;
    tImp._1 = 7;
    tImp._2 = 5;

    for (int c = 0; c < num_rotaciones; c++){  // recorro las caras de la zona central INTERIOR (son el mismo numero que las caras exteriores
        if (c == 0){
            Triangles[i] = tPar;
            Triangles[i+1] = tImp;
        }
        else if(c == num_rotaciones-1){
            _vertex3ui tAUX = trianglesSum(Triangles[i-2], tCuatro, vertices_size);
            tAUX._2 = 3;    // el tercer vertice siempre será 2
            Triangles[i] = tAUX;

            tAUX = trianglesSum(Triangles[i-1], tCuatro, vertices_size);
            tAUX._1 = 3;
            tAUX._2 = 1;
            Triangles[i+1] = tAUX;
        }
        else{
            Triangles[i] = trianglesSum(Triangles[i-2], tCuatro, vertices_size);
            Triangles[i+1] = trianglesSum(Triangles[i-1], tCuatro, vertices_size);
        }

        /*
        cout << i << endl;
        cout << "X: " << Triangles[i].x << " Y: " << Triangles[i].y << " Z: " << Triangles[i].z << endl;
        cout << i+1 << endl;
        cout << "X: " << Triangles[i+1].x << " Y: " << Triangles[i+1].y << " Z: " << Triangles[i+1].z << endl;
        */

        i+=2;
    }


    // PARTE SUPERIOR
    tPar._0 = 1;
    tPar._1 = 0;
    tPar._2 = 4;

    tImp._0 = 1;
    tImp._1 = 4;
    tImp._2 = 5;

    for (int c = 0; c < num_rotaciones; c++){  // recorro las caras de la zona central INTERIOR (son el mismo numero que las caras exteriores
        if (c == 0){
            Triangles[i] = tPar;
            Triangles[i+1] = tImp;
        }
        else if(c == num_rotaciones-1){
            _vertex3ui tAUX = trianglesSum(Triangles[i-2], tCuatro, vertices_size);
            tAUX._2 = 0;    // el tercer vertice siempre será 2
            Triangles[i] = tAUX;

            tAUX = trianglesSum(Triangles[i-1], tCuatro, vertices_size);
            tAUX._1 = 0;
            tAUX._2 = 1;
            Triangles[i+1] = tAUX;
        }
        else{
            Triangles[i] = trianglesSum(Triangles[i-2], tCuatro, vertices_size);
            Triangles[i+1] = trianglesSum(Triangles[i-1], tCuatro, vertices_size);
        }

        /*
        cout << i << endl;
        cout << "X: " << Triangles[i].x << " Y: " << Triangles[i].y << " Z: " << Triangles[i].z << endl;
        cout << i+1 << endl;
        cout << "X: " << Triangles[i+1].x << " Y: " << Triangles[i+1].y << " Z: " << Triangles[i+1].z << endl;
        */

        i+=2;
    }








    // PARTE INFERIOR
    tPar._0 = 3;
    tPar._1 = 2;
    tPar._2 = 6;

    tImp._0 = 3;
    tImp._1 = 6;
    tImp._2 = 7;

    for (int c = 0; c < num_rotaciones; c++){  // recorro las caras de la zona central INTERIOR (son el mismo numero que las caras exteriores
        if (c == 0){
            Triangles[i] = tPar;
            Triangles[i+1] = tImp;
        }
        else if(c == num_rotaciones-1){
            _vertex3ui tAUX = trianglesSum(Triangles[i-2], tCuatro, vertices_size);
            tAUX._2 = 2;    // el tercer vertice siempre será 2
            Triangles[i] = tAUX;

            tAUX = trianglesSum(Triangles[i-1], tCuatro, vertices_size);
            tAUX._1 = 2;
            tAUX._2 = 3;
            Triangles[i+1] = tAUX;
        }
        else{
            Triangles[i] = trianglesSum(Triangles[i-2], tCuatro, vertices_size);
            Triangles[i+1] = trianglesSum(Triangles[i-1], tCuatro, vertices_size);
        }

        /*
        cout << i << endl;
        cout << "X: " << Triangles[i].x << " Y: " << Triangles[i].y << " Z: " << Triangles[i].z << endl;
        cout << i+1 << endl;
        cout << "X: " << Triangles[i+1].x << " Y: " << Triangles[i+1].y << " Z: " << Triangles[i+1].z << endl;
        */

        i+=2;
    }

}

_vertex3ui _rectangular_ring::trianglesSum(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax){
    _vertex3ui t3;
    t3._0 = (t1._0 + t2._0) % valorMax;
    t3._1 = (t1._1 + t2._1) % valorMax;
    t3._2 = (t1._2 + t2._2) % valorMax;

    return t3;
}
