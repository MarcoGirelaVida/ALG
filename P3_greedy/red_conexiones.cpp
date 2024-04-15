// Implementación del algoritmo de djistra para la práctica 3 algorítmicia
// Marco Girela Vida Grupo B3
#include <iostream>
using namespace std;
#include <limits.h>
 
#define num_nodos 9
 
// Printea las distancias
void printea_distancias(int distancia_de[])
{
    cout << "Nodo \t Distancia Del Origen" << endl;
    for (int nodo = 0; nodo < num_nodos; nodo++)
        cout << nodo << " \t\t\t\t" << distancia_de[nodo] << endl;
}
 
// Printea la ruta óptima para llegar a un nodo
void printea_ruta(int nodo_anterior[], int nodo_destino)
{
    // Si el nodo anterior es -1, significa que no hay camino
    if (nodo_anterior[nodo_destino] == -1)
    {
        cout << "No hay camino para llegar al nodo " << nodo_destino << endl;
        return;
    }
 
    // Vector para guardar la ruta
    int ruta[num_nodos];
    int contador = 0;
    int nodo_actual = nodo_destino;
    ruta[contador] = nodo_actual;
    contador++;
 
    // Mientras no llegue al nodo origen, sigue buscando el nodo anterior
    while (nodo_anterior[nodo_actual] != -1)
    {
        ruta[contador] = nodo_anterior[nodo_actual];
        nodo_actual = nodo_anterior[nodo_actual];
        contador++;
    }
 
    // Printea la ruta
    cout << "Ruta: ";
    for (int i = contador - 1; i >= 0; i--)
        cout << ruta[i] << " -> ";
    cout << endl;
}

// Función para saber cual es el nodo con menor distancia
int nodo_menor_coste(int distancia_de[], bool nodos_explorados[])
{
    int menor_distancia = INT_MAX, nodo_menor_distancia;
 
    for (int nodo = 0; nodo < num_nodos; nodo++)
        if (nodos_explorados[nodo] == false && distancia_de[nodo] <= menor_distancia)
            menor_distancia = distancia_de[nodo], nodo_menor_distancia = nodo;
 
    return nodo_menor_distancia;
}
 
void camino_conexiones(int matriz_adyacencia[num_nodos][num_nodos], int nodo_origen, int * nodo_anterior)
{
    // Vector de las distancias (costes) de cada nodo con respecto al origen
    int distancia_de[num_nodos];

    // Lista para saber si un nodo fue ya explorado o no
    bool nodos_explorados[num_nodos];
 

    // Inicializo las distancias a "infinito" y los nodos explorados a "falso
    for (int i = 0; i < num_nodos; i++)
        distancia_de[i] = INT_MAX, nodos_explorados[i] = false;
 
    // Inicializo la distancia del origen a si mismo a 0 
    distancia_de[nodo_origen] = 0;
 
    // Busco el camino más corto para cada nodo
    for (int i = 0; i < num_nodos - 1; i++)
    {
        // Elijo el nodo con la menor distancia al origen como nodo a explorar
        int nodo_pivote = nodo_menor_coste(distancia_de, nodos_explorados);
 
        // Marco dicho nodo como explorado
        nodos_explorados[nodo_pivote] = true;
 
        // Actualizo las distancias mínimas a cada nodo, si es que hubiese una distancia menor
        for (int nodo_adyacente = 0; nodo_adyacente < num_nodos; nodo_adyacente++)
 
            // Actualizo la distancia si (en orden respectivo):
            // 1. El nodo adyacente no fue explorado
            // 2. El nodo pivote y el nodo adyacente están conectados (son adyacentes)
            // 3. La distancia del nodo pivote al nodo adyacente no es infinita (esto realmente no sé por qué se pone, pero en las implementaciones que he visto por internet lo ponían)
            // 4. La nueva distancia es menor que la que había previamente
            if (!nodos_explorados[nodo_adyacente] && matriz_adyacencia[nodo_pivote][nodo_adyacente]
                && distancia_de[nodo_pivote] != INT_MAX
                && distancia_de[nodo_pivote] + matriz_adyacencia[nodo_pivote][nodo_adyacente] < distancia_de[nodo_adyacente])
            {
                distancia_de[nodo_adyacente] = distancia_de[nodo_pivote] + matriz_adyacencia[nodo_pivote][nodo_adyacente];
                nodo_anterior[nodo_adyacente] = nodo_pivote;
            }
    }
 
    // Printea los costes actualizados
    printea_distancias(distancia_de);
}
 
// driver's code
int main()
{
 
    // Creo un grafo cualquiera de los nodos deseados
    int matriz_adyacencia[num_nodos][num_nodos] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
 
    // Function call
    int rutas[num_nodos] = { -1 };
    camino_conexiones(matriz_adyacencia, 0, rutas);
 
    // Printeo la ruta óptima para llegar al nodo 8
    printea_ruta(rutas, 8);

    return 0;
}
 
// VERSIÓN REDUCIDA PARA EL PDF
/*
int * camino_conexiones(int matriz_adyacencia[num_nodos][num_nodos], int nodo_origen)
{
    // Inicializo los vectores
    int distancia_de[num_nodos];
    bool nodos_explorados[num_nodos];
    int nodo_anterior[num_nodos];
 
    // Inicializo las distancias
    distancia_de[nodo_origen] = 0;

    for (int i = 0; i < num_nodos; i++)
        distancia_de[i] = INT_MAX, nodos_explorados[i] = false;
 

    for (int i = 0; i < num_nodos - 1; i++)
    {
        // Elijo el nodo con la menor distancia al origen como nodo a explorar
        int nodo_pivote = nodo_mas_cercano(distancia_de, nodos_explorados);
        nodos_explorados[nodo_pivote] = true;
 
        // Actualizo distancias
        for (int nodo_adyacente = 0; nodo_adyacente < num_nodos; nodo_adyacente++)
        {
            if (!nodos_explorados[nodo_adyacente]
                && matriz_adyacencia[nodo_pivote][nodo_adyacente]
                && distancia_de[nodo_pivote] != INT_MAX
                && distancia_de[nodo_pivote] + matriz_adyacencia[nodo_pivote][nodo_adyacente] < distancia_de[nodo_adyacente])
            {
                distancia_de[nodo_adyacente] = distancia_de[nodo_pivote] + matriz_adyacencia[nodo_pivote][nodo_adyacente];
                nodo_anterior[nodo_adyacente] = nodo_pivote;
            }
        } 
    }

    return nodo_anterior;
}
*/