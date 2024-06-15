#include <queue>
#include <vector>
using namespace std;

void rellenar_tabla_costes_minimos(const vector<int> peso, vector<vector<int>> &tabla)
{
    // RELLENO LOS CASOS BASE
    for (int obj_i = 0; obj_i < tabla.size(); obj_i++)
        tabla[obj_i][0] = 0;

    // Relleno la primera fila
    for (int MAX = 0; MAX < tabla.size(); MAX++)
            tabla[0][MAX] = (peso[0] > MAX/2) ? 0 : peso[0];
    
    //--------------------------------------//
    // RELLENO EL RESTO CON RECURSIVIDAD
    for (int obj_i = 1; obj_i < tabla.size(); obj_i++)
        for (int MAX = 1; MAX < tabla.size(); MAX++)
            tabla[obj_i][MAX] = peso[obj_i] <= MAX/2 ?
                max(tabla[obj_i-1][MAX-peso[obj_i]], tabla[obj_i-1][MAX]) : tabla[obj_i-1][MAX];
}

vector<int> recuperar_solucion(const vector<vector<int>> &tabla, const vector<int> peso, const int num_objetos, const int MAX)
{
    int obj_i = num_objetos;
    int MAX_i = MAX;
    vector<int> solucion;

    while (obj_i >= 0 and MAX_i >= 0)
    {
        if (peso[obj_i] <= MAX_i/2
            and tabla[obj_i-1][MAX-peso[obj_i]] >= tabla[obj_i-1][MAX])
        {
            solucion.push_back(obj_i);
            MAX_i -= peso[obj_i];
        }
        obj_i--;
    }

    return solucion;
}