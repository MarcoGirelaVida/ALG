#include <vector>
#include <iostream>
#include <limits>
using namespace std;

typedef unsigned char aldea;
const aldea DESTINO = 0;
const unsigned char INFINITO = numeric_limits<unsigned char>::max();


void printea_matriz_costes(const vector<vector<unsigned char>> &costes)
{
    for (size_t i = 0; i < costes.size(); i++)
    {
        for (size_t j = 0; j < costes[i].size(); j++)
        {
            cout << (int) costes[i][j] << " | ";
        }
        cout << endl;
    }
}

unsigned char coste_minimo(const aldea aldea_origen, const aldea aldeas_disponibles, const vector<vector<unsigned char>> &costes, vector<vector<unsigned char>> &costes_minimos)
{
    cerr << endl << "MATRIZ COSTES:" << endl;
    printea_matriz_costes(costes);
    cerr << endl;
    // Rellenamos la memoria para los casos base aldea > origen
    for (aldea aldea_i = 0; aldea_i < aldeas_disponibles; aldea_i++)
        for (aldea origen_i = 0; origen_i < aldea_i; origen_i++)
            costes_minimos[aldea_i][origen_i] = INFINITO;


    // Rellenamos la memoria para el caso base aldea == DESTINO
    for (aldea origen_i = 0; origen_i < aldea_origen; origen_i++)
        costes_minimos[DESTINO][origen_i] = costes[DESTINO][origen_i];
    printea_matriz_costes(costes_minimos);

    // Rellenamos la memoria para el resto de casos (aldea > DESTINO and origen > DESTINO and aldea <= origen)
    for (aldea aldea_i = 1; aldea_i < aldeas_disponibles; aldea_i++)
        for (aldea origen_i = aldea_i; origen_i < aldea_origen; origen_i++)
        {
            cerr << "aldea_i: " << (int) aldea_i << " origen_i: " << (int) origen_i << endl;
            cerr << "Costes_minimos[aldea_i-1][origen_i]: " << (int) costes_minimos[aldea_i-1][origen_i] << endl;
            cerr << "Costes_minimos[aldea_i-1][aldea_i]: " << (int) costes_minimos[aldea_i-1][aldea_i] << endl;
            cerr << "Costes[aldea_i][origen_i]: " << (int) costes[aldea_i][origen_i] << endl;
            costes_minimos[aldea_i][origen_i] = min(costes_minimos[aldea_i-1][origen_i], costes_minimos[aldea_i-1][aldea_i]) + costes[aldea_i][origen_i];
        }

    cerr << endl << "MATRIZ COSTES MINIMOS:" << endl;
    printea_matriz_costes(costes_minimos);
    cerr << endl;

    return costes_minimos[aldeas_disponibles-1][aldea_origen-1];
}

int main()
{
    vector<vector<unsigned char>> costes_minimos(5, vector<unsigned char>(5, (unsigned char) NULL));
    vector<vector<unsigned char>> matriz_adyacencia =
    {
        {0,     3,    3,    INFINITO,   INFINITO},
        {NULL,  0,    4,    7,          INFINITO},
        {NULL,  NULL, 0,    2,          3},
        {NULL,  NULL, NULL, 0,          2},
        {NULL,  NULL, NULL, NULL,       0}
    };

    unsigned char costes_minimo = coste_minimo(5, 5, matriz_adyacencia, costes_minimos);

    cerr << "Coste minimo: " << (int) costes_minimo << endl;
    return 0;


}