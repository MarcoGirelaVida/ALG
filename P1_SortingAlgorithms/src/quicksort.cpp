/*
Marco Girela Vida 2ºB3

Implementación de quicksort en C++

Hecha a partir de la explicación del algortimo (bastante buena) de este video
de geeksforgeeks: https://www.geeksforgeeks.org/videos/quick-sort-sde-sheet/

Con la variación de que se escoge el pivote como el medio del primero, mediano
y último que está extraida de la sección "Implementation Issues" de la
wikipediaen inglés: https://en.wikipedia.org/wiki/Quicksort
*/

#include "quicksort.hpp"

// Función para intercambiar 
void swap(int * pos1, int * pos2)
{
    int tmp = *pos1;
    *pos1 = *pos2;
    *pos2 = tmp;
}

// Función que organiza los elementos a la izquierda (si son menores)
// o derecha (si son mayores) del pivote
// Será la función que se repita por cada iteración recursiva.
// array: Vector donde se aplica la función.
// low: Punto de inicio de la partición que se quiere particionar.
// high: Punto de fin de dicha partición.
// En esta implementación se elige como pivote el último elemento.
int partition(int array[], int start, int end)
{
    // El "sistema" pone al principio al elemento más pequeño, y luego de los otros
    // dos coge el menor (el elemento medio) y lo pone al final, y siempre coge el del final
    int median = (end - start) / 2;
    if (array[median] < array[start])
        swap(&array[start], &array[median]);
    if (array[end] < array[start])
        swap(&array[start], &array[end]);
    if (array[median] < array[end])
        swap(&array[median], &array[end]);
    
    int pivot = array[end]; 
    
    int insertion_point = start;

    for (int i = start; i < end; i++)
    {
        if (array[i] <= pivot)
        {
            swap(&array[insertion_point], &array[i]);
            insertion_point++;
        }
    }

    // Al terminar intercambio el pivote por el último punto de inserción
    // (obserava que si todos los elementos eran menores que el pivote
    // se intercambiará consigo mismo)
    swap(&array[insertion_point], &array[end]);

    // devuelvo el punto por el cual se divide el vector en dos particiones
    // (donde se encuentra el pivote)
    return insertion_point;
}

// Función principal recursiva.
// Hasta que no se llegue al caso base (el vector está ordenado)
// se particiona el vector en la sección dada y se aplica de nuevo
// la función en las subsecciones restantes
void quicksort(int array[], int start, int end)
{
    // observa que si llegamos al final (el pivot = end)
    // Cuando hacemos la llamada recursiva pivot + 1 = start, que será mayor que end
    if (start < end)
    {
        int pivot = partition(array, start, end);

        // Observa que al pivote como tal no lo metemos en ninguna
        // de las llamadas porque sabemos que pase lo que pase este ya está
        // ordenado (lo que haya a su izquierda es menor que él y lo que haya a
        // su derecha es mayor)
        quicksort(array, start, pivot - 1);
        quicksort(array, pivot + 1, end);
    }
}