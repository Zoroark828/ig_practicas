
#include "chessboard.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_chessboard::_chessboard(int size, int num_divisiones){
    int num_vertices_lado, num_lineas_lado;
    float intervalo_vertices, intervalo_texturas, mitad_size;

    // Si num_divisiones = 0, el tablero tendrá 1 subcuadrado (2 triángulos). Si num_divisiones = 1, tendrá 4 subcuadrados (8 tiángulos en total),...

    // El número de vértices por lado del cuadrado que forma el tablero siempre será mínimo 2 (si num_divisiones = 0) y aumentará en 1 por cada
    // división que se haga
    num_vertices_lado = 2 + num_divisiones;

    // El número de líneas que unen a los vertices de un lado del cuadrado serán el número de vértices - 1
    // Cada una de estas líneas es un sub-cuadrado
    num_lineas_lado = num_vertices_lado - 1;

    // Al ser un cuadrado, si en cada lado hay N vertices, en total en todo el tablero habrán NxN vértices
    // Igual ocurre con los cuadrados. Si en cada lado hay M "líneas" (cada una representa el lado de un sub-cuadrado), en total habrán
    // MxM cuadrados en todo el tablero. El número de triángulos es el doble del número de subcuadrados, ya que hay 2 triángulos por subcuadrado
    Vertices.resize(num_vertices_lado * num_vertices_lado);
    CoordenadasTextura.resize(num_vertices_lado * num_vertices_lado);
    Triangles.resize(num_lineas_lado * num_lineas_lado * 2);




    /////// GENERACIÓN DE VERTICES Y COORDENADAS DE TEXTURA
    // Reparto el tamaño según el número de cuadrados
    intervalo_vertices = size / (num_lineas_lado * 1.0);
    intervalo_texturas = 1 / (num_lineas_lado * 1.0);   // Las coordenadas de textura se expresan en el intervalo 0-1
    mitad_size = size/2.0;

    // Añado los del lado izquierdo del tablero primero, para después usarlos como referencia
    for (int i = 0; i < num_vertices_lado; i++){
        // Haciendo un dibujo se entiende de donde salen los calculos
        // A las componentes de los vertices les resto size/2 para centrar el tablero en el origen, ya que la otra parte
        // del calculo crea el tablero con su esquina inferior izquierda en el (0,0,0) y su esquina superior derecha en el (Size,Size,0)

        Vertices[i].x = 0 - mitad_size;
        Vertices[i].y = i * intervalo_vertices - mitad_size;
        Vertices[i].z = 0;      // Siempre es 0, trabajamos sobre el plano z=0

        CoordenadasTextura[i].x = 0;
        CoordenadasTextura[i].y = i * intervalo_texturas;

        //cout << "[" << i << "] x = " << Vertices[i].x << " y = " << Vertices[i].y  << " z = " << Vertices[i].z << endl;
        //cout << " textura --> x = " << CoordenadasTextura[i].x << "   y = " << CoordenadasTextura[i].y << endl;
    }


    for (int i = num_vertices_lado; i < Vertices.size(); i++){      // Recorro cada vertice que debo crear
        Vertices[i].x = Vertices[i-num_vertices_lado].x + intervalo_vertices;
        Vertices[i].y = Vertices[i-num_vertices_lado].y;
        Vertices[i].z = 0;  // trabajamos sobre z = 0

        CoordenadasTextura[i].x = CoordenadasTextura[i-num_vertices_lado].x + intervalo_texturas;
        CoordenadasTextura[i].y = CoordenadasTextura[i-num_vertices_lado].y;

        //cout << "[" << i << "] x = " << Vertices[i].x << " y = " << Vertices[i].y  << " z = " << Vertices[i].z << endl;
        //cout << " textura --> x = " << CoordenadasTextura[i].x << "   y = " << CoordenadasTextura[i].y << endl;
    }


    /////// GENERACIÓN DE TRIÁNGULOS
    // Voy a seguir la misma lógica que usé para crear las caras de los objetos por barrido circular
    int vertices_size = Vertices.size();
    _vertex3ui tP, tI;                      // Triangulos par e impar
    _vertex3ui tSUM;  //triangulo que se encarga de sumar por columnas
    _vertex3ui tU;  //triangulo unidad, utilizado en sumas de triangulos
    tU._0 = 1;
    tU._1 = 1;
    tU._2 = 1;

    tP._0 = 1;
    tP._1 = 0;
    tP._2 = num_vertices_lado;

    tI._0 = 1;
    tI._1 = num_vertices_lado;
    tI._2 = num_vertices_lado+1;

    // Dependiendo del maximo de filas a recorrer también cambiará el valor que hay que sumar por columnas
    tSUM._0 = num_vertices_lado;
    tSUM._1 = num_vertices_lado;
    tSUM._2 = num_vertices_lado;

    int t = 0;  // indice para ir llenando el vector de triangulos
    for (int f = 0; f < num_lineas_lado; f++){    // Recorremos las filas de la "matriz"
        // Actualizo los triángulos según la fila
        if (f != 0){
            tP = trianglesSum(tP, tU, vertices_size);
            tI = trianglesSum(tI, tU, vertices_size);
        }

        for (int c = 0; c < num_lineas_lado; c++){ // Recorremos sus columnas
            if (c == 0){
                Triangles[t] = tP;
                Triangles[t+1] = tI;
            }
            else{
                Triangles[t] = trianglesSum(Triangles[t-2], tSUM, vertices_size);
                Triangles[t+1] = trianglesSum(Triangles[t-1], tSUM, vertices_size);
            }

            t+=2;
        }
    }
}




_vertex3ui _chessboard::trianglesSum(const _vertex3ui &t1,const _vertex3ui &t2, int valorMax){
    _vertex3ui t3;
    t3._0 = (t1._0 + t2._0) % valorMax;
    t3._1 = (t1._1 + t2._1) % valorMax;
    t3._2 = (t1._2 + t2._2) % valorMax;

    return t3;
}






















