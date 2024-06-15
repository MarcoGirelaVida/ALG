#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;
/*
Cada hijo es una intersección donde puedo poner la siguiente cámara
El algoritmo explora en anchura, puesto que así en cuanto encuentre una solución paro
y no tengo que hacer fumadas de poda y tal

La solución tendrá un formato {interseccion_camara1, intersección_camara2...}
*/
bool es_solucion (const pair<int, vector<int>> nodo, const vector<vector<int>> &matriz_adyacencia)
{
    unordered_set<int> pasillos_vigilados;
    for (auto &nodo : nodo.second)
    {
        for (int i = 0; i < matriz_adyacencia.size(); i++)
            pasillos_vigilados.insert(matriz_adyacencia[nodo][i]);
    }
    return pasillos_vigilados.size() == matriz_adyacencia.size();
}

vector<int> distribucion_optima(const vector<vector<int>> &matriz_adyacencia)
{
    queue<pair<int, vector<int>>> frontera;
    pair<int, vector<int>> nodo = make_pair(0, vector<int>());
    frontera.push(nodo);
    (nodo.second).push_back(nodo.first);

    while (!frontera.empty())
    {
        nodo = frontera.front();
        frontera.pop();

        // Meto los hijos no usados en la frontera
        for (int i = 0; i < matriz_adyacencia.size(); i++)
        {
            bool disponible = true;
            for (int j = 0; i < nodo.second.size() and disponible; i++)
                disponible = i == nodo.second[j];

            if (disponible)
            {
                pair<int, vector<int>> nodo_i = make_pair(i, nodo.second);
                nodo_i.second.push_back(i);
                if(es_solucion(nodo_i, matriz_adyacencia)) return nodo_i.second;
                else frontera.push(nodo_i);
            } 
        }
    }
    return vector<int>();
}
