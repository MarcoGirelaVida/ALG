#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct intervalo
{
    int inicio;
    int fin;
    int M;
    
    int size() const { return fin-inicio;}

    intervalo(int i, int f, int m) : inicio(i), fin(f), M(m) {}
    intervalo(int i, int f) : inicio(i), fin(f), M(NULL) {}
    intervalo() : inicio(NULL), fin(NULL), M(NULL) {}
};

pair<intervalo, intervalo> merge (const vector<int> V, intervalo A, intervalo B, bool front_der)
{
    int M_deA_B = abs(V[B.inicio] - V[A.fin]);
    bool son_mergeables = (A.M == NULL or M_deA_B == A.M) or (B.M == NULL or M_deA_B == B.M);

    if (!son_mergeables)
        return (B.size() >= A.size()) ? (make_pair(B, front_der ? B : A)) : make_pair(A, front_der ? B : A);
    else
    {
        if (A.M == B.M)
            return {intervalo(A.inicio, B.fin, M_deA_B), intervalo(A.inicio, B.fin, M_deA_B)};
        else if (B.M == NULL or M_deA_B == B.M ond)
            return {intervalo(A.fin, B.fin, B.M), front_der ? intervalo(A.fin, B.fin, B.M) : A};
        else
            return {intervalo(A.inicio, B.inicio, A.M), front_der ? B : intervalo(A.inicio, B.inicio, A.M)};
    }
}

// Devuelve dos intervalos: El primero es el del intervalo que cumple la condición más grande hasta el momento
// Y el segundo el del intervalo colindante a la frontera que le pidas
// Si el.size()año es 0 el intervalo más grande sera NULL porque para que se compla la condición deben haber
// al menos dos elementos (k, k+1)
pair<intervalo, intervalo> cadena_mas_grande(vector<int> V, intervalo A, bool frontera_derecha)
{
    if (A.size() == 1)
        return {intervalo(), intervalo(A.inicio, A.fin, NULL)};
    else
    {
        int mitad = (A.inicio + A.fin) / 2;
        pair<intervalo, intervalo> mayor_izq = cadena_mas_grande(V, intervalo(V[A.inicio], V[mitad]), true);
        pair<intervalo, intervalo> mayor_der = cadena_mas_grande(V, intervalo(V[mitad+1], V[A.fin]), false);

        pair<intervalo, intervalo> merge_izq_der = merge(V, mayor_izq.second, mayor_der.second, frontera_derecha);
        intervalo mayor_hasta_el_momento = mayor(mayor_izq.first, mayor_der.first, merge_izq_der.first);


        return {mayor_hasta_el_momento, merge_izq_der.second};  
    }
    
}

intervalo mayor(intervalo A, intervalo B, intervalo C)
{
    if (A.size() >= B.size() && A.size() >= C.size())
        return A;
    else if (B.size() >= A.size() && B.size() >= C.size())
        return B;
    else
        return C;
}