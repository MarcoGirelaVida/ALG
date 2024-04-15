#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>

using namespace std;




vector<pair<int,int>> AsignacionParejas(vector<vector<int>> v){

    // Lista de candidatos a emparejar
    list<int> candidatos;

    // Numeración de los candidatos. Se usa para inicialiar la lista
    int n_candidatos = v.size();

    // Valores que permiten ir guardando las parejas a lo largo del algoritmo.
    int afinidad_maxima = 0;
    pair<int,int> pareja_elegida;
    int pareja_aux = 0;

    vector<pair<int,int>> resultado;

    // Inicializamos la lista
    for (int i = 0; i < n_candidatos; i++){
        candidatos.push_back(i);
    }


    auto it = candidatos.begin();

    // Mientras queden candidatos
    while (it != candidatos.end()){

        // Recorremos todas las afinidades todas las afinidades
        for (int i = 0; i < v.size(); i++){

            // Buscamos que aquel cuya afinidad estamos comprobando no haya sido emparejado
            auto it2 = find(candidatos.begin(), candidatos.end(), i);

            // Si no ha sido emparejado y no es él mismo...
            if (v[*it][i] != -1 && it2 != candidatos.end()){
                // Si su afinidad supera el máximo hasta ahora Actualizo el máximo y la pareja elegida
                if ((v[*it][i]*v[i][*it]) > afinidad_maxima){
                    afinidad_maxima = v[*it][i]*v[i][*it];
                    pareja_elegida = make_pair(*it,i);
                    pareja_aux = i;
                    
                }
            }
        }

        // Guardo la pareja y elimino a los dos candidatos elegidos
        resultado.push_back(pareja_elegida);
        candidatos.erase(it);
        auto it_aux = find(candidatos.begin(), candidatos.end(), pareja_aux);
        candidatos.erase(it_aux);

        // Restauro it y afinidad_maxima para poder seguir buscando
        it = candidatos.begin();
        afinidad_maxima = 0;
    }
    
    return resultado;

}





int main(){

    int n_fil = 6;
    int n_col = 6;

// Inicializar la semilla para generar números aleatorios
    srand(time(NULL));

    // Definir una matriz de tamaño FILAS x COLUMNAS
    vector<vector<int>> afinidades(n_fil, vector<int>(n_col));

    // Llenar la matriz con números aleatorios entre 1 y 10
    for (int i = 0; i < n_fil; ++i) {
        for (int j = 0; j < n_col; ++j) {
            afinidades[i][j] = rand() % 10 + 1;
            // Si i == j, establecer -1 en la diagonal principal
            if (i == j) {
                afinidades[i][j] = -1;
            }
        }
    }

    // Imprimir la matriz
    std::cout << "Matriz generada:" << std::endl;
    for (int i = 0; i < n_fil; ++i) {
        for (int j = 0; j < n_col; ++j) {
            std::cout << afinidades[i][j] << " ";
        }
        std::cout << std::endl;
    }

    vector<pair<int,int>> parejas;

    parejas = AsignacionParejas(afinidades);

    // Imprimir parejas

    for (int i = 0; i < parejas.size(); i++){

        cout << "Pareja " << i << ": " << parejas[i].first << " " << parejas[i].second << endl;

    }

    return 0;

}