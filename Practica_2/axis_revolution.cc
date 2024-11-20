
#include "axis_revolution.h"
#include <cmath>
#include <algorithm>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
void _axis_revolution::circularSweepingOptim(int num_rotaciones){
    int perfil_size = Perfil.size();
    vector<_vertex3f> vertices_extremos, vertices_zona_central;

    cout << "Perfil[0].y es " << Perfil[0].y << " y Perfil[perfil_size-1].y es " << Perfil[perfil_size-1].y << endl;

    //////////// VÉRTICES ////////////
    // Primero debemos comprobar que los vertices del perfil estén almacenados empezando desde el
    // que se encuentre en el punto más alto (en el eje Y) al más bajo.
    if (Perfil[0].y < Perfil[perfil_size-1].y)
        reverse(Perfil.begin(), Perfil.end());  // Le doy la vuelta

    cout << "DESPUES DEL REVERSE Perfil[0].y es " << Perfil[0].y << " y Perfil[perfil_size-1].y es " << Perfil[perfil_size-1].y << endl << endl;

    // Generamos los vertices a partir del Perfil
    vertexGenerationOptim(num_rotaciones);

    // Analizamos los vectores para clasificarlos según si son extremos o de la zona central, para crear los triángulos
    for (int i = 0; i < Vertices.size(); i++){
        // Los vertices "extremos" serán aquellos cuyo valor en el eje X y Z valga 0
        if (Vertices[i].x == 0 && Vertices[i].z == 0)
            vertices_extremos.push_back(Vertices[i]);
        else // Serán vertices de la "zona central"
            vertices_zona_central.push_back(Vertices[i]);
    }


    //////////// TRIÁNGULOS ////////////
    trianglesGenerationOptim(vertices_extremos,vertices_zona_central, num_rotaciones);
    cout << "NUM TOTAL VERTICES " << Vertices.size() << endl << endl;
    cout << "NUM vertices extremos: " << vertices_extremos.size() << endl << endl;
    cout << "NUM vertices zona central:  " << vertices_zona_central.size() << endl << endl;

/*
    Triangles.resize(10);
    Triangles[0].x = 2;
    Triangles[0].y = 1;
    Triangles[0].z = 0;

    Triangles[1].x = 6;
    Triangles[1].y = 2;
    Triangles[1].z = 3;

    Triangles[2].x = 0;
    Triangles[2].y = 5;
    Triangles[2].z = 6;

    Triangles[3].x = 0;
    Triangles[3].y = 2;
    Triangles[3].z = 3;
*/


}

void _axis_revolution::circularSweepingNoOptim(int num_rotaciones){
    //////////// VÉRTICES ////////////
    // Se generan mediante la siguiente función
    vertexGenerationNoOptim(num_rotaciones);

    //////////// TRIÁNGULOS ////////////
    // La siguiente función se encarga de su generación
    trianglesGenerationNoOptim(num_rotaciones);

}

_vertex3ui _axis_revolution::trianglesSum(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax){
    _vertex3ui t3;
    t3._0 = (t1._0 + t2._0) % valorMax;
    t3._1 = (t1._1 + t2._1) % valorMax;
    t3._2 = (t1._2 + t2._2) % valorMax;

    return t3;
}

void _axis_revolution::vertexGenerationNoOptim(int num_rotaciones){
    int i, k;
    float radio, alpha = 2 * M_PI / num_rotaciones;

    //////////// VÉRTICES ////////////
    Vertices.resize(Perfil.size() * num_rotaciones);

    // Primero metemos los vertices del propio Perfil
    for (int j = 0; j < Perfil.size(); j++){
        Vertices[j] = Perfil[j];
    }

    i = 0;  // Para referirnos a los elementos del Perfil
    k = 0;  // Indice para controlar el ángulo
    for (int j = Perfil.size(); j < Vertices.size(); j++){      // Recorro cada vertice que debo crear
        radio = Perfil[i].x;
        if (j % Perfil.size() == 0)
            k++;    // Todos los vectores de un perfil tienen el mismo angulo. Cuando los recorremos todos, actualizamos el indice k

        Vertices[j].x = radio * cos(alpha*k);
        Vertices[j].y = Perfil[i].y;
        Vertices[j].z = - radio * sin(alpha*k);

        i = (i+1) % Perfil.size(); // Aumento i en 1 pero no debo pasarme del num total de vertices del perfil
    }
}

void _axis_revolution::vertexGenerationOptim(int num_rotaciones){
    int i, k;
    float radio, alpha = 2 * M_PI / num_rotaciones;
    int max_vertices = Perfil.size() * num_rotaciones;
    _vertex3f nuevo_vertice;

    // Primero metemos los vertices del propio Perfil
    for (int j = 0; j < Perfil.size(); j++){
        Vertices.push_back(Perfil[j]);
    }

    i = 0;  // Para referirnos a los elementos del Perfil
    k = 0;  // Indice para controlar el ángulo
    for (int j = Perfil.size(); j < max_vertices; j++){      // Recorro cada vertice que debo crear
        radio = Perfil[i].x;
        if (j % Perfil.size() == 0)
            k++;    // Todos los vectores de un perfil tienen el mismo angulo. Cuando los recorremos todos, actualizamos el indice k

        _vertex3f nuevo_vertice;
        nuevo_vertice.x = radio * cos(alpha*k);
        nuevo_vertice.y = Perfil[i].y;
        nuevo_vertice.z = - radio * sin(alpha*k);

        if (find(Vertices.begin(), Vertices.end(), nuevo_vertice) == Vertices.end()){   // Evitamos repetir vertices
            Vertices.push_back(nuevo_vertice);

            /*cout << "Vertice " << Vertices.size()-1 << " x = " << nuevo_vertice.x << endl;
            cout << "              y = " << nuevo_vertice.y << endl;
            cout << "              z = " << nuevo_vertice.z << endl << endl;
            */
        }

        i = (i+1) % Perfil.size(); // Aumento i en 1 pero no debo pasarme del num total de vertices del perfil
    }
}

void _axis_revolution::trianglesGenerationNoOptim(int num_rotaciones){
    int perfil_size = Perfil.size();        // Para evitar llamar tantas veces a ambas funciones
    int vertices_size = Vertices.size();
    _vertex3ui tP, tI;                      // Triangulos par e impar
    _vertex3ui tU;  //triangulo unidad que usaré para las sumas
    tU._0 = 1;
    tU._1 = 1;
    tU._2 = 1;
    _vertex3ui tV;  //triangulo con el número de vectores en el perfil original
    tV._0 = perfil_size;
    tV._1 = perfil_size;
    tV._2 = perfil_size;


    // Recorreremos los "triangulos" viendo los puntos como si formaran una matriz como se explica en el guión de practicas
    Triangles.resize((perfil_size-1) * num_rotaciones * 2);

    // El valor inicial del primer triángulo "par" siempre será T(numFila, numVerticesPerfil, numFila+1)
    // Como empezaremos por la fila numero 0, el triángulo será T(0,Perfil.size(),1)
    tP._0 = 0;
    tP._1 = perfil_size;
    tP._2 = 1;

    // El valor del primer triángulo "impar" será T(numFila+1, Perfil.size(), Perfil.size()+1)
    // Siempre empezamos por la fila 0, así que será T(1,Perfil.size(), Perfil.size()+1)
    tI._0 = 1;
    tI._1 = perfil_size;
    tI._2 = perfil_size+1;

    int i = 0;  // indice para ir llenando el vector de triangulos

    for (int f = 0; f < (perfil_size - 1); f++){    // Recorremos las filas de la "matriz"
        // Actualizo los triángulos según la fila
        if (f != 0){
            tP = trianglesSum(tP, tU, vertices_size);
            tI = trianglesSum(tI, tU, vertices_size);
        }

        for (int c = 0; c < (num_rotaciones); c++){ // Recorremos sus columnas
            if (c == 0){
                Triangles[i] = tP;
                Triangles[i+1] = tI;
            }
            else{
                Triangles[i] = trianglesSum(Triangles[i-2], tV, vertices_size);
                Triangles[i+1] = trianglesSum(Triangles[i-1], tV, vertices_size);
            }

            i+=2;
        }
    }
}

void _axis_revolution::trianglesGenerationOptim(vector<_vertex3f> & vertices_extremos, vector<_vertex3f> & vertices_zona_central, int num_rotaciones){
    int perfil_size = Perfil.size();        // Para evitar llamar tantas veces a ambas funciones
    int vertices_size = Vertices.size();
    int zona_central_size = vertices_zona_central.size();
    int num_centrales_por_perfil = zona_central_size / num_rotaciones;   // cuántos vertices centrales hay en UNA cara
    int num_zonas_centrales = num_centrales_por_perfil - 1;  // es decir, el número de filas que recorreremos


    _vertex3ui tP, tI;                      // Triangulos par e impar
    _vertex3ui tSUM;  //triangulo que se encarga de sumar por columnas
    _vertex3ui tU;  //triangulo unidad, utilizado en sumas de triangulos
    tU._0 = 1;
    tU._1 = 1;
    tU._2 = 1;

    Triangles.resize((perfil_size-1) * num_rotaciones * 2);

    /////// ZONA CENTRAL
    /// En este caso consideramos que los vertices de la zona central son el perfil que define esta zona
    /// Por tanto, hacemos el calculo parecido a como lo hacíamos en la versión no optima
    tP._0 = 3;  // Como hemos decidido que los vertices extremos sean siempre 0 y 1,
    tP._1 = 2;  // los dos primeros valores de los primeros triángulos serán siempre 2 y 3
    tP._2 = perfil_size;

    tI._0 = 3;
    tI._1 = perfil_size;
    tI._2 = perfil_size+1;

    // Dependiendo del maximo de filas a recorrer también cambiará el valor que hay que sumar por columnas
    tSUM._0 = 1+num_zonas_centrales;
    tSUM._1 = 1+num_zonas_centrales;
    tSUM._2 = 1+num_zonas_centrales;

    int i = 0;  // indice para ir llenando el vector de triangulos
    for (int f = 0; f < num_zonas_centrales; f++){    // Recorremos las filas de la "matriz"
        // Actualizo los triángulos según la fila
        if (f != 0){
            tP = trianglesSum(tP, tU, vertices_size);
            tI = trianglesSum(tI, tU, vertices_size);
        }

        for (int c = 0; c < (num_rotaciones); c++){ // Recorremos sus columnas
            if (c == 0){
                Triangles[i] = tP;
                Triangles[i+1] = tI;
            }
            else if(c == num_rotaciones-1){
                // Si es la ultima columna hay que tener cuidado con la suma de triangulos, porque el modulo
                // hace que los triángulos usen los vertices extremo como uno de sus vertices
                // Para arreglarlo ponemos los primeros vertices de la "cara central"
                _vertex3ui tAUX = trianglesSum(Triangles[i-2], tSUM, vertices_size);
                tAUX._2 = 2;
                Triangles[i] = tAUX;

                tAUX = trianglesSum(Triangles[i-1], tSUM, vertices_size);
                tAUX._1 = 2;
                tAUX._2 = 3;
                Triangles[i+1] = tAUX;
            }
            else{
                Triangles[i] = trianglesSum(Triangles[i-2], tSUM, vertices_size);
                Triangles[i+1] = trianglesSum(Triangles[i-1], tSUM, vertices_size);
            }

            i+=2;
        }
    }


    /////// ZONA SUPERIOR
    for(int j = 0; j < num_rotaciones; j++){
        if (j == 0){
            Triangles[i]._0 = 0;
            Triangles[i]._1 = perfil_size - 1;
            Triangles[i]._2 = perfil_size + num_zonas_centrales;
        }
        else if (j == num_rotaciones-1){
            Triangles[i]._0 = 0;
            Triangles[i]._1 = Triangles[i-1]._1 + 1 + num_zonas_centrales;
            Triangles[i]._2 = perfil_size - 1;
        }
        else{
            Triangles[i]._0 = 0;
            Triangles[i]._1 = Triangles[i-1]._1 + 1 + num_zonas_centrales;
            Triangles[i]._2 = Triangles[i-1]._2 + 1 + num_zonas_centrales;
        }

        i++;
    }

    /////// ZONA INFERIOR
    for(int j = 0; j < num_rotaciones; j++){
        if (j == 0){
            Triangles[i]._0 = 1;
            Triangles[i]._1 = 2;    // Siempre será 2, porque es el siguiente vertice después de 1
            if(num_zonas_centrales == 0)
                Triangles[i]._2 = 3;
            else
                Triangles[i]._2 = 2 + num_centrales_por_perfil;
        }
        else if (j == num_rotaciones-1){
            Triangles[i]._0 = 1;
            Triangles[i]._2 = 2;
            if (num_zonas_centrales == 0)
                Triangles[i]._1 = Triangles[i-1]._1 + 1;
            else
                Triangles[i]._1 = Triangles[i-1]._1 + num_centrales_por_perfil;
        }
        else{
            Triangles[i]._0 = 1;
            if (num_zonas_centrales == 0){
                Triangles[i]._1 = Triangles[i-1]._1 + 1;
                Triangles[i]._2 = Triangles[i-1]._2 + 1;
            }
            else{
                Triangles[i]._1 = Triangles[i-1]._1 + num_centrales_por_perfil;
                Triangles[i]._2 = Triangles[i-1]._2 + num_centrales_por_perfil;
            }
        }

        cout << "Triangulo " << i << " valores: " << Triangles[i].x << " " << Triangles[i].y << " " << Triangles[i].z << endl;

        i++;
    }







}









