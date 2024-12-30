
#include "axis_revolution.h"
#include <cmath>
#include <algorithm>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/
void _axis_revolution::circularSweeping(int num_rotaciones){
    int perfil_size = Perfil.size();
    vector<_vertex3f> vertices_zona_central;

    //////////// VÉRTICES ////////////
    // Primero debemos comprobar que los vertices del perfil estén almacenados empezando desde el
    // que se encuentre en el punto más alto (en el eje Y) al más bajo. Si no, los triángulos de las zonas superior e
    // inferior se calcularán mal
    if (Perfil[0].y < Perfil[perfil_size-1].y)
        reverse(Perfil.begin(), Perfil.end());  // Le doy la vuelta

    // Generamos los vertices a partir del Perfil
    vertexGeneration(num_rotaciones);

    // Analizamos los vectores para ver los que pertenecen a la zona central
    for (int i = 0; i < Vertices.size(); i++){
        // Los vertices "extremos" serán aquellos cuyo valor en el eje X y Z valga 0
        // Buscamos los NO extremos (es decir, centrales)
        if (! (Vertices[i].x == 0 && Vertices[i].z == 0))
            vertices_zona_central.push_back(Vertices[i]);
    }


    //////////// TRIÁNGULOS ////////////
    trianglesGeneration(vertices_zona_central, num_rotaciones);

/*
    cout << "NUM TOTAL VERTICES " << Vertices.size() << endl << endl;
    cout << "NUM vertices extremos: " << vertices_extremos.size() << endl << endl;
    cout << "NUM vertices zona central:  " << vertices_zona_central.size() << endl << endl;
*/
}

_vertex3ui _axis_revolution::trianglesSum(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax){
    _vertex3ui t3;
    t3._0 = (t1._0 + t2._0) % valorMax;
    t3._1 = (t1._1 + t2._1) % valorMax;
    t3._2 = (t1._2 + t2._2) % valorMax;

    return t3;
}

void _axis_revolution::vertexGeneration(int num_rotaciones){
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

        //_vertex3f nuevo_vertice;
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

void _axis_revolution::trianglesGeneration(vector<_vertex3f> & vertices_zona_central, int num_rotaciones){
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

    if (num_zonas_centrales == 0)    // Caso del cono
        Triangles.resize((perfil_size-1) * num_rotaciones);
    else if (num_zonas_centrales == 1)  // Caso del cilindro
        Triangles.resize((perfil_size) * num_rotaciones);
    else
        Triangles.resize(2 * num_rotaciones + num_rotaciones * num_zonas_centrales * 2);    ///////

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
                tAUX._2 = 2 + f;    // depende de la fila en que estés
                Triangles[i] = tAUX;

                tAUX = trianglesSum(Triangles[i-1], tSUM, vertices_size);
                tAUX._1 = 2 + f;
                tAUX._2 = 3 + f;
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
    // Haciendo pruebas con distintos perfiles te puedes dar cuenta rápidamente de qué
    // patrón siguen la zona superior e inferior y qué debes ir sumando
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

        i++;
    }
}

void _axis_revolution::calculo_normales(){
    calculo_normales_triangulos();
    calculo_normales_vertices();
}

void _axis_revolution::calculo_normales_triangulos(){
    _vertex3f A, B;
    _vertex3f N;

    // En cualquier figura generada por este método hay el mismo numero de triangulos en la parte inferior que
    // el numero de rotaciones que se han realizado

    NormalesTriangulos.resize(Triangles.size());

    for (int i = 0; i < Triangles.size(); i++){
        A = Vertices[Triangles[i]._1] - Vertices[Triangles[i]._0];
        B = Vertices[Triangles[i]._2] - Vertices[Triangles[i]._0];

        // Producto (vectorial) de A*B
        N = A.cross_product(B);

        // Compruebo si el triángulo es de la cara inferior del objeto, en cuyo caso necesito cambiar el sentido de la Normal
        // Los triangulos de la cara inferior siempre se guardan los ultimos en el vector de Triangulos
        if (i == (Triangles.size() - num_rotaciones) || i > (Triangles.size() - num_rotaciones)){
            N.x *= -1;
            N.y *= -1;
            N.z *= -1;
        }

        // También es importante normalizar el vector
        N.normalize();
        NormalesTriangulos[i] = N;
    }
}







