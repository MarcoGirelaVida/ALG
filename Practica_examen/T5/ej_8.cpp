#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

int suma(const vector<bool> conjunto)
{
    int suma = 0;
    for (int i = 0; i < conjunto.size(); i++)
        suma += i*conjunto[i];
    return suma;
}

int suma_cuadrados(const vector<bool> conjunto)
{
    int suma = 0;
    for (int i = 0; i < conjunto.size(); i++)
        suma += conjunto[i] ? pow(i, 2) : 0;

    //cerr << "Suma cuadrados: " << suma << endl;
    return suma;
}

bool es_mejor (const vector<bool> conjunto_A, const vector<bool> conjunto_B)
{
    if (!conjunto_A.size())
        return false;
    else if (!conjunto_B.size())
        return true;
    else
        return !conjunto_B.size() or suma_cuadrados(conjunto_A) < suma_cuadrados(conjunto_B);
}

vector<bool> backtraking(const int N, vector<bool> secuencia)
{
    int suma_sec = suma(secuencia);
    int suma_sig = suma_sec + secuencia.size();
    if (suma_sec == N) return secuencia;
    else if (suma_sig > N) return vector<bool>();
    else
    {
        secuencia.push_back(true);
        vector<bool> si_cojo = backtraking(N, secuencia);
        secuencia[secuencia.size() - 1] = false;
        vector<bool> si_no_cojo = backtraking(N, secuencia);

        return es_mejor(si_cojo, si_no_cojo) ? si_cojo : si_no_cojo;
    }
}

int main()
{
    vector<bool> secuencia;
    secuencia = backtraking(8, secuencia);

    for (int i = 0; i < secuencia.size(); i++)
        if (secuencia[i]) cerr << i << " | ";
}