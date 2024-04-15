#include <iostream>
#include <algorithm>
#include <cstdio>

#define MAX_PLAZAS 1000 // Máximo número de plazas

int padre[MAX_PLAZAS]; // Este array contendrá el padre de cada plaza

// Método de inicialización
void InicializarConjuntos(int n) {
    for (int i = 1; i <= n; i++) {
        padre[i] = i; // Cada plaza es un conjunto independiente
    }
}

// Método para encontrar la raíz del conjunto al que pertenece una plaza
int EncontrarRaiz(int x) {
    if (x == padre[x]) {
        return x; // Si la plaza es la raíz de sí misma, hacemos return
    }
    return padre[x] = EncontrarRaiz(padre[x]); // De lo contrario, busca la raíz de su padre
}

// Método para unir dos conjuntos de plazas
void UnirConjuntos(int a, int b) {
    a = EncontrarRaiz(a);
    b = EncontrarRaiz(b);
    padre[b] = a; // Hace que la raíz de b sea la nueva raíz de a
}

// Método que determina si dos plazas están en la misma componente conexa
bool MismaComponente(int x, int y) {
    return EncontrarRaiz(x) == EncontrarRaiz(y);
}

struct Calle {
    int origen;     // Plaza de origen de la calle
    int destino;    // Plaza de destino de la calle
    int costo;      // Costo de asfaltar la calle
    bool operator<(const Calle &c) const {
        return costo < c.costo; // Comparador por costo de asfaltado, se usará para ordenar las calles en orden ascendente
    }
};

Calle calles[MAX_PLAZAS]; // Array de calles para usar en Kruskal

void Kruskal(int num_plazas, int num_calles) {
    int total = 0;          // Costo total del asfaltado
    int num_calles_asfaltadas = 0; // Número de calles asfaltadas

    InicializarConjuntos(num_plazas); // Inicializamos cada plaza como un conjunto independiente
    std::sort(calles, calles + num_calles); // Ordenamos las calles por su costo de asfaltado

    std::cout << "Calles asfaltadas:\n";
    for (int i = 0; i < num_calles; ++i) { // Recorremos las calles ya ordenadas por costo de asfaltado
        int origen = calles[i].origen;    // Plaza de origen de la calle actual
        int destino = calles[i].destino;  // Plaza de destino de la calle actual
        int costo = calles[i].costo;      // Costo de asfaltar la calle actual

        // Verificamos si las plazas de origen y destino están en la misma componente conexa
        if (!MismaComponente(origen, destino)) { // Si no están en la misma componente, evitamos ciclos
            total += costo;              // Incrementamos el costo total del asfaltado
            UnirConjuntos(origen, destino);  // Unimos las plazas de origen y destino en una misma componente
            num_calles_asfaltadas++;               // Incrementamos el número de calles asfaltadas
            std::cout << "Calle entre plaza " << origen << " y plaza " << destino << ", costo: " << costo << "\n";
        }
    }

    // Si el número de calles asfaltadas no es igual al número de plazas - 1, mostramos un mensaje de error
    if (num_plazas - 1 != num_calles_asfaltadas) {
        std::cout << "No existe solución válida para el problema ingresado, el pueblo debe ser conexo.\n";
        return;
    }
    std::cout << "El costo mínimo de asfaltar todas las calles necesarias es: " << total << "\n";
}


int main() {
    // Datos de ejemplo
    int num_plazas = 5;
    int num_calles = 9;
    Calle calles_ejemplo[] = {
        {1, 2, 1100000}, {1, 3, 130000}, {1, 4, 450004}, {1, 5, 748456},
        {2, 3, 1300000}, {2, 5, 1700000}, {2, 4, 555123} , {3, 5, 554521},
        {4, 5, 143552}
    };

    // Copiamos los datos de ejemplo al arreglo de calles
    std::copy(calles_ejemplo, calles_ejemplo + num_calles, calles);

    // Ejecutamos el algoritmo de Kruskal con los datos de ejemplo
    Kruskal(num_plazas, num_calles);

    return 0;
}

