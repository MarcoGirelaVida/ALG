#include <iostream>
#include <vector>
#include <algorithm> 
#include <cstdlib> 
#include <ctime>   

using namespace std;


int afinidad(int invitado1, int invitado2,vector<vector<int>>& tabla_afinidades) {
    int conveniencia;

	conveniencia = tabla_afinidades[invitado1-1][invitado2-1] + tabla_afinidades[invitado2-1][invitado1-1];

    return conveniencia;
}

vector<int> MesaRedonda(int n, vector<vector<int>>& tabla_afinidades) {

    vector<int> invitados; // Número de invitados
    for (int i = 0; i < n; ++i) 
        invitados.push_back( i + 1);
    
    vector<int> asignacion; // Invitados sentados en la mesa

    while (!invitados.empty()) {
        if (asignacion.empty()) {
            asignacion.push_back(invitados.front());
            invitados.erase(invitados.begin());
        } else {
            // Obtener el último invitado asignado
            int ultimo_invitado = asignacion.back();

            // Calcular la afinidad máxima y el siguiente invitado basado en la afinidad
            int mejor_afinidad = -1;
            int siguiente_invitado = -1;
            for (int i = 0; i < invitados.size(); i++) {
                int invitado = invitados[i];
                if (invitado != ultimo_invitado && afinidad(ultimo_invitado, invitado, tabla_afinidades) > mejor_afinidad) {
                    mejor_afinidad = afinidad(ultimo_invitado, invitado, tabla_afinidades);
                    siguiente_invitado = invitado;
                }
            }

            // Agregar el siguiente invitado a la asignación y eliminarlo de la lista de invitados
            asignacion.push_back(siguiente_invitado);
            invitados.erase(remove(invitados.begin(), invitados.end(), siguiente_invitado), invitados.end());
        }
    }
	
	asignacion.push_back(1); // Ponemos en el último lugar de nuevo al primer invitado para representar que es una mesa

    return asignacion;
}


int main() {
    
    int n = 4; // Número total de invitados

	srand(time(NULL));
	
    vector<vector<int>> tabla_afinidades(n, vector<int>(n, 0)); 

	for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            tabla_afinidades[i][j] = rand() % 100 + 1;
            // Si i == j, establecer -1 en la diagonal principal
            if (i == j) {
                tabla_afinidades[i][j] = -1;
            }
        }
    }

    // Imprimir la matriz de afinidad
    cout << "Matriz generada:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << tabla_afinidades[i][j] << " ";
        }
        cout << endl;
    }

    vector<int> resultado = MesaRedonda(n, tabla_afinidades);

    cout << "Asignación de invitados en la mesa redonda:" << endl;
    for (int invitado : resultado) {
        cout << invitado << " ";
    }
    cout << endl;

    return 0;
}
